#pragma once

#include <vector>
#include "GameObject.h"

class Unit 
{
	friend class Grid;

private:
	Grid * grid;
	LPGAMEOBJECT obj;
	float x;
	float y;
	
	Unit * prev;
	Unit * next;

public:
	Unit(Grid * grid, LPGAMEOBJECT obj, float x, float y);

	void Move(float x, float y);
	LPGAMEOBJECT GetObj() { return this->obj; }
};

class Grid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int nums_col;
	int nums_row;

	vector<vector<Unit*>> cells;

public:
	Grid(int map_width, int map_height, int cell_width = DEFAULT_CELL_WIDTH, int cell_height = DEFAULT_CELL_HEIGHT);
	~Grid();

	void Add(Unit * unit);
	void Move(Unit * unit, float x, float y); // x, y là toạ độ mới của unit, vì vậy lúc này x, y của unit lưu vị trí cũ
	void Get(D3DXVECTOR3 camPosition, vector<Unit*>& listUnits); // lấy tất cả các Unit* nằm trong vùng viewport để Update và Render

	void Out();
};

