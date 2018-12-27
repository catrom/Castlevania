#pragma once

#include "GameObject.h"

class SubWeapon  : public GameObject
{
	int scoreReceived = 0;  // Điểm nhận được sau khi trúng mục tiêu
	int targetTypeHit = -1; // Loại mục tiêu đánh trúng (dùng để kiểm tra máu của boss...)

	bool isHolyWaterShattered = false;
	int holyWaterShatteredCounter = 0;

	vector<vector<float>> sparkCoord; // vector lưu toạ độ để render spark khi subweapon trúng mục tiêu
	Animation * spark = Animations::GetInstance()->Get("spark_ani");
	int startTimeRenderSpark = 0;

public:
	SubWeapon();
	~SubWeapon();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	
	void UpdateCollisionState();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	
	virtual void Render();
	void RenderSpark();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	int GetScoreReceived() { return scoreReceived; }
	int GetTargetTypeHit() { return targetTypeHit; }

	void GetCoordinateObject(LPGAMEOBJECT obj);			// Lấy toạ độ của object để lưu vào sparkCoord

	void SetScoreReceived(int x) { scoreReceived = x; }
	void SetTargetTypeHit(int x) { targetTypeHit = x; }

	void StartHolyWaterEffect() { isHolyWaterShattered = true; holyWaterShatteredCounter = GetTickCount(); }
};

