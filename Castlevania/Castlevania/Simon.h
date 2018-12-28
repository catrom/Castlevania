#pragma once

#include <vector>
#include "GameObject.h"
#include "Timer.h"

using namespace std;

class Simon : public GameObject
{
	// thuộc tính
	int score;
	int item;
	int energy;
	int life;
	int subWeapon;
	int HP;

	// auto-walk
	float autoWalkDistance = 0;		// Khoảng cách 
	int stateAfterAutoWalk = -1;	// Trạng thái sau khi auto-walk
	int nxAfterAutoWalk = 0;		// Hướng Simon sau khi auto-walk
	
public:
	Timer * untouchableTimer = new Timer(SIMON_UNTOUCHABLE_TIME);
	Timer * invisibilityTimer = new Timer(SIMON_INVISIBILITY_TIME);

	bool isDead = false;
	bool isTouchGround = false;	
	bool isFalling = false;
	bool isFallingWater = false;
	bool isStandOnStair = false;	// trạng thái đang đứng trên cầu thang 
	bool canMoveUpStair = false;	// có thể di chuyển lên cầu thang
	bool canMoveDownStair = false;	// có thể di chuyển xuống cầu thang
	bool isAutoWalk = false;		// tự động đi
	bool isWalkThroughDoor = false;	// đi qua cửa
	bool isHitSubWeapons = false;	// xác định xem là hit bằng roi hay subweapon
	bool isGotChainItem = false;	// xác định xem có nhặt được Chain item hay không, dùng để update whip
	bool isGotDoubleShotItem = false; // Double shot item
	bool isGotTripleShotItem = false; // Triple shot item
	bool isGotCrossItem = false;

	int changeScene = -1;			// lưu id Scene kế tiếp khi Simon va chạm với ChangeSceneObject

	int stairDirection = 0;			// 1: trái dưới - phải trên, -1: trái trên - phải dưới

	LPGAMEOBJECT stairCollided = nullptr; // lưu bậc thang va chạm với simon -> để xét vị trí đi tới cầu thang để lên - xuống
	
	///////

	Simon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	// Get function
	int GetEnergy() { return this->energy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetItem() { return this->item; }
	int GetSubWeapon() { return this->subWeapon; }
	int GetHP() { return this->HP; }
	
	// Properties change
	void AddScore(int x) { score += x; }
	void LoseEnergy(int x) { energy -= x; }
	void LoseHP(int x);
	void SetHP(int x) { HP = x; }
	void SetEnergy(int x) { energy = x; }
	void SetSubWeapon(int x) { subWeapon = x; }

	// Kiểm tra va chạm với danh sách bậc thang
	bool CheckCollisionWithStair(vector<LPGAMEOBJECT> * listStair);

	// Kiểm tra va chạm với danh sách item
	bool CheckCollisionWithItem(vector<LPGAMEOBJECT> * listItem);

	// Kiểm tra va chạm với vùng hoạt động của enemy
	void CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT> * listObjects);

	// Giữ cho Simon đứng yên trên bậc thang
	void StandOnStair() { vx = vy = 0; }

	// Auto-walk
	void AutoWalk(float distance, int new_state, int new_nx);
	void DoAutoWalk();

	// Xác định trạng thái đang đánh
	bool IsHit();
};


