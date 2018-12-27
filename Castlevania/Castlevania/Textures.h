#pragma once

#include <Windows.h>
#include <unordered_map>

#include <d3d9.h>
#include <d3dx9.h>

#include "Debug.h"
#include "Game.h"

using namespace std;

/*
	Manage texture database
*/
class Textures
{
	static Textures * _instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
	
public:
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor = D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 Get(int id) { return textures[id]; }

	static Textures * GetInstance();
};

