#pragma once

#include "GameObject.h"

class Items : public GameObject
{
	DWORD timeAppear;   // thời gian bắt đầu xuất hiện của item, dùng để xét cho item tự huỷ
	float velocityVariation_x;	// biến thiên vận tốc theo chiều x để cho smallheart bay lảo đảo
public:
	Items();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
};

