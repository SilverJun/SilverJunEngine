#include "stdafx.h"
#include "Mushmom.h"

#include "TimeManager.h"


CMushmom::CMushmom() : CSprite("Mushmom", 60, 80, 0, 0, 120, 160)
{
	SpriteDir = cLEFT;
	SetSpriteImage("Resource/Monster/Mushmom.png");

	AniRect.assign(1, vector<SDL_Rect>(NULL));
	AniDelay.assign(1, vector<int>(NULL));

	for (int i = 0; i < 7; i++)
	{
		AniRect[0].push_back(SDL_Rect{ 0 + (i * 120), 0, 120, 160 });
		AniDelay[0].push_back(100);
	}

	SpriteState = 0;
	SetSpritePos(10, 550);
}


CMushmom::~CMushmom()
{
}

void CMushmom::Update()
{
	clock_t curtime = g_TimeManager->GetTime();

	if (curtime - animationTime > AniDelay[SpriteState][nAniCount])
	{
		animationTime = curtime;

		if (nAniCount++ >= AniRect[SpriteState].size() - 1)
		{
			nAniCount = 0;
		}
	}


	if (SpriteRect.x <= 0)
	{
		flip = SDL_FLIP_HORIZONTAL;
		SpriteDir = cRIGHT;
	}

	if (SpriteRect.x >= WINDOW_DEFAULT_W)
	{
		flip = SDL_FLIP_NONE;
		SpriteDir = cLEFT;
	}

	switch (SpriteDir)
	{
	case cLEFT:
		SpriteRect.x -= 2;
		break;

	case cRIGHT:
		SpriteRect.x += 2;
		break;


	default:
		break;
	}

}