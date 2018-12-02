#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Define.h"
#include "Debug.h"

class KeyEventHandler;
class Game;

typedef KeyEventHandler * LPKEYEVENTHANDLER;


/*
Abstract class to define keyboard event handlers
*/
class KeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

class Game
{
	static Game* _instance;
	HWND hWnd;							// window handle

	LPDIRECT3D9 d3d = NULL;				// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;		// Direct3d device object handle

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;	// sprite helper library

	LPDIRECTINPUT8			di;			// the DirectInput object
	LPDIRECTINPUTDEVICE8	didv;		// the keyboard device

	BYTE keyStates[256];				// DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];	// buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	D3DXVECTOR3 cameraPosition;			// camera position for viewing

public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Init(HWND hWnd);
	void Draw(int accordingCam, int nx, float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	// accordingCam: render theo camera hay là không
	// 0 : no, 1 : yes																																					

	int IsKeyDown(int KeyCode);
	int IsKeyPress(int KeyCode);
	int IsKeyRelease(int KeyCode);

	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	D3DXVECTOR3 GetCameraPositon() { return this->cameraPosition; }
	
	static Game* GetInstance();

	void SetCameraPosition(float x, float y);
	


	~Game();
};

