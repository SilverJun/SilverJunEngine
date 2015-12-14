#pragma once
#include "Sprite.h"
class CYeti :
	public CSprite
{
public:
	CYeti();
	~CYeti();

	virtual void Update() override;
	virtual void Render() override;
};

