#include "GameMenuLayer.h"


GameMenuLayer::GameMenuLayer(void)
{
}

GameMenuLayer::~GameMenuLayer(void)
{
}

bool GameMenuLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSprite *bgSprite = CCSprite::create("ui_background_normal-ipadhd.png");
	this->addChild(bgSprite);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bgSprite->setPosition(CCPoint(winSize.width * 0.5,winSize.height * 0.5));
	this->createMenu();
	return true;
}

void GameMenuLayer::createMenu(void)
{
	CCSprite *startNormalBackgroundSprite = CCSprite::create("");
	CCSprite *startNormalTextSprite = CCSprite::create("");

	startNormalBackgroundSprite->addChild(startNormalTextSprite);
	startNormalTextSprite->setPosition(ccp(1,2));

	CCSprite *startSelectedBackgroundSprite = CCSprite::create("");
	CCSprite *startSelectedTextSprite = CCSprite::create("");

	startSelectedBackgroundSprite->addChild(startSelectedTextSprite);
	startSelectedTextSprite->setPosition(ccp(1,2));

	CCMenuItemSprite * startMenuItem = CCMenuItemSprite::create(startNormalBackgroundSprite,
		startSelectedBackgroundSprite,this,menu_selector(GameMenuLayer::menuCallbackStartGame));
	CCMenu *menu = CCMenu::create(startMenuItem,NULL);
	addChild(menu);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(winSize.width / 2,winSize.height / 3));
}

void GameMenuLayer::menuCallbackStartGame(CCObject *sender)
{
}