#pragma once

// main
#define WINDOW_CLASS_NAME		L"Castlevania"
#define MAIN_WINDOW_TITLE		L"Castlevania"

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(255,255,255)
#define SCREEN_WIDTH			640
#define SCREEN_HEIGHT			480

#define MAX_FRAME_RATE			90

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024

// special texture to draw object bounding box
#define ID_TEX_BBOX				-100		

// Simon	
#define ID_TEX_SIMON				0
#define FILEPATH_TEX_SIMON			L"Textures\\Simon.png"

#define SIMON_BBOX_WIDTH			60
#define SIMON_BBOX_HEIGHT			64

#define SIMON_WALKING_SPEED			0.1f
#define SIMON_JUMP_SPEED_Y			0.8f
#define SIMON_GRAVITY				0.1f

#define SIMON_STATE_STANDING		0
#define SIMON_STATE_WALKING			100
#define SIMON_STATE_SITTING			200
#define SIMON_STATE_JUMPING			300

#define STAND		0
#define WALK		1
#define SIT			2
#define JUMP		3
#define HIT_STAND	4
#define HIT_SIT		5


