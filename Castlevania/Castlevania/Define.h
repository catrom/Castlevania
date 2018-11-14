#pragma once

// main
#define WINDOW_CLASS_NAME		L"Castlevania"
#define MAIN_WINDOW_TITLE		L"Castlevania"

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(255,255,255)
#define SCREEN_WIDTH			512
#define SCREEN_HEIGHT			480

#define MAX_FRAME_RATE			90

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024


#pragma region Texture ID

#define ID_TEX_BBOX					-1
#define ID_TEX_SCENE_1				0
#define ID_TEX_SIMON				1
#define ID_TEX_WHIP					2
#define ID_TEX_CANDLE				3
#define ID_TEX_GROUND				4

#pragma endregion


#pragma region PathFile

#define FILEPATH_TEX_SCENE_1		L"Textures\\Scene1.png"
#define FILEPATH_DATA_SCENE_1		L"Textures\\Scene1_data.txt"
#define FILEPATH_TEX_SIMON			L"Textures\\Simon.png"
#define FILEPATH_TEX_WHIP			L"Textures\\Whip.png"
#define FILEPATH_TEX_CANDLE			L"Textures\\Candle.png"
#define FILEPATH_TEX_GROUND			L"Textures\\Ground.png"

#pragma endregion


#pragma region State
 
// Simon
#define STAND		0
#define WALK		1
#define SIT			2
#define JUMP		3
#define HIT_SIT		4
#define HIT_STAND	5

// Whip
#define NORMAL_WHIP	0

#pragma endregion


#pragma region Properties

// Simon
#define SIMON_WALKING_SPEED			0.10f
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_GRAVITY				0.03f


#pragma endregion


#pragma region BBox Size

// Simon
#define SIMON_BBOX_WIDTH			40
#define SIMON_BBOX_HEIGHT			62

// Ground
#define GROUND_BBOX_WIDTH			32
#define GROUND_BBOX_HEIGHT			32

// Candle
#define CANDLE_BBOX_WIDTH			32
#define CANDLE_BBOX_HEIGHT			64

// Whip
#define WHIP_BBOX_WIDTH				40
#define WHIP_BBOX_HEIGHT			20

#pragma endregion




