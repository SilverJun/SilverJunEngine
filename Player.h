#pragma once
#include "Sprite.h"
class CPlayer :
	public CSprite
{
public:
	CPlayer();
	~CPlayer();

	virtual void Update() override;
	virtual void Render() override;
private:
	bool bIsAnimation;
};

