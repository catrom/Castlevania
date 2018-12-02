#pragma once

#include "Define.h"

// Trigger object để nhận biết việc chuyển scene khi xét va chạm với Simon.
class ChangeSceneObject
{
	float x;
	float y;

	int IDNextScene;

public:
	ChangeSceneObject(float x, float y, int IDNextScene);
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetIDNextScene() { return this->IDNextScene; }
};


typedef ChangeSceneObject * LPCHANGESCENEOBJ;

