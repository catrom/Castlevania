#include "IntroScene.h"

IntroScene::IntroScene(Simon * simon)
{
	this->simon = simon;

	this->simon->SetPosition(450, 335);
	this->simon->SetOrientation(DIR_LEFT);
	this->simon->SetState(WALK);
	this->simon->vx = -SIMON_WALKING_SPEED_LOWER;
	this->simon->AutoWalk(-230, BACK, -1);

	cloud = new Cloud();

	for (int i = 0; i < 3; i++)
	{
		Bat * bat = new Bat();
		bats.push_back(bat);
	}
}

IntroScene::~IntroScene()
{
	for (int i = 0; i < 3; i++)
		delete bats[i];

	bats.clear();

	delete cloud;
}

void IntroScene::Update(DWORD dt)
{
	simon->Update(dt);
	cloud->Update(dt);
	for (auto bat : bats)
		bat->Update(dt);
}

void IntroScene::Render()
{
	Game::GetInstance()->Draw(0, 0, 0, 0, view, 0, 0, 512, 448);

	simon->Render();
	cloud->Render();
	for (auto bat : bats)
		bat->Render();
}
