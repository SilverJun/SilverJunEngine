#include "stdafx.h"
#include "Yeti.h"

#include "TimeManager.h"
#include "DrawManager.h"

CYeti::CYeti() : CSprite("Yeti", 129, 117, 0, 0, 129, 117)
{
	SetSpriteImage("Resource/Monster/Yeti.png");

	AniRect.assign(2, vector<SDL_Rect>(NULL));
	AniDelay.assign(2, vector<int>(NULL));

	for (int i = 0; i < 5; i++)
	{
		AniRect[0].push_back(SDL_Rect{ 0 + (i * 78), 0, 78, 70 });
		AniDelay[0].push_back(200);
	}

	for (int i = 0; i < 7; i++)
	{
		AniRect[1].push_back(SDL_Rect{ 0 + (i * 129), 71, 129, 117 });
		AniDelay[1].push_back(150);
	}
	AniDelay[1][2] = 50;

	SetSpritePos(300, 400);

	SpriteState = 0;
}


CYeti::~CYeti()
{
}

void CYeti::Update()
{
	clock_t curtime = g_TimeManager->GetTime();

	if (curtime - animationTime > AniDelay[SpriteState][nAniCount])
	{
		animationTime = curtime;
	
		if (nAniCount++ >= AniRect[SpriteState].size() - 1)
		{
			SpriteState = !SpriteState;

			if (SpriteState == 1)
			{
				SpriteRect.x = SpriteRect.x + 15;
				SpriteRect.y = SpriteRect.y - 47;
			}
			else
			{
				SpriteRect.x = SpriteRect.x - 15;
				SpriteRect.y = SpriteRect.y + 47;
			}
			nAniCount = 0;
		}
	}
	//if (nAniCount < AniRect[SpriteState].size() - 1)
	//{
	//	if (curtime - animationTime > 100)
	//	{
	//		nAniCount++;
	//		animationTime = curtime;
	//	}
	//}
	//else
	//{
	//	nAniCount = 0;
	//}

}

void CYeti::Render()
{
	SpriteRect.w = AniRect[SpriteState][0].w;
	SpriteRect.h = AniRect[SpriteState][0].h;

	

	SDL_RenderCopyEx(g_DrawManager->pRenderer, this->GetSpriteTexture(), &AniRect[SpriteState][nAniCount], this->GetSpriteRect(), this->GetSpriteRotation(), this->GetSpriteCenter(), *this->GetSpriteFlip());
}

