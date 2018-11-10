#include "Game.h"

Game * Game::_instance = NULL;

void Game::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT hr = DirectInput8Create(
				(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8, (VOID**)&di, NULL
				);

	if (hr != DI_OK) 
	{
		DebugOut(L"[ERROR] DirectInput8Create failed\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format
	
	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed\n");
		return;
	}

	this->keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

/*
Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
rendering 2D images
- hInst: Application instance handle
- hWnd: Application window handle
*/
void Game::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	RECT rect;
	GetClientRect(hWnd, &rect);

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = rect.bottom + 1;
	d3dpp.BackBufferWidth = rect.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		DebugOut(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	DebugOut(L"[INFO] Init Game done\n");
}

void Game::Draw(int nx, float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{
	// calculate position of object in real world
	D3DXVECTOR3 p(x - cameraPosition.x, y - cameraPosition.y, 0);

	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	// flip sprite, using nx parameter

	D3DXMATRIX oldTransform;
	D3DXMATRIX newTransform;

	spriteHandler->GetTransform(&oldTransform);

	D3DXVECTOR2 center = D3DXVECTOR2(p.x + (right - left) / 2, p.y + (bottom - top) / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(nx > 0 ? -1 : 1, 1);

	D3DXMatrixTransformation2D(&newTransform, &center, 0.0f, &rotate, NULL, 0.0f, NULL);

	D3DXMATRIX finalTransform = newTransform * oldTransform;
	spriteHandler->SetTransform(&finalTransform);

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spriteHandler->Draw(texture, &rect, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->End();
	spriteHandler->SetTransform(&oldTransform);
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

int Game::IsKeyPress(int KeyCode)
{
	return IsKeyDown(KeyCode) && !(keyEvents[KeyCode].dwData);
}

int Game::IsKeyRelease(int KeyCode)
{
	return !IsKeyDown(KeyCode) && (keyEvents[KeyCode].dwData);
}

void Game::ProcessKeyboard()
{
	HRESULT hr;

	// First, collect all key states
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);

	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back 
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK) 
			{
				DebugOut(L"[INFO] Keyboard re-acquired\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed\n");
			return;
		}
	}
	

	keyHandler->KeyState((BYTE*)&keyStates);


	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed\n");
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int keyCode = keyEvents[i].dwOfs;
		int keyState = keyEvents[i].dwData;

		if ((keyState & 0x80) > 0)
			keyHandler->OnKeyDown(keyCode);
		else
			keyHandler->OnKeyUp(keyCode);
	}
}

Game * Game::GetInstance()
{
	if (_instance == NULL) _instance = new Game();
	return _instance;
}

void Game::SetCameraPosition(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

void Game::SweptAABB(
	float ml, float mt, float mr, float mb, 
	float dx, float dy, 
	float sl, float st, 
	float sr, float sb, 
	float & t, float & nx, float & ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;		// no collision
	nx = ny = 0;

	
	//	Broad-phase test
	
	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bt > sb || bb < st)
		return;

	// moving object is not moving
	if (dx == 0 && dy == 0)
		return;

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}

	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else {
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}
