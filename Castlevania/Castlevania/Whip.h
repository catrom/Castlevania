#pragma once

#include "GameObject.h"

class Whip : public GameObject
{
	int scoreReceived = 0;  // Điểm nhận được sau khi trúng mục tiêu
	int targetTypeHit = -1; // Loại mục tiêu đánh trúng (dùng để kiểm tra máu của boss...)

public:
	Whip();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL, bool stopMovement = false);
	virtual void Render() {}
	void Render(int currentID);

	void SetWhipPosition(D3DXVECTOR3 simonPositon, bool isStand);
	bool CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	void PowerUp();

	int GetScoreReceived() { return scoreReceived; }
	int GetTargetTypeHit() { return targetTypeHit; }

	void SetScoreReceived(int x) { scoreReceived = x; }
	void SetTargetTypeHit(int x) { targetTypeHit = x; }
};

