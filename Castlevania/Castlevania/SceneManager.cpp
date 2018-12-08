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
	simon->LoadResources(textures, sprites, animations);
	candle->LoadResources(textures, sprites, animations);
	effect->LoadResources(textures, sprites, animations);
	ground->LoadResources(textures, sprites, animations);
	item->LoadResources(textures, sprites, animations);
	whip->LoadResources(textures, sprites, animations);
	weapon->LoadResources(textures, sprites, animations);
	stair->LoadResources(textures, sprites, animations);
	door->LoadResources(textures, sprites, animations);
	zombie->LoadResources(textures, sprites, animations);
	leopard->LoadResources(textures, sprites, animations);
	bat->LoadResources(textures, sprites, animations);
	fishman->LoadResources(textures, sprites, animations);
	fireball->LoadResources(textures, sprites, animations);
	bubble->LoadResources(textures, sprites, animations);
	boss->LoadResources(textures, sprites, animations);

	tilemaps->Add(SCENE_1, FILEPATH_TEX_MAP_SCENE_1, FILEPATH_DATA_MAP_SCENE_1, 1536, 320, 32, 32);
	tilemaps->Add(SCENE_2, FILEPATH_TEX_MAP_SCENE_2, FILEPATH_DATA_MAP_SCENE_2, 5632, 352, 32, 32);
	tilemaps->Add(SCENE_3, FILEPATH_TEX_MAP_SCENE_3, FILEPATH_DATA_MAP_SCENE_3, 1024, 352, 32, 32);

	tilemaps->Get(SCENE_2)->index = 2;

	textures->Add(ID_TEX_BBOX, FILEPATH_TEX_BBOX, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BBOX_2, FILEPATH_TEX_BBOX_2, D3DCOLOR_XRGB(255, 255, 255));

	simon = new Simon();
	weapon = new SubWeapon();
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	Objects.clear();
	listCandles.clear();
	listStairs.clear();
	listGrounds.clear();
	listItems.clear();
	listDoors.clear();
	listZombies.clear();
	listBlackLeopards.clear();
	listVampireBats.clear();
	listFishMans.clear();
	listFireBalls.clear();

	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		DebugOut(L"[ERROR] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}


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
			listCandles.push_back(candle);
			Objects.push_back(candle);
			break;
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			listGrounds.push_back(ground);
			Objects.push_back(ground);
			break;
		case STAIR:
			stair = new Stair();
			stair->SetPosition(pos_x, pos_y);
			stair->SetState(state);
			stair->SetEnable(isEnable);
			stair->SetIDItem(idItem);
			listStairs.push_back(stair);
			Objects.push_back(stair);
			break;
		case DOOR:
			door = new Door();
			door->SetPosition(pos_x, pos_y);
			door->SetState(state);
			door->SetEnable(isEnable);
			door->SetIDItem(idItem);
			listDoors.push_back(door);
			Objects.push_back(door);
			break;
		case ZOMBIE:
			zombie = new Zombie();
			zombie->SetEntryPosition(pos_x, pos_y);
			zombie->SetState(ZOMBIE_INACTIVE);
			zombie->SetEnable(isEnable);
			zombie->SetIDItem(idItem);
			listZombies.push_back(zombie);
			Objects.push_back(zombie);
			break;
		case BLACK_LEOPARD:
			leopard = new BlackLeopard();
			leopard->SetEntryPosition(pos_x, pos_y);
			leopard->SetPosition(pos_x, pos_y);
			leopard->SetState(state);
			leopard->SetIsRespawnWaiting(false);
			leopard->SetEnable(true);
			listBlackLeopards.push_back(leopard);
			Objects.push_back(leopard);
			break;
		case VAMPIRE_BAT:
			bat = new VampireBat();
			bat->SetEntryPosition(pos_x, pos_y);
			bat->SetState(VAMPIRE_BAT_INACTIVE);
			bat->SetEnable(true);
			bat->SetIDItem(idItem);
			listVampireBats.push_back(bat);
			Objects.push_back(bat);
			break;
		case FISHMAN:
			fishman = new FishMan();
			fishman->SetEntryPosition(pos_x, pos_y);
			fishman->SetState(FISHMAN_INACTIVE);
			fishman->SetEnable(true);
			fishman->SetIDItem(idItem);
			listFishMans.push_back(fishman);
			Objects.push_back(fishman);
			break;
		case BOSS:
			boss = new Boss();
			boss->SetEntryPosition(pos_x, pos_y);
			boss->SetPosition(pos_x, pos_y);
			boss->SetState(BOSS_INACTIVE);
			boss->SetEnable(true);
			boss->SetIDItem(idItem);
			Objects.push_back(boss);
			break;
		default:
			break;
		}
	}

	fs.close();

	// Simon
	Objects.push_back(simon);

	// Subweapons
	weapon->SetEnable(false);
	Objects.push_back(weapon);

	// Whip
	whip = new Whip();
	Objects.push_back(whip);
}

void SceneManager::CreateListChangeSceneObjects()
{
	listChangeSceneObjs.clear();

	switch (IDScene)
	{
	case SCENE_1:
		changeScene = new ChangeSceneObject(1440, 336, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		break;
	case SCENE_2:
		changeScene = new ChangeSceneObject(3168, 432, SCENE_3);
		listChangeSceneObjs.push_back(changeScene);
		changeScene = new ChangeSceneObject(3808, 432, SCENE_3);
		listChangeSceneObjs.push_back(changeScene);
		break;
	case SCENE_3:
		changeScene = new ChangeSceneObject(96, 80, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		changeScene = new ChangeSceneObject(736, 80, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		break;
	default:
		break;
	}
}

void SceneManager::Update(DWORD dt)
{
	// Cập nhật trạng thái Simon đi qua cửa:
	// Di chuyển Camera -> Mở cửa -> AutoWalk -> Di chuyển Camera

	if (simon->isWalkThroughDoor == true)
	{
		isMovingCamera = true;
		countDxCamera = 0;

		simon->isWalkThroughDoor = false;
	}

	if (isMovingCamera == true)
	{
		if (countDxCamera < 224)	// Di chuyển camera một đoạn 224
		{
			D3DXVECTOR3 cam = game->GetCameraPositon();
			game->SetCameraPosition(cam.x + 2, cam.y);
			countDxCamera += 2;

			return;
		}

		if (isSetSimonAutoWalk == false)  // AutoWalk
		{
			isSetSimonAutoWalk = true;

			simon->SetState(WALK);
			simon->vy = 0;
			simon->AutoWalk(120, STAND, 1);
		}
		else
		{
			if (simon->IsAutoWalk() == false)
			{
				if (countDxCamera < 480) // Di chuyển camera thêm một đoạn nữa
				{
					D3DXVECTOR3 cam = game->GetCameraPositon();
					game->SetCameraPosition(cam.x + 2, cam.y);
					countDxCamera += 2;

					return;
				}
				else
				{
					isMovingCamera = false;
					isSetSimonAutoWalk = false;
					countDxCamera = 0;

					tilemaps->Get(IDScene)->index += 1;  // tăng giới hạn của tilemap
				}
			}
		}
	}

	// Khi Simon va chạm với ChangScene objects, tiến hành thay đổi, cập nhật trạng thái

	if (simon->GetChangeScene() != -1)
	{
		if (IDScene == SCENE_1 ||
			(IDScene == SCENE_2 && simon->GetState() == STAIR_DOWN) ||
			(IDScene == SCENE_3 && simon->GetState() == STAIR_UP))
		{
			bool isNeedToUpdatePosition = false;

			if (IDScene != SCENE_1) isNeedToUpdatePosition = true;

			float x, y;
			simon->GetPosition(x, y);

			//DebugOut(L"%f %f \n", x, y);

			IDScene = simon->GetChangeScene();
			ChangeScene(IDScene);

			if (isNeedToUpdatePosition == true)
			{
				switch (IDScene)
				{
				case SCENE_3:
					if (x < 3200.0f) simon->SetPosition(100.0f, 48.0f);
					else simon->SetPosition(740.0f, 48.0f);

					tilemaps->Get(IDScene)->index = 0;
					game->SetCameraPosition(0.0f, 0.0f);
					break;
				case SCENE_2:
					if (x < 320.0f) simon->SetPosition(3136.0f, 335.0f);
					else simon->SetPosition(3776.0f, 335.0f);

					simon->SetState(STAND);
					tilemaps->Get(IDScene)->index = 1;
					game->SetCameraPosition(3056.0f, 0.0f);
					break;
				default:
					break;
				}
			}

			simon->SetChangeScene(-1);
		}
		else
		{
			simon->SetChangeScene(-1);
		}
	}

	// Cập nhật trạng thái hoạt động khi object đi ra khỏi viewport

	SetInactivationByPosition();

	// Stop Watch
	if (isUsingStopWatch == true && GetTickCount() - stopWatchCounter > WEAPONS_STOP_WATCH_TIME)
	{
		isUsingStopWatch = false;
		stopWatchCounter = 0;
	}

	// Cập nhật danh sách Objects theo delta time

	for (UINT i = 0; i < Objects.size(); i++)
	{
		LPGAMEOBJECT object = Objects[i];

		// Drop item cho các object bị huỷ

		SetDropItems(object); 


		vector<LPGAMEOBJECT> coObjects;

		if (dynamic_cast<Simon*>(object))
		{
			/*if (isBossFighting == true)
				coObjects.push_back(boss);*/

			coObjects.push_back(boss);

			for (auto candle : listCandles)
			{
				if (candle->IsEnable() == false)
					continue;

				coObjects.push_back(candle);
			}

			for (auto ground : listGrounds)
			{
				if (ground->IsEnable() == false)
					continue;

				coObjects.push_back(ground);
			}

			for (auto zombie : listZombies)
			{
				if (zombie->GetState() == ZOMBIE_INACTIVE)
					continue;

				coObjects.push_back(zombie);
			}

			for (auto leopard : listBlackLeopards)
			{
				if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
					continue;

				coObjects.push_back(leopard);
			}

			for (auto bat : listVampireBats)
			{
				if (bat->GetState() == VAMPIRE_BAT_INACTIVE)
					continue;

				coObjects.push_back(bat);
			}

			for (auto fishman : listFishMans)
			{
				if (fishman->GetState() == FISHMAN_INACTIVE)
					continue;

				coObjects.push_back(fishman);
			}

			for (auto fireball : listFireBalls)
			{
				if (fireball->IsEnable() == false)
					continue;

				coObjects.push_back(fireball);
			}

			for (auto door : listDoors)
			{
				if (door->IsEnable() == false)
					continue;

				coObjects.push_back(door);
			}


			simon->Update(dt, &Objects, &coObjects);
			simon->CheckCollisionWithItem(&listItems);
			simon->CheckChangeScene(&listChangeSceneObjs);
			simon->CheckCollisionWithEnemyActiveArea(&listZombies);
			simon->CheckCollisionWithEnemyActiveArea(&listBlackLeopards);
			simon->CheckCollisionWithEnemyActiveArea(&listVampireBats);
			simon->CheckCollisionWithEnemyActiveArea(&listFishMans);
			simon->CheckCollisionWithEnemyActiveArea(&coObjects);
		}
		else if (dynamic_cast<Items*>(object))
		{
			object->Update(dt, &Objects, &listGrounds);
		}
		else if (dynamic_cast<Whip*>(object))
		{
			if (simon->IsGotChainItem() == true) // update trạng thái của whip
			{
				simon->SetGotChainItem(false);
				whip->PowerUp();
			}

			// lấy vị trí và phương của simon cho whip
			float simon_x, simon_y;
			simon->GetPosition(simon_x, simon_y);

			whip->SetOrientation(simon->GetOrientation());
			whip->SetWhipPosition(D3DXVECTOR3(simon_x, simon_y, 0), simon->IsStand());

			// chỉ xét va chạm khi render tới sprite cuối cùng của simon (vung tay tới)
			if ((simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT ||
				simon->GetState() == HIT_STAIR_UP || simon->GetState() == HIT_STAIR_DOWN) &&
				simon->animations[simon->GetState()]->IsRenderingLastFrame() == true &&
				simon->IsHitSubWeapons() == false) 
			{
				// Lấy vector coobjects
				for (auto candle : listCandles)
				{
					if (candle->IsEnable() == false)
						continue;

					coObjects.push_back(candle);
				}

				for (auto zombie : listZombies)
				{
					if (zombie->GetState() == ZOMBIE_INACTIVE)
						continue;

					coObjects.push_back(zombie);
				}

				for (auto leopard : listBlackLeopards)
				{
					if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
						continue;

					coObjects.push_back(leopard);
				}

				for (auto bat : listVampireBats)
				{
					if (bat->GetState() == VAMPIRE_BAT_INACTIVE)
						continue;

					coObjects.push_back(bat);
				}

				for (auto fishman : listFishMans)
				{
					if (fishman->GetState() == FISHMAN_INACTIVE)
						continue;

					coObjects.push_back(fishman);
				}

				for (auto fireball : listFireBalls)
				{
					if (fireball->IsEnable() == false)
						continue;

					coObjects.push_back(fireball);
				}

				whip->Update(dt, &Objects, &coObjects);
			}
		}
		else if (dynamic_cast<SubWeapon*>(object) && weapon != STOP_WATCH)
		{
			if (weapon->GetScoreReceived() != 0)
			{
				simon->AddScore(weapon->GetScoreReceived());
				weapon->SetScoreReceived(0);
			}

			coObjects.push_back(simon); // dùng cho xét va chạm của simon với boomerang
			
			// dùng cho xét va chạm của holy water với ground
			for (auto ground : listGrounds)
			{
				if (ground->IsEnable() == false)
					continue;

				coObjects.push_back(ground);
			}

			if (weapon->IsEnable() == false)
				continue;

			for (auto candle : listCandles)
			{
				if (candle->IsEnable() == false)
					continue;

				coObjects.push_back(candle);
			}

			for (auto zombie : listZombies)
			{
				if (zombie->GetState() == ZOMBIE_INACTIVE)
					continue;

				coObjects.push_back(zombie);
			}

			for (auto leopard : listBlackLeopards)
			{
				if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
					continue;

				coObjects.push_back(leopard);
			}

			for (auto bat : listVampireBats)
			{
				if (bat->GetState() == VAMPIRE_BAT_INACTIVE)
					continue;

				coObjects.push_back(bat);
			}

			for (auto fishman : listFishMans)
			{
				if (fishman->GetState() == FISHMAN_INACTIVE)
					continue;

				coObjects.push_back(fishman);
			}

			for (auto fireball : listFireBalls)
			{
				if (fireball->IsEnable() == false)
					continue;

				coObjects.push_back(fireball);
			}

			weapon->Update(dt, &Objects, &coObjects);
		}
		else if (dynamic_cast<Zombie*>(object))
		{
			if (object->GetState() != ZOMBIE_INACTIVE)
				object->Update(dt, &Objects, &listGrounds, isUsingStopWatch);
		}
		else if (dynamic_cast<BlackLeopard*>(object))
		{
			if (object->GetState() != BLACK_LEOPARD_INACTIVE)
				object->Update(dt, &Objects, &listGrounds, isUsingStopWatch);
		}
		else if (dynamic_cast<VampireBat*>(object))
		{
			if (object->GetState() != VAMPIRE_BAT_INACTIVE)
			{
				bat = dynamic_cast<VampireBat*>(object);

				if (bat->IsSettedPosition() == false)
				{
					bat->SetIsSettedPosition(true);

					// set vị trí cho dơi luôn 
					// dơi bay ngang tầm simon, từ phía cuối của 2 đầu màn hình)
					float bx, by;

					by = simon->y + 30;

					if (bat->GetOrientation() == -1) bx = game->GetCameraPositon().x + SCREEN_WIDTH - VAMPIRE_BAT_BBOX_WIDTH;
					else bx = game->GetCameraPositon().x;

					bat->SetPosition(bx, by);
				}

				bat->Update(dt, NULL, NULL, isUsingStopWatch);
			}
				
		}
		else if (dynamic_cast<FishMan*>(object))
		{
			fishman = dynamic_cast<FishMan*>(object);

			if (fishman->GetState() == FISHMAN_ACTIVE && 
				GetTickCount() - fishman->GetLastTimeShoot() >= fishman->GetDeltaTimeToShoot())
			{
				fishman->SetState(FISHMAN_HIT);

				// Tạo fireball
				float fx, fy, nx;
				fishman->GetPosition(fx, fy);
				nx = fishman->GetOrientation();

				fireball = new FireBall();
				fireball->SetPosition(fx + 5.0f, fy + 10.0f);
				fireball->SetOrientation(nx);
				fireball->SetState(FIREBALL);
				fireball->SetEnable(true);
				listFireBalls.push_back(fireball);
				Objects.push_back(fireball);

				// Đặt hướng quay mặt của Fishman sau khi bắn (quay về phía simon)
				float sx, sy;
				simon->GetPosition(sx, sy);

				if (fx < sx) fishman->SetNxAfterShoot(1);
				else fishman->SetNxAfterShoot(-1);
			}
			else 
			{
				object->Update(dt, &Objects, &listGrounds, isUsingStopWatch);
			}
		}
		else if (dynamic_cast<Boss*>(object))
		{
			if (boss->GetState() == BOSS_INACTIVE)
				continue;

			// Passing simon's position for boss movement
			float sx, sy;
			simon->GetPosition(sx, sy);
			boss->SetSimonPosition(sx, sy);

			boss->Update(dt);
		}
		else
		{
			object->Update(dt, &Objects, &coObjects, isUsingStopWatch);
		}
	}

	UpdateCameraPosition();
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon());

	for (auto candle : listCandles)
	{
		if (candle->IsEnable() == false)
			continue;

		candle->Render();
		candle->RenderBoundingBox();
	}

	for (auto item : listItems)
	{
		if (item->IsEnable() == false)
			continue;

		item->Render();
		item->RenderBoundingBox();
	}

	for (auto zombie : listZombies)
	{
		zombie->RenderActiveBoundingBox();

		if (zombie->GetState() == ZOMBIE_INACTIVE)
			continue;

		zombie->Render();
		zombie->RenderBoundingBox();
	}

	for (auto leopard : listBlackLeopards)
	{
		leopard->RenderActiveBoundingBox();

		if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
			continue;

		leopard->Render();
		leopard->RenderBoundingBox();
	}

	for (auto bat : listVampireBats)
	{
		bat->RenderActiveBoundingBox();

		if (bat->GetState() == VAMPIRE_BAT_INACTIVE)
			continue;

		bat->Render();
		bat->RenderBoundingBox();
	}

	for (auto fireball : listFireBalls)
	{
		if (fireball->IsEnable() == false)
			continue;

		fireball->Render();
		fireball->RenderBoundingBox();
	}

	for (auto fish : listFishMans)
	{
		fish->RenderActiveBoundingBox();

		fishman = dynamic_cast<FishMan*>(fish);

		if (fishman->GetState() == FISHMAN_INACTIVE)
		{
			if (fishman->IsRenderingBubbles() == true)
				fishman->Render();
			continue;
		}

		fishman->Render();
		fishman->RenderBoundingBox();
	}

	simon->Render();
	simon->RenderBoundingBox();

	if (weapon->IsEnable() == true)
	{
		weapon->Render();
		weapon->RenderBoundingBox();
	}

	if ((simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT ||
		simon->GetState() == HIT_STAIR_UP || simon->GetState() == HIT_STAIR_DOWN) 
		&& simon->IsHitSubWeapons() == false)
	{
		whip->Render(simon->animations[simon->GetState()]->GetCurrentFrame());
		whip->RenderBoundingBox();
	}

	boss->Render();
	boss->RenderBoundingBox();
	boss->RenderActiveBoundingBox();

	for (auto door : listDoors)  // render door sau để chồng lên Simon
	{
		if (door->IsEnable() == false)
			continue;

		door->Render();
		door->RenderBoundingBox();
	}
}

void SceneManager::UpdateCameraPosition()
{
	if (isBossFighting == true) // Boss fight -> not moving camera
		return;

	if (IDScene == SCENE_2 &&
		tilemaps->Get(IDScene)->index == 2 &&
		simon->x + SCREEN_WIDTH / 2 >= tilemaps->Get(IDScene)->GetMapWidth())
	{
		isBossFighting = true;
		return; // Boss fight
	}

	if (simon->x > SCREEN_WIDTH / 2 &&
		simon->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		TileMap * map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (simon->x >= min_col * 32 + (SCREEN_WIDTH / 2 - 16) &&
			simon->x <= max_col * 32 - (SCREEN_WIDTH / 2 - 16))
		{
			game->SetCameraPosition(simon->x - SCREEN_WIDTH / 2, 0);
		}
	}
}

void SceneManager::SetDropItems(LPGAMEOBJECT object)
{
	if (object->IsEnable() == false ||
	   (dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_DESTROYED) ||
		(dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_DESTROYED) || 
		(dynamic_cast<FishMan*>(object) && object->GetState() == FISHMAN_DESTROYED))
	{
		if (object->idItem != -1 && object->IsDroppedItem() == false)
		{
			object->SetIsDroppedItem(true);

			// Tạo một item theo id

			item = new Items();
			item->SetEnable(true);
			item->SetPosition(object->x, object->y);
			item->SetItem(object->idItem);

			listItems.push_back(item);
			Objects.push_back(item);
		}
	}
}

void SceneManager::SetInactivationByPosition()
{
	D3DXVECTOR2 entryViewPort = game->GetCameraPositon();

	for (auto zombie : listZombies)
	{
		Zombie * zb = dynamic_cast<Zombie*>(zombie);

		if (zb->GetState() == ZOMBIE_ACTIVE)
		{
			float zx, zy;
			zb->GetPosition(zx, zy);

			if (zx + ZOMBIE_BBOX_WIDTH < entryViewPort.x || zx > entryViewPort.x + SCREEN_WIDTH)
			{
				zb->SetState(ZOMBIE_INACTIVE);
			}
		}
	}

	for (auto leopard : listBlackLeopards)
	{
		BlackLeopard * bl = dynamic_cast<BlackLeopard*>(leopard);

		if(bl->GetState() == BLACK_LEOPARD_ACTIVE)
		{
			float lx, ly;
			bl->GetPosition(lx, ly);

			if (lx + BLACK_LEOPARD_BBOX_WIDTH < entryViewPort.x || lx > entryViewPort.x + SCREEN_WIDTH)
			{
				bl->SetState(BLACK_LEOPARD_INACTIVE);
			}
		}
	}

	for (auto bat : listVampireBats)
	{
		VampireBat * vb = dynamic_cast<VampireBat*>(bat);

		if (vb->GetState() == VAMPIRE_BAT_ACTIVE && vb->IsSettedPosition() == true)
		{
			float bx, by;
			vb->GetPosition(bx, by);

			if (bx + VAMPIRE_BAT_BBOX_WIDTH < entryViewPort.x || bx > entryViewPort.x + SCREEN_WIDTH)
			{
				vb->SetState(VAMPIRE_BAT_INACTIVE);
			}
		}
	}

	for (auto fishman : listFishMans)
	{
		FishMan * fm = dynamic_cast<FishMan*>(fishman);

		if (fm->GetState() == FISHMAN_ACTIVE || fm->GetState() == FISHMAN_JUMP || fm->GetState() == FISHMAN_HIT)
		{
			float fx, fy;
			fm->GetPosition(fx, fy);

			if (fx + FISHMAN_BBOX_WIDTH < entryViewPort.x || fx > entryViewPort.x + SCREEN_WIDTH ||
				fy > (fm->GetEntryPosition()).y)
			{
				if (fy > (fm->GetEntryPosition()).y) // rớt xuống nước mới có bọt nước
					fm->SetIsNeedToCreateBubbles(true);
				
				fm->SetState(FISHMAN_INACTIVE);
			}
		}
	}

	for (auto fireball : listFireBalls)
	{
		if (fireball->IsEnable() == true)
		{
			float fx, fy;
			fireball->GetPosition(fx, fy);

			if (fx + FIREBALL_BBOX_WIDTH < entryViewPort.x || fx > entryViewPort.x + SCREEN_WIDTH)
			{
				fireball->SetEnable(false);
			}
		}
	}

	if (weapon->IsEnable() == true)
	{
		float wx, wy;
		weapon->GetPosition(wx, wy);

		if (wx < entryViewPort.x || wx > entryViewPort.x + SCREEN_WIDTH ||
			wy > entryViewPort.y + SCREEN_HEIGHT)
		{
			weapon->SetEnable(false);
		}
	}
}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case SCENE_1:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		CreateListChangeSceneObjects();
		simon->SetPosition(0.0f, 302.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case SCENE_2:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		CreateListChangeSceneObjects();
		//simon->SetPosition(2560.0f, 335.0f);
		//game->SetCameraPosition(0.0f, 0.0f);
		simon->SetPosition(5344.0f, 335.0f);
		game->SetCameraPosition(4080.0f, 0.0f); 
		break;
	case SCENE_3:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_3);
		CreateListChangeSceneObjects();
		simon->SetPosition(100.0f, 48.0f);
		simon->SetState(STAIR_DOWN);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

