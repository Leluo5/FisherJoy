#include "PaneLayer.h"
#include "GameScene.h"
#include "ScheduleCountDown.h"
PaneLayer::PaneLayer(void)
{

}

PaneLayer::~PaneLayer(void)
{

}
bool PaneLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	_goldCounter = GoldCounterLayer::create(0);
	addChild(_goldCounter);
    _goldCounter->setPosition(ccp(600,45));
	
	ScheduleCountDown* countDown = ScheduleCountDown::create(this);
	_scheduleLabel = CCLabelTTF::create("60", "Thonburi", 70);
	_scheduleLabel->addChild(countDown);
	this->addChild(_scheduleLabel);
	_scheduleLabel->setPosition(ccp(50, 500));

	CCMenuItemSprite* pauseItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_pause_normal")), 
		CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_pause_selected")),
		this,menu_selector(PaneLayer::pause));
	CCMenu* pauseMenu = CCMenu::create(pauseItem, NULL);
	this->addChild(pauseMenu);
    pauseMenu->setPosition(CCPoint(200,1470));
	
	return true;
}

void PaneLayer::pause(CCObject *sender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->pause();
}

void PaneLayer::setScheduleNumber(int number)
{
	_scheduleLabel->setString(CCString::createWithFormat("%d",number)->getCString());
}

void PaneLayer::scheduleTimeUp()
{
	_scheduleLabel->setVisible(false);
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->scheduleTimeUp();
}
