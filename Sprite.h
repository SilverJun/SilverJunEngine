#pragma once

typedef enum tageSpriteDirection{cUP, cDOWN, cLEFT, cRIGHT, cUNKNOWN} SpriteDirection;


class CSprite
{
protected:
	int x, y;

	SDL_Rect SpriteRect;
	vector<vector<SDL_Rect> > AniRect;
	vector<vector<int> > AniDelay;
	SDL_Rect SpriteMask;
	SDL_Point center;
	
	SpriteDirection SpriteDir;

	float rotation;
	SDL_RendererFlip flip;

	SDL_Surface * SpriteImage;
	SDL_Texture * SpriteTexture;
	char * SpriteName;

	int nAniCount;
	clock_t animationTime;
	
public:
	CSprite();
	CSprite(char *, int w, int h, int mx,int my,int mw, int mh);
	virtual ~CSprite();

	void SetSpriteImage(char *);

	void SetSpritePos(int, int);
	void SetSpriteX(int);
	void SetSpriteY(int);
	void SetSpriteRotation(float); //ȸ���� ����
	void SetSpriteRotate(int);	//ȸ���� ��ȭ
	void SetSpriteCenter(int x, int y);

	SDL_Rect* GetSpriteRect();
	SDL_Rect* GetSpriteMask();
	int GetSpriteX();
	int GetSpriteY();
	float GetSpriteRotation();
	SDL_Texture * GetSpriteTexture();
	char * GetSpriteName();
	SDL_Point * GetSpriteCenter();
	SDL_RendererFlip * GetSpriteFlip();

	SpriteDirection GetSpriteDirection();

	virtual void Update() = 0;
	virtual void Render();
	
	int SpriteState;

};

