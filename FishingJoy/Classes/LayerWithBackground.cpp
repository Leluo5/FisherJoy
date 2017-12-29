#include "LayerWithBackground.h"


LayerWithBackground::LayerWithBackground(void)
{
}


LayerWithBackground::~LayerWithBackground(void)
{
}


bool LayerWithBackground::init()
{
	if(!CCLayer::init())
		return false;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *duoSprite = CCSprite::createWithSpriteFrameName("ui_duo_img.png");
	duoSprite->setPosition(CCPoint(190,170));
	this->addChild(duoSprite);

	CCSprite *topSprite = CCSprite::createWithSpriteFrameName("ui_box_01.png");
	topSprite->setPosition(CCPoint(winSize.width/2,1450));
	this->addChild(topSprite);

	CCSprite *topDuoSprite = CCSprite::createWithSpriteFrameName("ui_box_01_01.png");
	topDuoSprite->setPosition(CCPoint(winSize.width/2,1500));
	this->addChild(topDuoSprite);
	
	CCSprite *bottomSprite = CCSprite::createWithSpriteFrameName("ui_box_02.png");
	bottomSprite->setPosition(CCPoint(winSize.width/2,60));
	this->addChild(bottomSprite);
	
	return true;
}
