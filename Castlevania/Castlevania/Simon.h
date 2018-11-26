#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Whip.h"
#include "Candle.h"
#include "Effect.h"
#include "Ground.h"
#include "Items.h"

using namespace std;

class Simon : public GameObject
{
	Whip* whip;

	int score;
	int item;
	int energy;
	int life;
	int subWeapon;
	int HP;

public:
	bool isStand = true; // xác định trạng thái đứng/ngồi để lấy vị trí gắn roi cho phù hợp
	bool isPowered = false; // lấy item, phóng item (up + fight key)
	bool isTouchGround = false; 
	bool isStandOnStair = false; // trạng thái đang đứng trên cầu thang 
	bool isMovingUp = false;
	bool isMovingDown = false;
	int stairDirection = 0; // 1: trái dưới - phải trên, -1: trái trên - phải dưới
	

	LPGAMEOBJECT stairCollided = nullptr; // lưu bậc thang va chạm với simon -> để xét vị trí cho chuẩn trong hàm PositionCorrection

	Simon();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	
	int GetEnergy() { return this->energy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetItem() { return this->item; }
	int GetSubWeapon() { return this->subWeapon; }
	int GetHP() { return this->HP; }
	int GetStairDirection() { return this->stairDirection; }

	bool IsTouchGround() { return isTouchGround; }

	bool IsStandOnStair() { return this->isStandOnStair; }
	void SetStandOnStair(bool x) { this->isStandOnStair = x; }

	bool IsMovingUp() { return this->isMovingUp; }
	bool IsMovingDown() { return this->isMovingDown; }

	void LoseEnergy(int amount) { energy -= amount; }

	// Kiểm tra va chạm của Simon với list bậc thang
	bool CheckCollisionWithStair(vector<LPGAMEOBJECT> * listStair);
	LPGAMEOBJECT GetStairCollided() { return this->stairCollided; }
	
	// Căn chỉnh lại vị trí của Simon với bậc thang
	void PositionCorrection(int prevState = -1);  // -1 is not changed  
	// Giữ cho Simon đứng yên trên bậc thang
	void StandOnStair();
};


