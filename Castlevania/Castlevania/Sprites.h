#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Game.h"
#include "Debug.h"

using namespace std;

/*
	A class contains id of a sprite and its position in texture.
*/
class Sprite
{
	string id;			// Sprite ID 
	int left, top, right, bottom;

	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(int accordingCam, int nx, float x, float y, int alpha = 255);
};

typedef Sprite * LPSPRITE;

/*
	Sprite Manager Class
*/
class Sprites
{
	static Sprites * _instance;
	unordered_map<string, LPSPRITE> sprites;		// list of Sprite Pointer by Id

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(string id) { return sprites[id]; }

	static Sprites * GetInstance();
};

/*
	Sprite Animation Frame
*/
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;				// time to render a sprite

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	
	LPSPRITE GetSprite() { return this->sprite; }
	DWORD GetTime() { return this->time; }
};

typedef AnimationFrame * LPANIMATION_FRAME;

/*
	Manage all frames of an animation
*/
class Animation
{
	DWORD animStartTime;   // mốc thời gian kể từ lúc bắt đầu render một animation
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;

public:
	
	Animation(int defaultTime = 100);

	void SetAniStartTime(DWORD t) { animStartTime = t; }
	bool IsOver(DWORD dt) { return GetTickCount() - animStartTime >= dt; }
	bool IsRenderingLastFrame() { return currentFrame == frames.size() - 1; }
	void Reset() { currentFrame = -1; }
	void SetFrame(int x) { currentFrame = x; }

	int GetCurrentFrame() { return currentFrame; }
	int GetFramesSize() { return frames.size(); }
	
	void Add(string spriteID, DWORD time = 0);
	void Render(int accordingCam, int nx, float x, float y, int alpha = 255);
	void RenderByID(int currentID, int nx, float x, float y, int alpha = 255); // hàm dùng riêng để render whip -> giải quyết bài toán đồng bộ whip cử động tay của simon
};

typedef Animation * LPANIMATION;

/*
	Manage all animations
*/
class Animations
{
	static Animations * _instance;
	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani) { animations[id] = ani; }
	LPANIMATION Get(string id) { return animations[id]; }

	static Animations* GetInstance();
};