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
	//vector<vector<int>> map_Data;	// ma trận lưu dữ liệu map

	int map_Width;			// chiều rộng của map
	int map_Height;			// chiều cao của map

	int nums_row;			// số hàng của map
	int nums_col;			// số cột của map

	int tile_Width;			// chiều rộng một tile
	int tile_Height;		// chiều cao một tile

	LPCWSTR filePath_tex;	
	LPCWSTR filePath_data;
	int ID;					// ID của tile map, dùng để tạo class quản lí TileMaps sau này ...

public:
	vector<vector<int>> map_Data;	// ma trận lưu dữ liệu map

	Sprites * sprites;	// lưu các tile

	TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height);
	
	void LoadResources();	// load tất cả các block tile lưu vào sprites
	void Load_MapData();	// load ma trận dữ liệu map 
	void Draw(D3DXVECTOR3 camPosition);	// vẽ tất cả các tile nằm trong camera
	void Draw(int start_col, int end_col);

	int GetMapWidth() { return map_Width; }

	void abcxyz() {
		fstream fs;
		fs.open(filePath_data, ios::out);
		if (fs.fail())
		{
			DebugOut(L"TileMap::Load_MapData failed: ID=%d", ID);
			fs.close();
			return;
		}

		for (int i = 0; i < map_Data.size(); i++) {
			for (int j = 0; j < map_Data[0].size(); j++) {
				fs << map_Data[i][j] << " ";
			}
			fs << endl;
		}


		fs.close();
	}

};

typedef TileMap * LPTILEMAP;

class TileMaps
{
	static TileMaps * _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static TileMaps * GetInstance();
};
