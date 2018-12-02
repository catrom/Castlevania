#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

#include "Debug.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;


class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;


struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
public:
	float x;		// coordinate
	float y;

	float dx;		// distance
	float dy;

	float vx;		// velocity
	float vy;	

	int nx;			// orientation (left / right)

	int state;		// state of object

	DWORD dt;

	bool isEnable;
	int idItem;		// id của item mà object đó chứa (-1: no item)

	bool isRenderAnimation;

	vector<LPANIMATION> animations;


	GameObject();
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) = 0;

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void SetState(int state) { this->state = state; }
	void SetOrientation(int nx) { this->nx = nx; }
	void SetIDItem(int id) { this->idItem = id; }
	void SetEnable(bool enable) { this->isEnable = enable; }

	bool GetIsRenderAnimation() { return this->isRenderAnimation; }
	void SetIsRenderAnimation(bool x) { this->isRenderAnimation = x; }

	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }
	int GetOrientation() { return this->nx; }
	bool IsEnable() { return this->isEnable; }

	void RenderBoundingBox();
	
	// check collision of 2 static object (ex: whip and candle)
	bool AABB(
		float left_a, float top_a, float right_a, float bottom_a,
		float left_b, float top_b, float right_b, float bottom_b
	);

	void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st,
		float sr, float sb,
		float & t, float & nx, float & ny);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniID);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void Render() = 0;
};

