#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Define.h"

#include "Debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Candle.h"
#include "TileMap.h"
#include "Ground.h"
#include "Items.h"


Game * game;
Simon * simon;
Candle * candle;
TileMap * tilemap;
Ground * ground;
Items * item;
Whip * whip;
Effect * effect;

Textures * textures = Textures::GetInstance();
Sprites * sprites = Sprites::GetInstance();
Animations * animations = Animations::GetInstance();

vector<LPGAMEOBJECT> Objects;

void LoadAllResources()
{
	simon = new Simon();
	simon->LoadResources(textures, sprites, animations);

	candle = new Candle();
	candle->LoadResources(textures, sprites, animations);

	effect = new Effect();
	effect->LoadResources(textures, sprites, animations);

	ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	item = new Items();
	item->LoadResources(textures, sprites, animations);

	whip = new Whip();
	whip->LoadResources(textures, sprites, animations);
}


class KeyHandler : public KeyEventHandler
{
	virtual void KeyState(BYTE *state)
	{
		// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
		if (simon->GetState() == JUMP && simon->IsTouchGround() == false)
			return;

		// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render
		if (simon->GetState() == HIT_STAND && simon->animations[HIT_STAND]->IsOver(450) == false)
			return;

		if (simon->GetState() == HIT_SIT && simon->animations[HIT_SIT]->IsOver(450) == false)
			return;
		
		if (game->IsKeyDown(DIK_RIGHT))
		{
			simon->nx = 1;
			simon->SetState(WALK);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			simon->nx = -1;
			simon->SetState(WALK);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			simon->SetState(SIT);
		}
		else
		{
			simon->SetState(STAND);
		}
	}

	virtual void OnKeyDown(int KeyCode)
	{
		DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

		switch (KeyCode)
		{
		case DIK_SPACE:
			if (simon->GetState() == JUMP || simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT)
				return;
			simon->SetState(JUMP);
			break;
		case DIK_Z:
			if ((simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT))
				return;
			if (simon->GetState() == STAND || simon->GetState() == JUMP)
			{
				simon->SetState(HIT_STAND);
			}
			else if (simon->GetState() == SIT)
			{
				simon->SetState(HIT_SIT);
			}
			break;
		default:
			break;
		}
	}

	virtual void OnKeyUp(int KeyCode)
	{
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	}
};

KeyHandler * keyHandler;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Update(DWORD dt)
{
	//vector<LPGAMEOBJECT*> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects

	//for (int i = 1; i < Objects.size(); i++)
	//{
	//	if (dynamic_cast<Items*>(Objects[i]))
	//		DebugOut(L"xXX   xx  xxxx\n");

	//	coObjects.push_back(&(Objects[i]));
	//}

	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i] == NULL)
		{
			Objects.erase(Objects.begin() + i);
			i--;
			continue;
		}

		vector<LPGAMEOBJECT*> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects

		if (dynamic_cast<Simon*>(Objects[i]))
		{
			for (int j = 0; j < Objects.size(); j++)
			{
				if (Objects[j] == NULL) {
					Objects.erase(Objects.begin() + j);
					j--;
					continue;
				}

				if (i != j) // thêm tất cả objects "ko phải là simon", dùng trong hàm update của simon 
					coObjects.push_back(&(Objects[j]));
			}
		}
		else if (dynamic_cast<Items*>(Objects[i]))
		{
			for (int j = 0; j < Objects.size(); j++)
			{
				if (Objects[j] == NULL) {
					Objects.erase(Objects.begin() + j);
					j--;
					continue;
				}

				if (dynamic_cast<Ground*>(Objects[j])) // thêm tất cả objects "là ground", dùng trong hàm update của item
				{
					coObjects.push_back(&(Objects[j]));
				}
			}
		}
		else
		{
			coObjects.push_back(&(Objects[i]));
		}


		Objects[i]->Update(dt, &coObjects);
	}

	//simon->Update(dt, &coObjects);

	// render camera
	float cx, cy;
	simon->GetPosition(cx, cy);
	
	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tilemap->GetMapWidth()) 
		game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// clear back buffer with background color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		tilemap->Draw(game->GetCameraPositon());

		for (int i = 0; i < Objects.size(); i++)
		{
			Objects[i]->Render();
		}
			

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

void NewGame()
{
	Objects.clear();

	simon = new Simon();
	simon->AddAnimation(STAND_ANI);
	simon->AddAnimation(WALK_ANI);
	simon->AddAnimation(SIT_ANI);
	simon->AddAnimation(JUMP_ANI);
	simon->AddAnimation(HIT_SIT_ANI);
	simon->AddAnimation(HIT_STAND_ANI);
	simon->SetState(STAND_ANI);
	simon->SetPosition(0.0f, 224.0f);
	Objects.push_back(simon);

	///
	
	candle = new Candle();
	candle->AddAnimation(BIG_CANDLE_ANI);
	candle->SetPosition(160.0f, 224.0f);
	Objects.push_back(candle);

	candle = new Candle();
	candle->AddAnimation(BIG_CANDLE_ANI);
	candle->SetPosition(448.0f, 224.0f);
	Objects.push_back(candle);

	candle = new Candle();
	candle->AddAnimation(BIG_CANDLE_ANI);
	candle->SetPosition(672.0f, 224.0f);
	Objects.push_back(candle);

	candle = new Candle();
	candle->AddAnimation(BIG_CANDLE_ANI);
	candle->SetPosition(960.0f, 224.0f);
	Objects.push_back(candle);

	candle = new Candle();
	candle->AddAnimation(BIG_CANDLE_ANI);
	candle->SetPosition(1216.0f, 224.0f);
	Objects.push_back(candle);

	///

	for (int i = 0; i < 48; i++)
	{
		ground = new Ground();
		ground->AddAnimation(GROUND_ANI);
		ground->SetPosition(32 * i, 288.0f);
		Objects.push_back(ground);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	keyHandler = new KeyHandler();
	game->InitKeyboard(keyHandler);

	LoadAllResources();

	NewGame();

	tilemap = new TileMap(0, FILEPATH_TEX_SCENE_1, FILEPATH_DATA_SCENE_1, 1536, 320, 32, 32);
	tilemap->LoadResources();
	tilemap->Load_MapData();
	


	Run();

	return 0;
}