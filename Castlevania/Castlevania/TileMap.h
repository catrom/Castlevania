#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"

using namespace std;

class TileMap
{
	vector<vector<int>> map_Data;	// ma trận lưu dữ liệu map

	int map_Width;					// chiều rộng của map
	int map_Height;					// chiều cao của map

	int nums_row;					// số hàng của map
	int nums_col;					// số cột của map

	int tile_Width;					// chiều rộng một tile
	int tile_Height;				// chiều cao một tile

	LPCWSTR filePath_tex;			// filepath texture (chứa các ô tile)
	LPCWSTR filePath_data;			// filepath data (chứa ma trận map)

	int ID;							// ID của tile map, dùng để tạo class quản lí TileMaps sau này.

public:
	Sprites * sprites = Sprites::GetInstance();

	vector<vector<int>> min_max_col_to_draw; // khoảng giới hạn để vẽ tilemap (trong lâu đài)
	int index = 0;							 // index hiện tại của min_max_col_to_draw

	TileMap() {}
	TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width = TILEMAP_DEFAULT_CELL_WIDTH, int tile_height = TILEMAP_DEFAULT_CELL_HEIGHT);
	
	void LoadResources();			// load tất cả các ô tile lưu vào sprites
	void Load_MapData();			// load ma trận dữ liệu map 
	void CreateZoneToDraw();		// khởi tạo vector 2 chiều min_max_col_to_draw
	void Draw(D3DXVECTOR3 camPosition, bool isCrossEffect = false);	// vẽ tất cả các tile nằm trong camera

	int GetMapWidth() { return map_Width; }
};

typedef TileMap * LPTILEMAP;

/*
	Class quản lí danh sách các Tilemap
*/
class TileMaps
{
	static TileMaps * _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width = TILEMAP_DEFAULT_CELL_WIDTH, int tile_height = TILEMAP_DEFAULT_CELL_HEIGHT);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static TileMaps * GetInstance();
};
