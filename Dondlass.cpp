#include "stdafx.h"
#include "Dondlass.h"

#include "TimeManager.h"

CDondlass::CDondlass() : CSprite("Dondlass", 98, 102, 0, 0, 98, 102)
{
	SetSpriteImage("Resource/NPC/Dondlass.png");

	AniRect.assign(3, vector<SDL_Rect>(NULL));
	AniDelay.assign(3, vector<int>(NULL));

	for (int i = 0; i < 13; i++)
	{
		AniRect[1].push_back(SDL_Rect{ 0 + (i * 97), 102, 98, 102 });
		AniDelay[1].push_back(100);
	}
	AniDelay[1].back() = 1000;
	SetSpritePos(760, 536);

	SpriteState = 1;
}


CDondlass::~CDondlass()
{
}

void CDondlass::Update()
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
}
