#include "TileMap.h"
#include "Define.h"

TileMap::TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height)
{
	this->ID = ID;

	this->filePath_tex = filePath_tex;
	this->filePath_data = filePath_data;

	this->map_Width = map_width;
	this->map_Height = map_height;

	this->tile_Width = tile_width;
	this->tile_Height = tile_height;

	nums_row = map_Height / tile_Height;
	nums_col = map_Width / tile_Width;

	LoadResources();
	LoadMap();
	CreateZoneToDraw();
}

void TileMap::LoadResources()
{
	Textures * texture = Textures::GetInstance();

	texture->Add(ID, filePath_tex, D3DCOLOR_XRGB(255, 255, 255));
	
	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(ID);

	// lấy thông tin về kích thước của texture lưu các block tiles (filePath_tex)
	D3DSURFACE_DESC surfaceDesc;
	int level = 0; 
	texTileMap->GetLevelDesc(level, &surfaceDesc);
	
	// tính toán số hàng, số cột cần thiết để đọc các ô tile từ file
	int nums_rowToRead = surfaceDesc.Height / tile_Height;
	int nums_colToRead = surfaceDesc.Width / tile_Width;

	// thực hiện lưu danh sách các tile vô sprites theo thứ tự id_sprite
	int id_sprite = 1;

	for (UINT i = 0; i < nums_rowToRead; i++)
	{
		for (UINT j = 0; j < nums_colToRead; j++)
		{
			string idTile = "map_" + to_string(ID) + "_tile_" + to_string(id_sprite);
			sprites->Add(idTile, tile_Width * j, tile_Height * i, tile_Width * (j + 1), tile_Height * (i + 1), texTileMap);
			id_sprite = id_sprite + 1;
		}
	}
}

void TileMap::LoadMap()
{
	fstream fs;
	fs.open(filePath_data, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", ID);
		fs.close();
		return;
	}

	string line;

	while (!fs.eof())
	{
		getline(fs, line);

		// Lưu sprite tile vào vector tilemap
		vector<LPSPRITE> spriteline; 
		stringstream ss(line);
		int n;

		while (ss >> n)
		{
			string idTile = "map_" + to_string(ID) + "_tile_" + to_string(n);
			spriteline.push_back(sprites->Get(idTile));
		}

		tilemap.push_back(spriteline);
	}

	fs.close();
}

void TileMap::CreateZoneToDraw()
{
	switch (ID)
	{
	case SCENE_1:
		min_max_col_to_draw.push_back({ 0, 48 });
		break;
	case SCENE_2:
		min_max_col_to_draw.push_back({ 0, 96 });
		min_max_col_to_draw.push_back({ 96, 128 });
		min_max_col_to_draw.push_back({ 128, 176 });
		break;
	case SCENE_3:
		min_max_col_to_draw.push_back({ 0, 32 });
		break;
	default:
		break;
	}
}

void TileMap::Draw(D3DXVECTOR3 camPosition, bool isCrossEffect)
{
	int start_col_to_draw = (int)camPosition.x / 32;
	int end_col_to_draw = start_col_to_draw + SCREEN_WIDTH / 32;

	// Xét thông số blend cho hiệu ứng của item cross
	int alpha = 255;
	if (isCrossEffect == true) 
		alpha = rand() % 255;

	for (UINT i = 0; i < nums_row; i++)
	{
		for (UINT j = start_col_to_draw; j <= end_col_to_draw; j++)
		{
			// +camPosition.x để luôn giữ camera ở chính giữa, vì trong hàm Game::Draw() có trừ cho camPosition.x làm các object đều di chuyển theo
			// +(int)camPosition.x % 32 để giữ cho camera chuyển động mượt
			float x = tile_Width * (j - start_col_to_draw) + camPosition.x - (int)camPosition.x % 32; 
			float y = tile_Height * i + 80;

			tilemap[i][j]->Draw(1, -1, x, y, alpha);
		}
	}
}

TileMaps * TileMaps::_instance = NULL;

void TileMaps::Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height)
{
	LPTILEMAP tilemap = new TileMap(ID, filePath_tex, filePath_data, map_width, map_height, tile_width, tile_height);
	tilemaps[ID] = tilemap;
}

TileMaps * TileMaps::GetInstance()
{
	if (_instance == NULL) _instance = new TileMaps();
	return _instance;
}
