#include "stdafx.h"
#include "Ayan.h"

#include "TimeManager.h"

CAyan::CAyan() : CSprite("Ayan", 58, 77, 0, 0, 58, 77)
{
	SpriteState = 0;
	SetSpriteImage("Resource/NPC/Ayan.png");

	AniRect.assign(2, vector<SDL_Rect>(NULL));
	AniDelay.assign(2, vector<int>(NULL));

	for (int i = 0; i < 5; i++)
	{
		AniRect[0].push_back(SDL_Rect{ 0 + (i * 58), 0, 58, 77 });
		AniRect[1].push_back(SDL_Rect{ 0 + (i * 58), 77, 58, 77 });
		AniDelay[0].push_back(100);
		AniDelay[1].push_back(100);
	}


	SetSpritePos(600, 384);

	SpriteState = 0;
}


CAyan::~CAyan()
{
}

void CAyan::Update()
{
	clock_t curtime = g_TimeManager->GetTime();

	if (curtime - animationTime > AniDelay[SpriteState][nAniCount])
	{
		animationTime = curtime;

		if (nAniCount++ >= AniRect[SpriteState].size() - 1)
		{
			SpriteState = !SpriteState;
			nAniCount = 0;
		}
	}

}