#pragma once

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"

class Whip : public GameObject
{
public:
	Whip() : GameObject() {}

	void LoadResources();
	void Update();
	void Render();

	void SetWhipPosition(D3DXVECTOR3 simonPositon, bool isStand);
	bool CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

