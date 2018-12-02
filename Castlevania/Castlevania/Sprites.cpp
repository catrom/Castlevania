#include "Sprites.h"


Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void Sprite::Draw(int accordingCam, int nx, float x, float y, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(accordingCam, nx, x, y, texture, left, top, right, bottom, alpha);
}


Sprites * Sprites::_instance = NULL;

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = sprite;
}

Sprites * Sprites::GetInstance()
{
	if (_instance == NULL) _instance = new Sprites();
	return _instance;
}


Animation::Animation(int defaultTime)
{
	this->defaultTime = defaultTime;
	lastFrameTime = -1;
	currentFrame = -1;
}

void Animation::Add(int spriteID, DWORD time)
{
	if (time == 0) time = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteID);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, time);
	frames.push_back(frame);
}

void Animation::Render(int accordingCam, int nx, float x, float y, int alpha)
{
	DWORD now = GetTickCount();

	if (currentFrame == -1) 
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime >= t) {
			currentFrame++;
			lastFrameTime = now;

			if (currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
		}
	}

	frames[currentFrame]->GetSprite()->Draw(accordingCam, nx, x, y, alpha);
}

void Animation::RenderByID(int currentID, int nx, float x, float y, int alpha)
{
	if (frames.size() <= 5) // normal whip, short chain
	{
		frames[currentID]->GetSprite()->Draw(1, nx, x, y, alpha);
	}
	else  // == 12, long chain
	{
		int rd = rand() % 4;

		frames[currentID * 4 + rd]->GetSprite()->Draw(1, nx, x, y, alpha);
	}
}


Animations * Animations::_instance = NULL;

Animations * Animations::GetInstance()
{
	if (_instance == NULL) _instance = new Animations();
	return _instance;
}
