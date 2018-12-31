#include "TitleScreen.h"



TitleScreen::TitleScreen()
{
}


TitleScreen::~TitleScreen()
{
}

void TitleScreen::Render()
{
	Game::GetInstance()->Draw(0, 0, 0, 0, view, 0, 0, 514, 450);
	bird->Render(0, 0, 370, 210);

	if (bird->GetCurrentFrame() == 15)
		bird->SetFrame(12);
}
