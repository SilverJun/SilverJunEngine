#include "stdafx.h"
#include "Player.h"

#include "TimeManager.h"
#include "DrawManager.h"
#include "EventManager.h"

CPlayer::CPlayer() : CSprite("Player", 64, 80, 0, 0, 64, 80)
{
	SetSpriteImage("Resource/Player/Player.png");

	AniRect.assign(5, vector<SDL_Rect>(NULL));
	AniDelay.assign(5, vector<int>(NULL));

	
	AniRect[0].push_back(SDL_Rect{ 0, 0, 64, 80 });
	AniDelay[0].push_back(0);

	for (int i = 0; i < 5; i++)
	{
		AniRect[1].push_back(SDL_Rect{ 0 + (i * 64), 80, 64, 80 });
		AniDelay[1].push_back(100);
	}

	AniRect[2].push_back(SDL_Rect{ 0, 160, 64, 80 });
	AniDelay[2].push_back(500);

	for (int i = 0; i < 6; i++)
	{
		AniRect[3].push_back(SDL_Rect{ 0 + (i * 128), 240, 128, 96 });
		AniDelay[3].push_back(200);
	}

	for (int i = 0; i < 7; i++)
	{
		AniRect[4].push_back(SDL_Rect{ 0 + (i * 128), 240 + 96, 128, 96 });
		AniDelay[4].push_back(200);
	}

	SetSpritePos(100, 550);

	SpriteState = 0;
	SpriteDir = cLEFT;
	bIsAnimation = false;
}


CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	clock_t curtime = g_TimeManager->GetTime();

	if (g_EventManager->g_Event.type == SDL_KEYDOWN)
	{
		
		if (g_EventManager->KeyProsess[Left])
		{
			SpriteDir = cLEFT;
			SpriteState = 1;
			SpriteRect.x -= 5;
			bIsAnimation = true;
		}
		if (g_EventManager->KeyProsess[Right])
		{
			SpriteDir = cRIGHT;
			SpriteState = 1;
			SpriteRect.x += 5;
			bIsAnimation = true;
		}
		if (!bIsAnimation)
		{
			if (g_EventManager->KeyProsess[n1])			//공격1 애니메이션
			{
				SpriteState = 3;
				nAniCount = 0;
				bIsAnimation = true;
			}
			if (g_EventManager->KeyProsess[n2])			//공격2 애니메이션
			{
				SpriteState = 4;
				nAniCount = 0;
				bIsAnimation = true;
			}
			if (g_EventManager->KeyProsess[n3])			//점프 애니메이션
			{
				SpriteState = 2;
				nAniCount = 0;
				bIsAnimation = true;
			}
		}
	}
	else
	{
		if (SpriteState == 1)
		{
			SpriteState = 0;
			nAniCount = 0;
			bIsAnimation = false;
		}
		
	}
	

	if (bIsAnimation)
	{
		if (SpriteState == 2 && curtime - animationTime > 250)
		{
			SpriteRect.y--;
		}

		if (curtime - animationTime > AniDelay[SpriteState][nAniCount])
		{
			animationTime = curtime;
			

			if (nAniCount++ >= AniRect[SpriteState].size() - 1)
			{
				nAniCount = 0;
				if (SpriteState == 3 || SpriteState == 4 || SpriteState == 2)
				{
					SpriteState = 0;
					nAniCount = 0;
					bIsAnimation = false;
				}
			}
		}
	}
	else if (SpriteState == 1)
	{
		SpriteState = 0;
		nAniCount = 0;
		bIsAnimation = false;
	}

	if (SpriteDir == cRIGHT)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}


}

void CPlayer::Render()
{
	SpriteRect.w = AniRect[SpriteState][0].w;
	SpriteRect.h = AniRect[SpriteState][0].h;

	SDL_RenderCopyEx(g_DrawManager->pRenderer, this->GetSpriteTexture(), &AniRect[SpriteState][nAniCount], this->GetSpriteRect(), this->GetSpriteRotation(), this->GetSpriteCenter(), *this->GetSpriteFlip());
}

