#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{
	if(!CCLayer::init())
		return false;
	CCSprite *bgSprite = CCSprite::create(STATIC_DATA_STRING("game_background_01"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bgSprite->setPosition(CCPoint(winSize.width * 0.5,winSize.height * 0.5));
	this->addChild(bgSprite);
	return true;
}

BackgroundLayer::~BackgroundLayer(void)
{
}
