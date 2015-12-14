#include "StdAfx.h"
#include "SceneManager.h"
#include "TimeManager.h"

#include "HelloWorldScene.h"


CSceneManager::CSceneManager(void)
{
	thisScene = nullptr;
}


CSceneManager::~CSceneManager(void)
{
}


void CSceneManager::SetParam(int n)
{
	Param = n;
}


void CSceneManager::SetScene(int idx)
{
	if (thisScene != nullptr)
		delete thisScene;

	switch (idx)
	{
	case 0:
		//thisScene = new CScene;
		//SceneIdx = 0;
		break;

	case sHelloWorld:
		thisScene = new CHelloWorldScene();
		SceneIdx = sHelloWorld;
		break;

	default:
		break;
	}

	thisScene->Init();
}


void CSceneManager::Init()
{
	SceneIdx = 1;
	SetScene(1);
}

void CSceneManager::Update()
{
	thisScene->Update();
	g_TimeManager->Update();
}

void CSceneManager::Render()
{
	thisScene->Render();
}

void CSceneManager::Release()
{
	if (thisScene != nullptr)
		delete thisScene;
}
