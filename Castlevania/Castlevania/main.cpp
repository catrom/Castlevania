﻿#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Candle.h"
#include "Define.h"
#include "TileMap.h"


Game * game;
Simon * simon;
Candle * candle;
TileMap * tilemap;

class KeyHandler : public KeyEventHandler
{
	virtual void KeyState(BYTE *state)
	{
		// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
		if (simon->GetState() == JUMP && simon->IsStand() == false)
			return;

		// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render
		if (simon->GetState() == HIT_STAND && simon->animations[HIT_STAND]->IsOver() == false)
			return;

		if (simon->GetState() == HIT_SIT && simon->animations[HIT_SIT]->IsOver() == false)
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
			simon->SetState(JUMP);
			break;
		case DIK_Z:
			if (simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT)
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
	simon->Update(dt);

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
		
		
		simon->Render();
		candle->Render();
		

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	simon = new Simon();

	keyHandler = new KeyHandler();
	game->InitKeyboard(keyHandler);
	simon->LoadResources();

	candle = new Candle();
	candle->LoadResources();

	tilemap = new TileMap(0, FILEPATH_TEX_SCENE_1, FILEPATH_DATA_SCENE_1, 1536, 320, 32, 32);
	tilemap->LoadResources();
	tilemap->Load_MapData();
	//tilemap->abcxyz();
	


	Run();

	return 0;
}