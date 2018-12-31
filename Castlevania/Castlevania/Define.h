#pragma once

// main
#define WINDOW_CLASS_NAME		L"Castlevania"
#define MAIN_WINDOW_TITLE		L"Castlevania"

#define BACKGROUND_COLOR				D3DCOLOR_XRGB(0,0,0)
#define BACKGROUND_CROSS_EFFECT_COLOR	D3DCOLOR_XRGB(188,188,188)
#define TILEMAP_TRANSPARENT_COLOR		D3DCOLOR_XRGB(5,5,5)
#define SCREEN_WIDTH			512
#define SCREEN_HEIGHT			480

#define DEFAULT_CELL_WIDTH		256
#define DEFAULT_CELL_HEIGHT		240

#define MAX_FRAME_RATE			150

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024

// Time play
#define DEFAULT_TIME_PLAY		300

#pragma region Texture ID

#define ID_TEX_BBOX					-1
#define ID_TEX_BBOX_2				-2
#define ID_TEX_SIMON				0
#define ID_TEX_WHIP					1
#define ID_TEX_BOSS					2
#define ID_TEX_SUBWEAPONS			3
#define ID_TEX_CANDLE				4
#define ID_TEX_EFFECT				5
#define ID_TEX_SPARK				6
#define ID_TEX_BUBBLES				7
#define ID_TEX_GROUND				8
#define ID_TEX_ITEMS				9
#define ID_TEX_STAIR				10
#define ID_TEX_DOOR					11
#define ID_TEX_ZOMBIE				12
#define ID_TEX_BLACK_LEOPARD		13
#define ID_TEX_VAMPIRE_BAT			14
#define ID_TEX_FISHMAN				15
#define ID_TEX_FIREBALL				16
#define ID_TEX_HP					17
#define ID_TEX_RECT					18
#define ID_TEX_BREAKWALL			19
#define ID_TEX_INTROOBJECTS			24
#define ID_TEX_TITLE				25
//
#define ID_TEX_YESNO				20
#define ID_TEX_PAUSE				21
#define ID_TEX_TITLESCREEN			22
#define ID_TEX_INTROSCREEN			23

#pragma endregion


#pragma region Filepath

// Font
#define FILEPATH_FONT					L"Font\\prstart.ttf"

// Scenes
#define FILEPATH_OBJECTS_SCENE_1		L"Scenes\\Scene1_objects.txt"
#define FILEPATH_OBJECTS_SCENE_2		L"Scenes\\Scene2_objects.txt"
#define FILEPATH_OBJECTS_SCENE_3		L"Scenes\\Scene3_objects.txt"
#pragma endregion


#pragma region State
 
// Game
#define GAMESTATE_INTRO	-1
#define GAMESTATE_1		0   // SCENE_1
#define GAMESTATE_2_1	1	// SCENE_2 - phòng 1
#define GAMESTATE_2_2	2	// SCENE_2 - phòng 2
#define GAMESTATE_2_2_1	3	// SCENE_2 - phòng 2 - cầu thang xuống 1
#define GAMESTATE_2_2_2	4	// SCENE_2 - phòng 2 - cầu thang xuống 2
#define GAMESTATE_2_3	5	// SCENE_2 - phòng 3 (Boss)
#define GAMESTATE_3_1	6	// SCENE_3 - cầu thang lên 1
#define GAMESTATE_3_2	7	// SCENE_3 - cầu thang lên 2

// Orientation
#define DIR_LEFT		-1
#define DIR_RIGHT		1

// Collision direction
#define CDIR_LEFT		1.0f
#define CDIR_RIGHT		-1.0f
#define CDIR_TOP		1.0f
#define	CDIR_BOTTOM		-1.0f

// Scene
#define TITLE_SCREEN	-2
#define INTRO_SCREEN	-1
#define SCENE_1			0
#define SCENE_2			1
#define SCENE_3			2

// Simon
#define STAND			0
#define WALK			1
#define SIT				2
#define JUMP			3
#define HIT_SIT			4
#define HIT_STAND		5
#define POWER			6
#define STAIR_UP		7
#define STAIR_DOWN		8
#define HIT_STAIR_UP	9
#define HIT_STAIR_DOWN	10
#define	DEFLECT			11
#define DEAD			12
#define BACK			13
#define STAND_INVISIBLE				14	
#define WALK_INVISIBLE				15
#define SIT_INVISIBLE				16
#define JUMP_INVISIBLE				17
#define HIT_SIT_INVISIBLE			18
#define HIT_STAND_INVISIBLE			19
#define STAIR_UP_INVISIBLE			20
#define STAIR_DOWN_INVISIBLE		21
#define HIT_STAIR_UP_INVISIBLE		22
#define HIT_STAIR_DOWN_INVISIBLE	23

// Whip
#define NORMAL_WHIP		0
#define SHORT_CHAIN		1
#define LONG_CHAIN		2

// Candle
#define BIG_CANDLE		0
#define SMALL_CANDLE	1
#define CANDLE_DESTROYED	2

// Ground
#define GROUND_1		0
#define GROUND_2		1

// Stair
#define STAIR_LEFT_UP		0
#define STAIR_RIGHT_DOWN	1

// Items
#define	STOP_WATCH		0
#define DAGGER			1
#define	AXE				2
#define HOLY_WATER		3
#define BOOMERANG		4
#define SMALL_HEART		5
#define LARGE_HEART		6
#define CROSS			7
#define INVISIBILITY_POTION	8
#define CHAIN			9
#define MONEY_BAG_RED	10
#define MONEY_BAG_BLUE	11
#define MONEY_BAG_WHITE 12
#define MONEY_BAG_FLASHING 13
#define DOUBLE_SHOT		14
#define TRIPLE_SHOT		15
#define PORK_CHOP		16
#define MAGIC_CRYSTAL	17

// Subweapons
#define	WEAPONS_STOP_WATCH	0
#define WEAPONS_DAGGER		1
#define	WEAPONS_AXE			2
#define WEAPONS_HOLY_WATER	3
#define WEAPONS_BOOMERANG	4
#define WEAPONS_HOLY_WATER_SHATTERED	5

// Door
#define DOOR_1			0
#define DOOR_2_IDLE		1
#define DOOR_2_OPEN		2

// Enemy (chung cho Zombie, Black Leopard, Bat...)
#define ACTIVE			0
#define DESTROYED		1
#define INACTIVE		2

// Zombie
#define ZOMBIE_ACTIVE		0
#define ZOMBIE_DESTROYED	1
#define ZOMBIE_INACTIVE		2

// Black Leopard
#define BLACK_LEOPARD_ACTIVE		0    
#define BLACK_LEOPARD_DESTROYED		1
#define BLACK_LEOPARD_INACTIVE		2
#define BLACK_LEOPARD_IDLE			3
#define BLACK_LEOPARD_JUMP			4

// Vampire Bat
#define VAMPIRE_BAT_ACTIVE		0
#define VAMPIRE_BAT_DESTROYED	1
#define VAMPIRE_BAT_INACTIVE	2

// Fish man
#define FISHMAN_ACTIVE		0
#define FISHMAN_DESTROYED	1
#define FISHMAN_INACTIVE	2
#define FISHMAN_JUMP		3
#define FISHMAN_HIT			4

// Boss (Phantom Bat)
#define BOSS_ACTIVE			0
#define BOSS_DESTROYED		1
#define BOSS_INACTIVE		2

// Fire ball
#define FIREBALL			0

// Break wall
#define NORMAL				0
#define BREAK				1
#pragma endregion

#pragma region Animation 
// Animation Delay
#define SPARK_ANI_TIME_DELAY		100
#define EFFECT_ANI_TIME_DELAY		300
#define EFFECT_2_ANI_TIME_DELAY		1000
#define POWER_ANI_TIME_DELAY		450
#define STAIR_WALK_ANI_TIME_DELAY	200
#define DEFLECT_ANI_TIME_DELAY		600
#define HIT_ANI_TIME_DELAY			300
#define BACK_ANI_TIME_DELAY			3000
#define DOOR_2_OPEN_ANI_TIME_DELAY	5000
#define FISHMAN_HIT_ANI_TIME_DELAY	1000
#pragma endregion


#pragma region Properties
// Simon
#define SIMON_HP					16
#define SIMON_ENERGY				5
#define SIMON_UNTOUCHABLE_TIME		2000
#define SIMON_INVISIBILITY_TIME		4000
#define SIMON_DEAD_TIME				3000
#define SIMON_WALKING_SPEED			0.13f
#define SIMON_WALKING_SPEED_LOWER	0.05f
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_SPEED_Y_LOWER_ZONE    0.2f
#define SIMON_GRAVITY				0.002f
#define SIMON_GRAVITY_LOWER			0.001f
#define SIMON_STAIR_SPEED_X			0.079f
#define SIMON_STAIR_SPEED_Y			0.079f
#define SIMON_DEFLECT_SPEED_X		0.13f
#define SIMON_DEFLECT_SPEED_Y		0.3f

// Item
#define ITEM_FALLING_SPEED_X			0.15f
#define ITEM_FALLING_SPEED_X_VARIATION	0.01f
#define ITEM_FALLING_SPEED_Y			0.15f
#define ITEM_SMALLHEART_FALLING_SPEED_Y	0.1f
#define ITEM_TIME_DESTROYED				4000
#define ITEM_CROSS_EFFECT_TIME			500
#define ITEM_DOUBLE_SHOT_EFFECT_TIME	10000
#define ITEM_TRIPLE_SHOT_EFFECT_TIME	10000

// SubWeapons
#define WEAPONS_DAGGER_SPEED		0.3f

#define WEAPONS_AXE_SPEED_X			0.2f
#define WEAPONS_AXE_SPEED_Y			0.45f
#define WEAPONS_AXE_GRAVITY			0.001f

#define WEAPONS_HOLY_WATER_SPEED_X	0.25f
#define WEAPONS_HOLY_WATER_SPEED_Y	0.1f
#define WEAPONS_HOLY_WATER_GRAVITY	0.001f
#define WEAPONS_HOLY_WATER_TIME_EFFECT	1000

#define WEAPONS_BOOMERANG_SPEED		0.5f
#define WEAPONS_BOOMERANG_TURNBACK_SPEED	0.01f

#define WEAPONS_STOP_WATCH_TIME		2000

// Zombie
#define ZOMBIE_WALKING_SPEED		0.1f
#define ZOMBIE_GRAVITY				0.002f

// Black Leopard
#define BLACK_LEOPARD_RUNNING_SPEED_X	0.3f
#define BLACK_LEOPARD_RUNNING_SPEED_Y	0.2f
#define BLACK_LEOPARD_GRAVITY			0.001f

// Vampire Bat
#define VAMPIRE_BAT_FLYING_SPEED_X	0.12f
#define VAMPIRE_BAT_FLYING_SPEED_Y	0.1f
#define VAMPIRE_BAT_SPEED_VARIATION 0.004f

// Fish man
#define FISHMAN_JUMP_SPEED_Y		0.7f
#define FISHMAN_GRAVITY				0.0015f
#define FISHMAN_WALKING_SPEED_X		0.1f

// Boss
#define BOSS_HP						16
#define BOSS_DEFAULT_TIME_TO_FLY	1000
#define BOSS_FAST_TIME_TO_FLY		750
#define BOSS_STOP_TIME_WAITING		1500

// Fire ball
#define FIREBALL_SPEED				0.13f

// Bubbles
#define BUBBLES_GRAVITY				0.0005f
#define BUBBLES_TIME				1000

// Wall pieces
#define	WALLPIECES_GRAVITY			0.0005f
#define WALLPIECES_TIME				2000
#pragma endregion


#pragma region BBox Size

#define ENEMY_DEFAULT_BBOX_WIDTH	32
#define ENEMY_DEFAULT_BBOX_HEIGHT	32

// Simon
#define SIMON_BBOX_WIDTH			30
#define SIMON_BBOX_HEIGHT			62

// Ground
#define GROUND_BBOX_WIDTH			32
#define GROUND_BBOX_HEIGHT			32

// Candle
#define CANDLE_BBOX_WIDTH			32
#define CANDLE_BBOX_HEIGHT			64

#define SMALL_CANDLE_BBOX_WIDTH		16
#define SMALL_CANDLE_BBOX_HEIGHT	32

// Whip
#define LONG_CHAIN_BBOX_WIDTH		85
#define WHIP_BBOX_WIDTH				55
#define WHIP_BBOX_HEIGHT			15

// Stair
#define STAIR_BBOX_WIDTH			32
#define STAIR_BBOX_HEIGHT			32

// Door
#define DOOR_BBOX_WIDTH				32
#define DOOR_BBOX_HEIGHT			96

// Change Scene Object
#define CHANGE_SCENE_BBOX_WIDTH		32
#define CHANGE_SCENE_BBOX_HEIGHT	32

// Zombie
#define ZOMBIE_BBOX_WIDTH			10
#define ZOMBIE_BBOX_HEIGHT			60
#define ZOMBIE_ACTIVE_BBOX_WIDTH	200
#define ZOMBIE_ACTIVE_BBOX_HEIGHT	200

// Black Leopard
#define BLACK_LEOPARD_BBOX_WIDTH			10
#define BLACK_LEOPARD_BBOX_HEIGHT			32
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH		100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT	200

// Vampire Bat
#define VAMPIRE_BAT_BBOX_WIDTH			10
#define VAMPIRE_BAT_BBOX_HEIGHT			10
#define VAMPIRE_BAT_ACTIVE_BBOX_WIDTH	250 
#define VAMPIRE_BAT_ACTIVE_BBOX_HEIGHT	200

// Fish man
#define FISHMAN_BBOX_WIDTH			10
#define FISHMAN_BBOX_HEIGHT			60
#define FISHMAN_ACTIVE_BBOX_WIDTH	200
#define FISHMAN_ACTIVE_BBOX_HEIGHT	200

// Boss
#define BOSS_BBOX_WIDTH						70
#define BOSS_BBOX_HEIGHT					46
#define BOSS_ACTIVE_BBOX_WIDTH				50
#define BOSS_ACTIVE_BBOX_HEIGHT				400
#define BOSS_RECT_RANDOMSPOT_BBOX_WIDTH		200
#define BOSS_RECT_RANDOMSPOT_BBOX_HEIGHT	200

// Fire ball
#define FIREBALL_BBOX_WIDTH			14
#define FIREBALL_BBOX_HEIGHT		12

// Bubbles
#define BUBBLES_BBOX_WIDTH			14
#define BUBBLES_BBOX_HEIGHT			28

// SubWeapons
#define WEAPONS_HOLY_WATER_BBOX_WIDTH	32
#define WEAPONS_HOLY_WATER_BBOX_HEIGHT	26

#define WEAPONS_DAGGER_BBOX_WIDTH		34
#define WEAPONS_DAGGER_BBOX_HEIGHT		18

#define WEAPONS_AXE_BBOX_WIDTH			30
#define WEAPONS_AXE_BBOX_HEIGHT			28

#define WEAPONS_BOOMERANG_BBOX_WIDTH	28
#define WEAPONS_BOOMERANG_BBOX_HEIGHT	28

// Water
#define	WATER_BBOX_WIDTH			512
#define WATER_BBOX_HEIGHT			32
#pragma endregion

#pragma region ID objects to load from file

#define	CANDLE				0
#define	GROUND				1
#define STAIR				2
#define DOOR				3
#define ZOMBIE				4
#define BLACK_LEOPARD		5
#define VAMPIRE_BAT			6
#define FISHMAN				7
#define	BOSS				8
#define CHANGE_SCENE_OBJECT 9
#define WATER				10
#define BREAKWALL			11

#pragma endregion



