#pragma once
#include "Scene.h"
class CHelloWorldScene :
	public CScene
{
public:
	CHelloWorldScene();
	~CHelloWorldScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

private:
	SDL_Rect TextBox[2];
	char TextString[2][100];
};

