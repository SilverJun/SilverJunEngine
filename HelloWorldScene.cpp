#include "stdafx.h"
#include "HelloWorldScene.h"

#include "TextManager.h"
#include "SoundManager.h"

#include "Mushmom.h"
#include "Dondlass.h"
#include "Ayan.h"
#include "Yeti.h"
#include "Player.h"


CHelloWorldScene::CHelloWorldScene() : CScene(sHelloWorld)
{
	TextBox[0] = { 20, 20, 0, 40 };
	TextBox[1] = { 20, 60, 0, 40 };

	strcpy(TextString[0], "--헤네시스-- z키-공격1 x키-공격2 c키-점프(미구현) 화살표-이동");
	strcpy(TextString[1], "1420 장은준");

	TextBox[0].w = (strlen(TextString[0]) - 1) * 15;
	TextBox[1].w = (strlen(TextString[1]) - 1) * 15;

	SetSceneBGImage("Resource/BackGround/bg.png");
}


CHelloWorldScene::~CHelloWorldScene()
{
	Release();
}

void CHelloWorldScene::Init()
{
	vSprite.push_back(new CMushmom());
	vSprite.push_back(new CDondlass());
	vSprite.push_back(new CAyan());
	vSprite.push_back(new CYeti());
	vSprite.push_back(new CPlayer());


	for (int i = 0; i < 2; i++)
	{
		g_TextManager->CreateText(TextString[i], &TextBox[i]);
	}

	g_SoundManager->MakeSound(eMainMenuSound, eMainMenu);
	g_SoundManager->PlaySound(eBGMChannel, eMainMenuSound);
}


void CHelloWorldScene::Update()
{
	for (int i = 0; i != vSprite.size(); i++)
	{
		if (vSprite[i] != nullptr)
		{
			vSprite[i]->Update();
		}
	}
}


void CHelloWorldScene::Release()
{
	g_SoundManager->DestroySound(eMainMenuSound);
}

