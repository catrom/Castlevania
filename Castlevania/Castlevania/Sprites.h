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
	int id;			// Sprite ID 
	int left, top, right, bottom;

	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(int nx, float x, float y, int alpha = 255);
};

typedef Sprite * LPSPRITE;

/*
	Sprite Manager Class
*/
class Sprites
{
	static Sprites * _instance;
	unordered_map<int, LPSPRITE> sprites;		// list of Sprite Pointer by Id

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id) { return sprites[id]; }

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
	DWORD animStartTime;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;

	bool isOverAnimation = false;

public:

	Animation(int defaultTime = 100);

	void setAniStartTime(DWORD t) { animStartTime = t; }
	bool IsOver(DWORD dt) { /*return currentFrame == frames.size() - 1;*/ return GetTickCount() - animStartTime >= dt; }
	void Reset() { /*isOverAnimation = false;*/ currentFrame = -1; }

	int GetCurrentFrame() { return currentFrame; }
	int GetFramesSize() { return frames.size(); }
	
	void Add(int spriteID, DWORD time = 0);
	void Render(int nx, float x, float y, int alpha = 255);
};

typedef Animation * LPANIMATION;

/*
	Manage all animations
*/
class Animations
{
	static Animations * _instance;
	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani) { animations[id] = ani; }
	LPANIMATION Get(int id) { return animations[id]; }

	static Animations* GetInstance();
};