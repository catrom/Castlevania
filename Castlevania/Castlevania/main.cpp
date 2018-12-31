#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Define.h"
#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "SceneManager.h"
#include "Player.h"

Game * game;
Input * input;
Player * player;
SceneManager * scene;

TileMaps * tilemaps = TileMaps::GetInstance();
Textures * textures = Textures::GetInstance();
Sprites * sprites = Sprites::GetInstance();
Animations * animations = Animations::GetInstance();

// Read data of sprites and animations from file.
void LoadSprites(int id, LPCWSTR tex, LPCWSTR sprite_data, LPCWSTR animation_data)
{
	textures->Add(id, tex);
	LPDIRECT3DTEXTURE9 texture = textures->Get(id);

	ifstream spriteReader, animationReader;

	spriteReader.open(sprite_data);
	animationReader.open(animation_data);

	if (spriteReader.fail())
	{
		DebugOut(L"[ERROR] LoadSprites failed!: ID=%d", id);
		spriteReader.close();
		return;
	}

	if (animationReader.fail())
	{
		DebugOut(L"[ERROR] LoadAnimation failed!: ID=%d", id);
		animationReader.close();
		return;
	}

	// Load sprite data

	string spriteid;
	int left, top, right, bottom;

	while (spriteReader >> spriteid >> left >> top >> right >> bottom)
		sprites->Add(spriteid, left, top, right, bottom, texture);

	spriteReader.close();

	// Load animation data

	string animationId;
	string line;
	string spriteId;
	int frameTime;

	while (getline(animationReader, line))
	{
		LPANIMATION ani = new Animation();

		istringstream iss(line, istringstream::in);
		iss >> animationId;

		while (iss >> spriteId >> frameTime)
			ani->Add(spriteId, frameTime);

		animations->Add(animationId, ani);
	}

	animationReader.close();
}

// Load all sprite, animations, texture, tilemap data from file
void LoadResources()
{
	// for render bounding box
	textures->Add(ID_TEX_BBOX, L"Textures\\BBox.png");
	textures->Add(ID_TEX_BBOX_2, L"Textures\\BBox2.png");

	// for game control
	textures->Add(ID_TEX_YESNO, L"Textures\\YesNo.png");
	textures->Add(ID_TEX_PAUSE, L"Textures\\Pause.png");

	// Title screen
	textures->Add(ID_TEX_TITLESCREEN, L"Textures\\TitleScreen.png");

	// Intro screen
	textures->Add(ID_TEX_INTROSCREEN, L"Textures\\IntroScreen.png");

	// Game object
	LoadSprites(ID_TEX_SIMON, L"Textures\\Simon.png", L"Textures\\Simon_sprites.txt", L"Textures\\Simon_animations.txt");
	LoadSprites(ID_TEX_WHIP, L"Textures\\Whip.png", L"Textures\\Whip_sprites.txt", L"Textures\\Whip_animations.txt");
	LoadSprites(ID_TEX_BOSS, L"Textures\\Boss.png", L"Textures\\Boss_sprites.txt", L"Textures\\Boss_animations.txt");
	LoadSprites(ID_TEX_SUBWEAPONS, L"Textures\\SubWeapons.png", L"Textures\\SubWeapons_sprites.txt", L"Textures\\SubWeapons_animations.txt");
	LoadSprites(ID_TEX_CANDLE, L"Textures\\Candle.png", L"Textures\\Candle_sprites.txt", L"Textures\\Candle_animations.txt");
	LoadSprites(ID_TEX_EFFECT, L"Textures\\Effect.png", L"Textures\\Effect_sprites.txt", L"Textures\\Effect_animations.txt");
	LoadSprites(ID_TEX_SPARK, L"Textures\\Spark.png", L"Textures\\Spark_sprites.txt", L"Textures\\Spark_animations.txt");
	LoadSprites(ID_TEX_BUBBLES, L"Textures\\Bubbles.png", L"Textures\\Bubbles_sprites.txt", L"Textures\\Bubbles_animations.txt");
	LoadSprites(ID_TEX_GROUND, L"Textures\\Ground.png", L"Textures\\Ground_sprites.txt", L"Textures\\Ground_animations.txt");
	LoadSprites(ID_TEX_ITEMS, L"Textures\\Items.png", L"Textures\\Items_sprites.txt", L"Textures\\Items_animations.txt");
	LoadSprites(ID_TEX_STAIR, L"Textures\\Stair.png", L"Textures\\Stair_sprites.txt", L"Textures\\Stair_animations.txt");
	LoadSprites(ID_TEX_DOOR, L"Textures\\Door.png", L"Textures\\Door_sprites.txt", L"Textures\\Door_animations.txt");
	LoadSprites(ID_TEX_ZOMBIE, L"Textures\\Zombie.png", L"Textures\\Zombie_sprites.txt", L"Textures\\Zombie_animations.txt");
	LoadSprites(ID_TEX_BLACK_LEOPARD, L"Textures\\BlackLeopard.png", L"Textures\\BlackLeopard_sprites.txt", L"Textures\\BlackLeopard_animations.txt");
	LoadSprites(ID_TEX_VAMPIRE_BAT, L"Textures\\VampireBat.png", L"Textures\\VampireBat_sprites.txt", L"Textures\\VampireBat_animations.txt");
	LoadSprites(ID_TEX_FISHMAN, L"Textures\\FishMan.png", L"Textures\\FishMan_sprites.txt", L"Textures\\FishMan_animations.txt");
	LoadSprites(ID_TEX_FIREBALL, L"Textures\\FireBall.png", L"Textures\\FireBall_sprites.txt", L"Textures\\FireBall_animations.txt");
	LoadSprites(ID_TEX_RECT, L"Textures\\Rect.png", L"Textures\\Rect_sprites.txt", L"Textures\\Rect_animations.txt");
	LoadSprites(ID_TEX_HP, L"Textures\\HP.png", L"Textures\\HP_sprites.txt", L"Textures\\HP_animations.txt");
	LoadSprites(ID_TEX_BREAKWALL, L"Textures\\BreakWall.png", L"Textures\\BreakWall_sprites.txt", L"Textures\\BreakWall_animations.txt");
	LoadSprites(ID_TEX_INTROOBJECTS, L"Textures\\IntroObjects.png", L"Textures\\IntroObjects_sprites.txt", L"Textures\\IntroObjects_animations.txt");
	LoadSprites(ID_TEX_TITLE, L"Textures\\Title.png", L"Textures\\Title_sprites.txt", L"Textures\\Title_animations.txt");

	tilemaps->Add(SCENE_1, L"Scenes\\Scene1.png", L"Scenes\\Scene1_map.txt", 1536, 320);
	tilemaps->Add(SCENE_2, L"Scenes\\Scene2.png", L"Scenes\\Scene2_map.txt", 5632, 352);
	tilemaps->Add(SCENE_3, L"Scenes\\Scene3.png", L"Scenes\\Scene3_map.txt", 1024, 352);
}

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
	player->Update(dt, !scene->stopWatchTimer->IsTimeUp());
	scene->Update(dt);
}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// clear back buffer with background color
		// cross effect, random to render background color changed
		if (scene->crossEffectTimer->IsTimeUp() == false && rand() % 2 == 1)
			d3ddv->ColorFill(bb, NULL, BACKGROUND_CROSS_EFFECT_COLOR);
		else
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Render();

		if (scene->GetIDScene() >= 0)  // Intro screen, title screen -> not render HUD
			player->Render();

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
		MessageBox(GetActiveWindow(), L"CreateWindow failed!", L"ERROR", MB_OK);
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
	DWORD gamePlayStartTime = GetTickCount();
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
	
	LoadResources();

	scene = new SceneManager(game);
	scene->Init(TITLE_SCREEN);

	input = new Input(game, scene);
	game->InitKeyboard(input);

	player = new Player(game, scene);
	player->Init();
	
	Run();


	return 0;
}