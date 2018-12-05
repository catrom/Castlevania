#pragma once

#include <vector>
#include "GameObject.h"

class Bubble : public GameObject
{
public:
	Bubble();
	~Bubble();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

typedef Bubble * LPBUBBLE;

// Vì mỗi cụm có 3 Bubble nên tạo class Bubbles để quản lí
class Bubbles
{
	

public:
	vector<LPBUBBLE> bubbles;
	Bubbles(float x, float y);
	~Bubbles();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

};

