#include "SceneManager.h"


SceneManager::SceneManager(Game * game, int idScene)
{
	this->game = game;
	IDScene = idScene;
}


SceneManager::~SceneManager()
{
}

void SceneManager::LoadResources()
{
	simon = new Simon();
	simon->LoadResources(textures, sprites, animations);

	candle = new Candle();
	candle->LoadResources(textures, sprites, animations);

	effect = new Effect();
	effect->LoadResources(textures, sprites, animations);

	ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	item = new Items();
	item->LoadResources(textures, sprites, animations);

	whip = new Whip();
	whip->LoadResources(textures, sprites, animations);

	
	tilemaps->Add(SCENE_1, FILEPATH_TEX_MAP_SCENE_1, FILEPATH_DATA_MAP_SCENE_1, 1536, 320, 32, 32);
	tilemaps->Add(SCENE_2, FILEPATH_TEX_MAP_SCENE_2, FILEPATH_DATA_MAP_SCENE_2, 2880, 352, 32, 32);

	textures->Add(ID_TEX_BBOX, FILEPATH_TEX_BBOX, D3DCOLOR_XRGB(255, 255, 255));
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	Objects.clear();

	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		DebugOut(L"[INFO] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}

	simon = new Simon();
	simon->SetPosition(0.0f, 220.0f);
	Objects.push_back(simon);

	dagger = new Dagger();
	dagger->isEnable = false;
	Objects.push_back(dagger);

	int ID_Obj;
	float pos_x, pos_y;
	int state;
	bool isEnable;
	int idItem;

	while (!fs.eof())
	{
		fs >> ID_Obj >> pos_x >> pos_y >> state >> isEnable >> idItem;

		switch (ID_Obj)
		{
		case CANDLE:
			candle = new Candle();
			candle->SetPosition(pos_x, pos_y);
			candle->SetState(state);
			candle->SetEnable(isEnable);
			candle->SetIDItem(idItem);
			Objects.push_back(candle);
			break;
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			Objects.push_back(ground);
			break;
		default:
			break;
		}
	}

	fs.close();
}

void SceneManager::Update(DWORD dt)
{
	float pos_x, pos_y;
	simon->GetPosition(pos_x, pos_y);
	
	//DebugOut(L"%f %f\n", pos_x, pos_y);

	if (IDScene == SCENE_1 && pos_x >= 1450.0f)
	{
		ChangeScene(SCENE_2);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}

	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->isEnable == false)
			continue;

		vector<LPGAMEOBJECT> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects

		if (dynamic_cast<Simon*>(Objects[i]))
		{
			for (int j = 0; j < Objects.size(); j++)
			{
				if (Objects[j]->isEnable == false)
					continue;

				if (i != j) // thêm tất cả objects "ko phải là simon", dùng trong hàm update của simon 
					coObjects.push_back(Objects[j]);
			}
		}
		else if (dynamic_cast<Items*>(Objects[i]))
		{
			for (int j = 0; j < Objects.size(); j++)
			{
				if (Objects[i]->isEnable == false)
					continue;

				if (dynamic_cast<Ground*>(Objects[j])) // thêm tất cả objects "là ground", dùng trong hàm update của item
				{
					coObjects.push_back(Objects[j]);
				}
			}
		}
		else
		{
			coObjects.push_back(Objects[i]);
		}


		Objects[i]->Update(dt, &Objects, &coObjects);
	}

	// render camera
	float cx, cy;
	simon->GetPosition(cx, cy);

	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
		game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon());

	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->isEnable == false)
			continue;

		Objects[i]->Render();
		Objects[i]->RenderBoundingBox();
	}
}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case SCENE_1:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		break;
	case SCENE_2:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		break;
	default:
		break;
	}
}
