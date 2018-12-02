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
#define HIT			6  // subweapon, no need whip
#define POWER		7
#define STAIR_UP	8
#define STAIR_DOWN	9
#define HIT_STAIR_UP	10
#define HIT_STAIR_DOWN	11
#define AUTO_WALK		12
#define	DEFLECT			13

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

// Door
#define DOOR_1			0
#define DOOR_2_IDLE			1
#define DOOR_2_OPEN			2

// Zombie
#define ZOMBIE		0
#define ZOMBIE_DESTROYED	1

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

// Stair
#define STAIR_LEFT_UP_ANI		801
#define STAIR_RIGHT_DOWN_ANI	802

// Door
#define DOOR_1_ANI				901
#define DOOR_2_IDLE_ANI			902
#define DOOR_2_OPEN_ANI			903

// Zombie
#define ZOMBIE_ANI				1001
#pragma endregion


#pragma region Properties

// Simon
#define SIMON_UNTOUCHABLE_TIME		3000
#define SIMON_WALKING_SPEED			0.15f
#define SIMON_WALKING_SPEED_LOWER	0.05f
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_GRAVITY				0.002f
#define SIMON_GRAVITY_LOWER			0.001f
#define SIMON_STAIR_SPEED_X			0.08f
#define SIMON_STAIR_SPEED_Y			0.08f
#define SIMON_DEFLECT_SPEED_X		0.15f
#define SIMON_DEFLECT_SPEED_Y		0.3f


// Item
#define ITEM_FALLING_SPEED			0.2f
#define ITEM_TIME_DESTROYED			5000

// SubWeapons
#define WEAPONS_DAGGER_SPEED		0.3f

#define WEAPONS_AXE_SPEED_X			0.2f
#define WEAPONS_AXE_SPEED_Y			0.5f

#define WEAPONS_HOLY_WATER_SPEED_X	0.25f
#define WEAPONS_HOLY_WATER_SPEED_Y	0.1f

#define WEAPONS_BOOMERANG_SPEED		0.5f

// Zombie
#define ZOMBIE_WALKING_SPEED		0.1f
#pragma endregion


#pragma region BBox Size

// Simon
#define SIMON_BBOX_WIDTH			34
#define SIMON_BBOX_HEIGHT			62
#define SIMON_JUMPING_BBOX_HEIGHT	62

// Ground
#define GROUND_BBOX_WIDTH			32
#define GROUND_BBOX_HEIGHT			32

// Candle
#define CANDLE_BBOX_WIDTH			32
#define CANDLE_BBOX_HEIGHT			64

#define SMALL_CANDLE_BBOX_WIDTH		16
#define SMALL_CANDLE_BBOX_HEIGHT	32

// Whip
#define LONG_CHAIN_BBOX_WIDTH		80
#define WHIP_BBOX_WIDTH				50
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
#define ZOMBIE_BBOX_WIDTH			32
#define ZOMBIE_BBOX_HEIGHT			64
#pragma endregion


#pragma region ID objects to load from file

#define	CANDLE		0
#define	GROUND		1
#define STAIR		2
#define DOOR		3

#pragma endregion



