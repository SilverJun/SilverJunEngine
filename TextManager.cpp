#include "stdafx.h"
#include "TextManager.h"

#include "han2unicode.h"
#include "DrawManager.h"

#define VA_MAX		1024

CTextManager::CTextManager()
{
	for (int i = 0; i < 10; i++)
	{
		pTTF_Texture[i] = SDL_CreateTexture(g_DrawManager->pRenderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WINDOW_DEFAULT_W, WINDOW_DEFAULT_H);

		pTTF_Surface[i] = SDL_CreateRGBSurface(0, WINDOW_DEFAULT_W, WINDOW_DEFAULT_H, 32,
			0,
			0,
			0,
			0);
	}
}


CTextManager::~CTextManager()
{
}


void CTextManager::Init()
{
	TTF_Init();

	pTTF_Font = nullptr;
	point = 20;

	

	color.a = 255;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (int i = 0; i < 10; i++)
	{
		string_han_idx_table[i] = false;
		pTTF_Texture[i] = nullptr;
		if (pTTF_Surface[i] != nullptr)
		{
			SDL_FreeSurface(pTTF_Surface[i]);
			pTTF_Surface[i] = nullptr;
			pTTF_Texture[i] = nullptr;
		}
	}

	pTTF_Font = TTF_OpenFont("Resource/korFont.TTF", point);
}


void CTextManager::Update()
{

}


void CTextManager::Render()
{
	for (int i = 0; i < 10; i++)
	{
		if (string_han_idx_table[i])
		{
			pTTF_Texture[i] = SDL_CreateTextureFromSurface(g_DrawManager->pRenderer, pTTF_Surface[i]);
			SDL_RenderCopy(g_DrawManager->pRenderer, pTTF_Texture[i], NULL, &TTF_Rect[i]);
			SDL_DestroyTexture(pTTF_Texture[i]);
		}
	}
}


void CTextManager::Release()
{
	DestroyTextAll();
	for (int i = 0; i < 10; i++)
	{
		SDL_FreeSurface(pTTF_Surface[i]);
	}

	TTF_CloseFont(pTTF_Font);
	TTF_Quit();
}


int CTextManager::CreateText(char *string, int x, int y, int w, int h)
{
	int i;
	for (i = 0;; i++)
	{
		if (string_han_idx_table[i] == false)
		{
			TTF_Rect[i].x = x;
			TTF_Rect[i].y = y;
			TTF_Rect[i].w = w;
			TTF_Rect[i].h = h;
			han2unicode(string, string_han[i]);
			string_han_idx_table[i] = true;

			if (pTTF_Surface[i] != nullptr)
			{
				SDL_FreeSurface(pTTF_Surface[i]);
				pTTF_Surface[i] = nullptr;
			}
			if (string_han_idx_table[i] && pTTF_Surface[i] == nullptr)
			{
				pTTF_Surface[i] = TTF_RenderUNICODE_Blended(pTTF_Font, string_han[i], color);
			}

			break;
		}
	}
	return i;
}

int CTextManager::CreateText(char *string, SDL_Rect *rect)
{
	int i;
	for (i = 0;; i++)
	{
		if (string_han_idx_table[i] == false)
		{
			TTF_Rect[i].x = rect->x;
			TTF_Rect[i].y = rect->y;
			TTF_Rect[i].w = rect->w;
			TTF_Rect[i].h = rect->h;
			han2unicode(string, string_han[i]);
			string_han_idx_table[i] = true;

			if (pTTF_Surface[i] != nullptr)
			{
				SDL_FreeSurface(pTTF_Surface[i]);
				pTTF_Surface[i] = nullptr;
			}
			if (string_han_idx_table[i] && pTTF_Surface[i] == nullptr)
			{
				pTTF_Surface[i] = TTF_RenderUNICODE_Blended(pTTF_Font, string_han[i], color);
			}

			break;
		}
	}

	return i;
}


void CTextManager::ModifyText(char * string, int idx)
{
	han2unicode(string, string_han[idx]);

	if (pTTF_Surface[idx] != nullptr)
	{
		SDL_FreeSurface(pTTF_Surface[idx]);
		pTTF_Surface[idx] = nullptr;
	}
	if (string_han_idx_table[idx] && pTTF_Surface[idx] == nullptr)
	{
		pTTF_Surface[idx] = TTF_RenderUNICODE_Blended(pTTF_Font, string_han[idx], color);
	}
}


void CTextManager::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}


void CTextManager::DestroyText(int idx)
{
	memset(string_han[idx], 0, 256);
	string_han_idx_table[idx] = false;
	if (pTTF_Surface[idx] != nullptr)
	{
		SDL_FreeSurface(pTTF_Surface[idx]);
		pTTF_Surface[idx] = nullptr;
	}
}


void CTextManager::DestroyTextAll()
{
	for (int i = 0; i < 10; i++)
	{
		if (pTTF_Surface[i] != nullptr)
		{
			SDL_FreeSurface(pTTF_Surface[i]);
			pTTF_Surface[i] = nullptr;
			string_han_idx_table[i] = false;
		}
		memset(string_han[i], 0, 256);
	}
	
}

SDL_Surface *SDL_TextOut(const char *format, ...)
{
	static char buffer[VA_MAX];

	va_list vl;
	va_start(vl, format);
	_vsnprintf(buffer, VA_MAX, format, vl);
	va_end(vl);

	TTF_Font* font;
	font = TTF_OpenFont("./Resource/MALGUNBD.TTF", 18);

	Uint16 destBuff[128];
	han2unicode(buffer, destBuff);
	SDL_Surface* msg;
	SDL_Color FontColor = {0, 0, 0};

	msg = TTF_RenderUNICODE_Solid(font, destBuff, FontColor);

	TTF_CloseFont(font);

	return msg;
}
