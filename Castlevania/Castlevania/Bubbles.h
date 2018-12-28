#pragma once

#include <vector>
#include "GameObject.h"

class Bubble : public GameObject
{
public:
	Bubble();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

typedef Bubble * LPBUBBLE;

// Vì mỗi cụm có 3 Bubble nên tạo class Bubbles để quản lí
class Bubbles
{
	DWORD startTime = 0;

public:
	vector<LPBUBBLE> bubbles;
	Bubbles(float x, float y);
	~Bubbles();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	DWORD GetStartTimeRender() { return startTime; }
	void SetStartTimeRender(DWORD x) { startTime = x; }
};

