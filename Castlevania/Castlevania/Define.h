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
#define ID_TEX_EFFECT				5
#define ID_TEX_ITEM_LARGE_HEART		6
#define ID_TEX_ITEM_CHAIN			7
#define ID_TEX_ITEM_DAGGER			8

#pragma endregion


#pragma region PathFile

#define FILEPATH_TEX_SCENE_1		L"Textures\\Scene1.png"
#define FILEPATH_DATA_SCENE_1		L"Textures\\Scene1_data.txt"
#define FILEPATH_TEX_SIMON			L"Textures\\Simon.png"
#define FILEPATH_TEX_WHIP			L"Textures\\Whip.png"
#define FILEPATH_TEX_CANDLE			L"Textures\\Candle.png"
#define FILEPATH_TEX_GROUND			L"Textures\\Ground.png"
#define FILEPATH_TEX_EFFECT			L"Textures\\Effect.png"
#define FILEPATH_TEX_ITEM_LARGE_HEART			L"Textures\\Items\\Large Heart.png"
#define FILEPATH_TEX_ITEM_CHAIN					L"Textures\\Items\\Chain.png"
#define FILEPATH_TEX_ITEM_DAGGER				L"Textures\\Items\\Dagger.png"


#pragma endregion


#pragma region State
 
// Simon
#define STAND		0
#define WALK		1
#define SIT			2
#define JUMP		3
#define HIT_SIT		4
#define HIT_STAND	5
#define HIT			6  // dagger, no need whip
#define POWER		7

// Whip
#define NORMAL_WHIP		0
#define SHORT_CHAIN		1
#define LONG_CHAIN		2

// Candle
#define BIG_CANDLE	0
#define DESTROYED	1

// Ground
#define GROUND		0

// Flame Effect
#define	EFFECT		0

// Items
#define	LARGE_HEART 0
#define CHAIN		1
#define	DAGGER		2

// Dagger
#define DAGGER_STATE 0

#pragma endregion

#pragma region Animation ID

// Simon
#define STAND_ANI		101
#define WALK_ANI		102
#define SIT_ANI			103
#define JUMP_ANI		104
#define HIT_SIT_ANI		105
#define HIT_STAND_ANI	106
#define POWER_ANI		107

// Whip
#define NORMAL_WHIP_ANI	201
#define SHORT_CHAIN_ANI	202
#define LONG_CHAIN_ANI	203

// Candle
#define BIG_CANDLE_ANI	301

// Ground
#define GROUND_ANI		401

// Flame Effect
#define	EFFECT_ANI		501

// Items
#define	LARGE_HEART_ANI 601
#define CHAIN_ANI		701
#define	DAGGER_ANI		801

#pragma endregion


#pragma region Properties

// Simon
#define SIMON_WALKING_SPEED			0.10f
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_GRAVITY				0.002f
#define SIMON_GRAVITY_LOWER			0.001f

// Item
#define ITEM_FALLING_SPEED			0.2f
#define ITEM_TIME_DESTROYED			5000
#define ITEM_DAGGER_SPEED			0.3f

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
#define WHIP_BBOX_HEIGHT			10

// Large Heart
#define LARGE_HEART_BBOX_WIDTH		24
#define LARGE_HEART_BBOX_HEIGHT		20

// Chain
#define CHAIN_BBOX_WIDTH			32
#define CHAIN_BBOX_HEIGHT			32

// Dagger
#define DAGGER_BBOX_WIDTH			32
#define DAGGER_BBOX_HEIGHT			18
#pragma endregion




