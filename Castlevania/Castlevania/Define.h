#pragma once

// main
#define WINDOW_CLASS_NAME		L"Castlevania"
#define MAIN_WINDOW_TITLE		L"Castlevania"

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(0,0,0)
#define SCREEN_WIDTH			512
#define SCREEN_HEIGHT			480

#define MAX_FRAME_RATE			150

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024

// Time play
#define DEFAULT_TIME_PLAY		1000

#pragma region Texture ID

#define ID_TEX_BBOX					-1
#define ID_TEX_SCENE_1				0
#define ID_TEX_SIMON				1
#define ID_TEX_WHIP					2
#define ID_TEX_CANDLE				3
#define ID_TEX_GROUND				4
#define ID_TEX_EFFECT				5
#define ID_TEX_HP					6
#define ID_TEX_RECT					7
#define ID_TEX_SMALL_CANDLE			26
#define ID_TEX_STAIR				27
#define ID_TEX_DOOR					28
#define ID_TEX_GATE					29
#define ID_TEX_ZOMBIE				30
#define ID_TEX_BLACK_LEOPARD		31
#define ID_TEX_VAMPIRE_BAT			32
#define ID_TEX_FISHMAN				33
#define ID_TEX_FIREBALL				34
#define ID_TEX_BUBBLES				35
#define ID_TEX_BOSS					36

//Items
#define ID_TEX_ITEM_STOP_WATCH		8
#define ID_TEX_ITEM_DAGGER			9
#define ID_TEX_ITEM_AXE 			10
#define ID_TEX_ITEM_HOLY_WATER		11
#define ID_TEX_ITEM_BOOMERANG		12
#define ID_TEX_ITEM_SMALL_HEART		13
#define ID_TEX_ITEM_LARGE_HEART		14
#define ID_TEX_ITEM_CROSS			15
#define ID_TEX_ITEM_INVISIBILITY_POTION		16
#define ID_TEX_ITEM_CHAIN			17
#define ID_TEX_ITEM_MONEY_BAG		18
#define ID_TEX_ITEM_DOUBLE_SHOT		19
#define ID_TEX_ITEM_TRIPLE_SHOT		20
#define ID_TEX_ITEM_PORK_CHOP		21
#define ID_TEX_ITEM_MAGIC_CRYSTAL	22
//SubWeapons
#define ID_TEX_WEAPONS_AXE			23
#define ID_TEX_WEAPONS_HOLY_WATER	24
#define ID_TEX_WEAPONS_BOOMERANG	25



#pragma endregion


#pragma region PathFile

// Font
#define FILEPATH_FONT				L"Font\\prstart.ttf"

// Objects
#define FILEPATH_TEX_BBOX			L"Textures\\BBox.png"
#define FILEPATH_TEX_SIMON			L"Textures\\Simon.png"
#define FILEPATH_TEX_WHIP			L"Textures\\Whip.png"
#define FILEPATH_TEX_CANDLE			L"Textures\\Candle.png"
#define FILEPATH_TEX_SMALL_CANDLE	L"Textures\\SmallCandle.png"
#define FILEPATH_TEX_GROUND			L"Textures\\Ground.png"
#define FILEPATH_TEX_EFFECT			L"Textures\\Effect.png"
#define FILEPATH_TEX_STAIR			L"Textures\\Stair.png"
#define FILEPATH_TEX_DOOR			L"Textures\\Door.png"
#define FILEPATH_TEX_GATE			L"Textures\\Gate.png"
#define FILEPATH_TEX_ZOMBIE			L"Textures\\Zombie.png"
#define FILEPATH_TEX_BLACK_LEOPARD	L"Textures\\BlackLeopard.png"
#define FILEPATH_TEX_VAMPIRE_BAT	L"Textures\\VampireBat.png"
#define FILEPATH_TEX_FISHMAN		L"Textures\\FishMan.png"
#define FILEPATH_TEX_FIREBALL		L"Textures\\FireBall.png"
#define FILEPATH_TEX_BUBBLES		L"Textures\\Bubbles.png"
#define FILEPATH_TEX_BOSS			L"Textures\\Boss.png"

// Items
#define FILEPATH_TEX_ITEM_STOP_WATCH			L"Textures\\Items\\Stopwatch.png"
#define FILEPATH_TEX_ITEM_DAGGER				L"Textures\\Items\\Dagger.png"
#define FILEPATH_TEX_ITEM_AXE					L"Textures\\Items\\Axe.png"
#define FILEPATH_TEX_ITEM_HOLY_WATER			L"Textures\\Items\\HolyWater.png"
#define FILEPATH_TEX_ITEM_BOOMERANG				L"Textures\\Items\\Boomerang.png"
#define FILEPATH_TEX_ITEM_SMALL_HEART			L"Textures\\Items\\SmallHeart.png"
#define FILEPATH_TEX_ITEM_LARGE_HEART			L"Textures\\Items\\LargeHeart.png"
#define FILEPATH_TEX_ITEM_CROSS					L"Textures\\Items\\Cross.png"
#define FILEPATH_TEX_ITEM_INVISIBILITY_POTION	L"Textures\\Items\\InvisibilityPotion.png"
#define FILEPATH_TEX_ITEM_CHAIN					L"Textures\\Items\\Chain.png"
#define FILEPATH_TEX_ITEM_MONEY_BAG				L"Textures\\Items\\MoneyBag.png"
#define FILEPATH_TEX_ITEM_DOUBLE_SHOT			L"Textures\\Items\\DoubleShot.png"
#define FILEPATH_TEX_ITEM_TRIPLE_SHOT			L"Textures\\Items\\TripleShot.png"
#define FILEPATH_TEX_ITEM_PORK_CHOP				L"Textures\\Items\\PorkChop.png"
#define FILEPATH_TEX_ITEM_MAGIC_CRYSTAL			L"Textures\\Items\\MagicCrystal.png"

// Sub Weapons
#define FILEPATH_TEX_WEAPONS_AXE				L"Textures\\SubWeapons\\Axe.png"
#define FILEPATH_TEX_WEAPONS_HOLY_WATER			L"Textures\\SubWeapons\\HolyWater.png"
#define FILEPATH_TEX_WEAPONS_BOOMERANG			L"Textures\\SubWeapons\\Boomerang.png"


// Scenes
#define FILEPATH_TEX_MAP_SCENE_1		L"Scenes\\Scene1.png"
#define FILEPATH_DATA_MAP_SCENE_1		L"Scenes\\Scene1_map.txt"
#define FILEPATH_OBJECTS_SCENE_1		L"Scenes\\Scene1_objects.txt"

#define FILEPATH_TEX_MAP_SCENE_2		L"Scenes\\Scene2.png"
#define FILEPATH_DATA_MAP_SCENE_2		L"Scenes\\Scene2_map.txt"
#define FILEPATH_OBJECTS_SCENE_2		L"Scenes\\Scene2_objects.txt"

#define FILEPATH_TEX_MAP_SCENE_3		L"Scenes\\Scene3.png"
#define FILEPATH_DATA_MAP_SCENE_3		L"Scenes\\Scene3_map.txt"
#define FILEPATH_OBJECTS_SCENE_3		L"Scenes\\Scene3_objects.txt"
// Player
#define FILEPATH_TEX_HP				L"Textures\\HP.png"
#define FILEPATH_TEX_RECT			L"Textures\\Rect.png"

#pragma endregion


#pragma region State
 
// Scene
#define SCENE_1		0
#define SCENE_2		1
#define SCENE_3		2

// Simon
#define STAND		0
#define WALK		1
#define SIT			2
#define JUMP		3
#define HIT_SIT		4
#define HIT_STAND	5
#define POWER		6
#define STAIR_UP	7
#define STAIR_DOWN	8
#define HIT_STAIR_UP	9
#define HIT_STAIR_DOWN	10
#define AUTO_WALK		11
#define	DEFLECT			12

// Whip
#define NORMAL_WHIP		0
#define SHORT_CHAIN		1
#define LONG_CHAIN		2

// Candle
#define BIG_CANDLE	0
#define SMALL_CANDLE	1
#define CANDLE_DESTROYED	2

// Flame Effect
#define	EFFECT		0

// Ground
#define GROUND_1	0
#define GROUND_2	1

// Stair
#define STAIR_LEFT_UP		0
#define STAIR_RIGHT_DOWN	1

// Items
#define	STOP_WATCH	 0
#define DAGGER		1
#define	AXE			2
#define HOLY_WATER	3
#define BOOMERANG	4
#define SMALL_HEART	5
#define LARGE_HEART  6
#define CROSS       7
#define INVISIBILITY_POTION	8
#define CHAIN		9
#define MONEY_BAG_RED	10
#define MONEY_BAG_BLUE	11
#define MONEY_BAG_WHITE 12
#define MONEY_BAG_FLASHING 13
#define DOUBLE_SHOT		14
#define TRIPLE_SHOT		15
#define PORK_CHOP		16
#define MAGIC_CRYSTAL	17

// Subweapons
#define	WEAPONS_STOP_WATCH	 0
#define WEAPONS_DAGGER		1
#define	WEAPONS_AXE			2
#define WEAPONS_HOLY_WATER	3
#define WEAPONS_BOOMERANG	4
#define WEAPONS_HOLY_WATER_SHATTERED	5

// Door
#define DOOR_1			0
#define DOOR_2_IDLE			1
#define DOOR_2_OPEN			2

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
#define VAMPIRE_BAT_INACTIVE		2

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

// Bubbles
#define BUBBLES				0
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
#define STAIR_UP_ANI	108
#define STAIR_DOWN_ANI	109
#define HIT_STAIR_UP_ANI	110
#define HIT_STAIR_DOWN_ANI	111
#define DEFLECT_ANI			112

// Whip
#define NORMAL_WHIP_ANI	201
#define SHORT_CHAIN_ANI	202
#define LONG_CHAIN_ANI	203

// Candle
#define BIG_CANDLE_ANI	301
#define SMALL_CANDLE_ANI	302

// Ground
#define GROUND_ANI_1	401
#define GROUND_ANI_2	402

// Flame Effect
#define	EFFECT_ANI		501

// Items
#define	STOP_WATCH_ANI				601
#define DAGGER_ANI					602
#define	AXE_ANI						603
#define HOLY_WATER_ANI				604
#define BOOMERANG_ANI				605
#define SMALL_HEART_ANI				606
#define LARGE_HEART_ANI				607
#define CROSS_ANI					608
#define INVISIBILITY_POTION_ANI		609
#define CHAIN_ANI					610
#define MONEY_BAG_RED_ANI			611
#define MONEY_BAG_BLUE_ANI			612
#define MONEY_BAG_WHITE_ANI			613
#define MONEY_BAG_FLASHING_ANI		614
#define DOUBLE_SHOT_ANI				615
#define TRIPLE_SHOT_ANI				616
#define PORK_CHOP_ANI				617
#define MAGIC_CRYSTAL_ANI			618

// SubWeapons
#define	WEAPONS_STOP_WATCH_ANI				701
#define WEAPONS_DAGGER_ANI					702
#define	WEAPONS_AXE_ANI						703
#define WEAPONS_HOLY_WATER_ANI				704
#define WEAPONS_BOOMERANG_ANI				705
#define WEAPONS_HOLY_WATER_SHATTERED_ANI	706

// Stair
#define STAIR_LEFT_UP_ANI		801
#define STAIR_RIGHT_DOWN_ANI	802

// Door
#define DOOR_1_ANI				901
#define DOOR_2_IDLE_ANI			902
#define DOOR_2_OPEN_ANI			903

// Zombie
#define ZOMBIE_ANI				1001

// Black Leopard
#define BLACK_LEOPARD_ACTIVE_ANI		1101
#define BLACK_LEOPARD_INACTIVE_ANI		1102
#define BLACK_LEOPARD_IDLE_ANI			1103
#define BLACK_LEOPARD_JUMP_ANI			1104

// Vampire Bat
#define VAMPIRE_BAT_ANI			1201

// Fish man
#define FISHMAN_ACTIVE_ANI		1301
#define FISHMAN_INACTIVE_ANI	1302
#define FISHMAN_JUMP_ANI		1303
#define FISHMAN_HIT_ANI			1304

// Boss
#define BOSS_ACTIVE_ANI			1601
#define BOSS_DESTROYED_ANI		1602
#define BOSS_INACTIVE_ANI		1603

// Fire ball
#define FIREBALL_ANI			1401

// Bubbles
#define BUBBLES_ANI				1501
#pragma endregion


#pragma region Properties

// Simon
#define SIMON_UNTOUCHABLE_TIME		2000
#define SIMON_WALKING_SPEED			0.13f
#define SIMON_WALKING_SPEED_LOWER	0.05f
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_GRAVITY				0.002f
#define SIMON_GRAVITY_LOWER			0.001f
#define SIMON_STAIR_SPEED_X			0.08f
#define SIMON_STAIR_SPEED_Y			0.08f
#define SIMON_DEFLECT_SPEED_X		0.13f
#define SIMON_DEFLECT_SPEED_Y		0.3f

// Item
#define ITEM_FALLING_SPEED			0.2f
#define ITEM_TIME_DESTROYED			3000

// SubWeapons
#define WEAPONS_DAGGER_SPEED		0.3f

#define WEAPONS_AXE_SPEED_X			0.2f
#define WEAPONS_AXE_SPEED_Y			0.5f
#define WEAPONS_AXE_GRAVITY			0.001f

#define WEAPONS_HOLY_WATER_SPEED_X	0.25f
#define WEAPONS_HOLY_WATER_SPEED_Y	0.1f
#define WEAPONS_HOLY_WATER_GRAVITY	0.001f
#define WEAPONS_HOLY_WATER_TIME_EFFECT	1000

#define WEAPONS_BOOMERANG_SPEED		0.5f
#define WEAPONS_BOOMERANG_TURNBACK_SPEED		0.01f

#define WEAPONS_STOP_WATCH_TIME		2000

// Zombie
#define ZOMBIE_WALKING_SPEED		0.1f
#define ZOMBIE_RESPAWN_TIME			5000
#define ZOMBIE_GRAVITY				0.002f

// Black Leopard
#define BLACK_LEOPARD_RUNNING_SPEED_X		0.3f
#define BLACK_LEOPARD_RUNNING_SPEED_Y		0.2f
#define BLACK_LEOPARD_GRAVITY				0.001f
#define BLACK_LEOPARD_RESPAWN_TIME			20000

// Vampire Bat
#define VAMPIRE_BAT_FLYING_SPEED_X	0.12f
#define VAMPIRE_BAT_FLYING_SPEED_Y	0.1f
#define VAMPIRE_BAT_SPEED_VARIATION 0.004f
#define VAMPIRE_BAT_RESPAWN_TIME	5000

// Fish man
#define FISHMAN_JUMP_SPEED_Y		0.7f
#define FISHMAN_GRAVITY				0.0015f
#define FISHMAN_WALKING_SPEED_X		0.1f
#define FISHMAN_RESPAWN_TIME		5000

// Boss
#define BOSS_

// Fire ball
#define FIREBALL_SPEED				0.13f

// Bubbles
#define BUBBLES_SPEED_X				0.07f
#define BUBBLES_SPEED_Y				0.1f
#define BUBBLES_SPEED_X2			0.03f
#define BUBBLES_SPEED_Y2			0.2f
#define BUBBLES_GRAVITY				0.0005f
#pragma endregion


#pragma region BBox Size

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
#define ZOMBIE_ACTIVE_BBOX_WIDTH			260
#define ZOMBIE_ACTIVE_BBOX_HEIGHT			150

// Black Leopard
#define BLACK_LEOPARD_BBOX_WIDTH			10
#define BLACK_LEOPARD_BBOX_HEIGHT			32
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH		100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT	200

// Vampire Bat
#define VAMPIRE_BAT_BBOX_WIDTH			10
#define VAMPIRE_BAT_BBOX_HEIGHT			10
#define VAMPIRE_BAT_ACTIVE_BBOX_WIDTH			400 
#define VAMPIRE_BAT_ACTIVE_BBOX_HEIGHT			200

// Fish man
#define FISHMAN_BBOX_WIDTH			10
#define FISHMAN_BBOX_HEIGHT			60
#define FISHMAN_ACTIVE_BBOX_WIDTH			200
#define FISHMAN_ACTIVE_BBOX_HEIGHT			400

// Fire ball
#define FIREBALL_BBOX_WIDTH				14
#define FIREBALL_BBOX_HEIGHT			12

// Bubbles
#define BUBBLES_BBOX_WIDTH			14
#define BUBBLES_BBOX_HEIGHT			28

// SubWeapons
#define WEAPONS_HOLY_WATER_BBOX_WIDTH			32
#define WEAPONS_HOLY_WATER_BBOX_HEIGHT			26

#define WEAPONS_DAGGER_BBOX_WIDTH			32
#define WEAPONS_DAGGER_BBOX_HEIGHT			18

#define WEAPONS_AXE_BBOX_WIDTH			30
#define WEAPONS_AXE_BBOX_HEIGHT			28

#define WEAPONS_BOOMERANG_BBOX_WIDTH			28
#define WEAPONS_BOOMERANG_BBOX_HEIGHT			28
#pragma endregion


#pragma region ID objects to load from file

#define	CANDLE		0
#define	GROUND		1
#define STAIR		2
#define DOOR		3
#define ZOMBIE		4
#define BLACK_LEOPARD	5
#define VAMPIRE_BAT		6
#define FISHMAN			7

#pragma endregion



