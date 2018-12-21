#pragma once

#include "GameObject.h"

// Trigger object để nhận biết việc chuyển scene khi xét va chạm với Simon.
class ChangeSceneObject : public GameObject
{
	int IDNextScene;

public:
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false) {}
	virtual void Render() {}

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom) {}

	void SetIDNextScene(int x) { this->IDNextScene = x; }
	int GetIDNextScene() { return this->IDNextScene; }
};

typedef ChangeSceneObject * LPCHANGESCENEOBJ;

