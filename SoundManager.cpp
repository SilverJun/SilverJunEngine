#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager(void)
{
	System_Create(&pSystem);
}


CSoundManager::~CSoundManager(void)
{
}

void CSoundManager::Init()
{
	pSystem->init(3, FMOD_INIT_NORMAL, 0);

	
	FilePath.insert(unordered_map<eSong, char*>::value_type(eMainMenu, "Resource/Henesys.mp3"));
}

void CSoundManager::Update()
{
	pSystem->update();
}


void CSoundManager::Release()
{
	FilePath.erase(FilePath.begin(), FilePath.end());
	SongMap.erase(SongMap.begin(), SongMap.end());

	for (int i = 0; i < 3; i++)
	{
		pChannel[i]->stop();
	}
	
	pSystem->close();
}


void CSoundManager::MakeSound(eSound n, eSong song)
{
	FMOD_RESULT f;
	Sound *temp;
	
	f = pSystem->createSound(FilePath[song], FMOD_DEFAULT, NULL, &temp);
	f;

	SongMap.insert(unordered_map<eSound, Sound*>::value_type(n, temp));

	
}


void CSoundManager::DestroySound(eSound n)
{
	SongMap[n]->release();
	SongMap.erase(n);
}


void CSoundManager::PlaySound(eChannel c, eSound n)
{
	FMOD_RESULT f;
	f = pSystem->playSound(FMOD_CHANNEL_FREE, SongMap[n], false, &pChannel[c]);
	f;

	pChannel[c]->setVolume(0.5f);
}


void CSoundManager::PauseSound(eChannel c, bool b)
{
	pChannel[c]->setPaused(b);
}


void CSoundManager::StopSound(eChannel c)
{
	pChannel[c]->stop();
}

