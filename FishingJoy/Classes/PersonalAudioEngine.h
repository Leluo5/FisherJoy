#pragma once
#include "cocos2d.h"
#include "StaticData.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class PersonalAudioEngine :
	public SimpleAudioEngine
{
public:
	PersonalAudioEngine(void);
	~PersonalAudioEngine(void);
	static PersonalAudioEngine* sharedEngine();
	bool init();
	void setBackgroundMusicVolume(float volume);
	void setEffectsVolume(float volume);
	void purge();
	void PersonalAudioEngine::playBackgroundMusic(int type);
};
