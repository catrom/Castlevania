#include "Textures.h"

Textures * Textures::_instance = NULL;

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT hr = D3DXGetImageInfoFromFile(filePath, &info);

	if (hr != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	hr = D3DXCreateTextureFromFileEx(
		d3ddv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&texture
	);

	if (hr != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}


	textures[id] = texture;
	DebugOut(L"[INFO] Load texture successfully: id=%d, path=%s \n", id, filePath);
}

Textures * Textures::GetInstance()
{
	if (_instance == NULL) _instance = new Textures();
	return _instance;
}
