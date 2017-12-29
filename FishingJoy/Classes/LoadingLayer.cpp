#include "LoadingLayer.h"
#include "GameScene.h"
#include "PersonalAudioEngine.h"
#include "FishingJoyData.h"

LoadingLayer::LoadingLayer(void)
{
	_loadedSp = 0;
	_numSp = 3;
	_progressBar = NULL;
	_progressFg = NULL;
}

CCScene* LoadingLayer::scene(void)
{
	CCScene* scene = CCScene::create();
	LoadingLayer* loadingLayer = LoadingLayer::create();
	scene->addChild(loadingLayer);
	return scene;
}


bool LoadingLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("loading_1-ipadhd.png");
	background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.6));
	this->addChild(background);
	this->initProgressBar();
	this->scheduleOnce(schedule_selector(LoadingLayer::cacheInit), 0.5f);
	return true;
}


void LoadingLayer::initProgressBar()
{
	CCSprite* progressBg = CCSprite::create("loading_4-ipadhd.png");
	_progressFg = CCLabelTTF::create("0/100", "Thonburi", 55);
	_progressFg->setColor(ccc3(197, 118, 20));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_progressBar = ProgressBar::create(this, CCSprite::create("loading_5-ipadhd.png"));
	_progressBar->setBackground(progressBg);
	_progressBar->setForeground(_progressFg);
	_progressBar->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.25));
	_progressBar->setSpeed(20.0f);
	this->addChild(_progressBar);
}

void LoadingLayer::progressPercentageSetter(float percentage)
{
	CCString* str = CCString::createWithFormat("%d/100", (int)percentage);
	_progressFg->setString(str->getCString());
}

void LoadingLayer::loadingFinished()
{
	CCScene* gameScene = GameScene::create();	
	CCDirector::sharedDirector()->replaceScene(gameScene);
}

void LoadingLayer::cacheInit(float delta)
{
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	int progressStart = 1;

	float ratio = 3.3f;

	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_05"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_04"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_03"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_02")); 
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_01"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));
	spriteFrameCache->addSpriteFramesWithFile("UI_GameMenuLayer-ipadhd.plist");
	for (int i = 0; i < 8; i++)
		_progressBar->progressTo(ratio*(progressStart++));
	
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	textureCache->addImage(STATIC_DATA_STRING("button_add"));
	textureCache->addImage(STATIC_DATA_STRING("button_sub"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_selected"));
	for (int i = 0; i < 8; i++)
		_progressBar->progressTo(ratio*(progressStart++));

	char str[][50]={"SmallFish","Croaker","AngelFish","Amphiprion","PufferS",
		"Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark",
		"GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
	for(int i = 0;i < 18;i++)
	{
		CCArray *array1 = CCArray::createWithCapacity(10);
		for(int j=0;j<10;j++)
		{
			CCString *spriteFrameName=CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),str[i],j+1);
			CCSpriteFrame * spriteFrame = spriteFrameCache->spriteFrameByName(spriteFrameName->getCString());
			if(spriteFrame==NULL)
			{
				break;
			}
			array1->addObject(spriteFrame);
		}
		if(array1->count()==0)
		{
			continue;
		}
		CCAnimation *animation =CCAnimation::createWithSpriteFrames(array1,0.15f);
		CCString *animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"),i + 1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName->getCString());
		_progressBar->progressTo(ratio*(progressStart++));
	}

	PersonalAudioEngine::sharedEngine();
	FishingJoyData::sharedFishingJoyData();

	_progressBar->progressTo(100.0f);
}

LoadingLayer::~LoadingLayer(void)
{
}
