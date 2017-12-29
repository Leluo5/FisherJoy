#include "GameMenuLayer.h"
#include "LoadingLayer.h"
GameMenuLayer::GameMenuLayer(void)
{
}

CCScene* GameMenuLayer::scene(void)
{
	CCScene* scene = CCScene::create();
	GameMenuLayer* gameMenuLayer = GameMenuLayer::create();
	scene->addChild(gameMenuLayer);
	return scene;
}

bool GameMenuLayer::init()
{
	do
	{
		if(!CCLayer::init())
		{
			return false;
		}
		CCSprite* bgSprite = CCSprite::create(STATIC_DATA_STRING("game_menu_background"));
		CC_BREAK_IF(!bgSprite);
		this->addChild(bgSprite);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
		CCSprite* titleSprite = CCSprite::create(STATIC_DATA_STRING("game_menu_title"));
		CC_BREAK_IF(!titleSprite);
		this->addChild(titleSprite);
		titleSprite->setPosition(ccp(winSize.width/2,winSize.height*0.75));
		this->createMenu();
		return true;
	}while(0);
	return false;
}

void GameMenuLayer::createMenu(void)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_ui"));
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_text"));
	
	CCSprite* startNormalBackgroundSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_normal"));
	CCSprite* startNormalTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_text"));
	
	startNormalBackgroundSprite->addChild(startNormalTextSprite);
	CCSize startSpriteSize = startNormalBackgroundSprite->getContentSize();
	startNormalTextSprite->setPosition(ccp(startSpriteSize.width * 0.5,startSpriteSize.height * 0.5 + 20));

	CCSprite *startSelectedBackgroundSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_selected"));
	CCSprite *startSelectedTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_text"));

	startSelectedBackgroundSprite->addChild(startSelectedTextSprite);
	startSelectedTextSprite->setPosition(ccp(startSpriteSize.width * 0.5,startSpriteSize.height * 0.5 + 20));
	
	CCMenuItemSprite * startMenuItem = CCMenuItemSprite::create(startNormalBackgroundSprite,
		startSelectedBackgroundSprite,this,menu_selector(GameMenuLayer::menuCallbackStartGame));

	CCMenu *start_menu = CCMenu::create(startMenuItem,NULL);
	this->addChild(start_menu);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	start_menu->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.4));
	
	//
	CCSprite *sceneNormalBackgroundSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_scene_normal"));
	CCSprite *sceneNormalTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_scene_text"));

	sceneNormalBackgroundSprite->addChild(sceneNormalTextSprite);
	CCSize sceneSpriteSize = sceneNormalBackgroundSprite->getContentSize();
	sceneNormalTextSprite->setPosition(ccp(sceneSpriteSize.width * 0.5,sceneSpriteSize.height * 0.5 + 5));

	CCSprite *sceneSelectedBackgroundSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_scene_selected"));
	CCSprite *sceneSelectedTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_scene_text"));

	sceneSelectedBackgroundSprite->addChild(sceneSelectedTextSprite);
	sceneSelectedTextSprite->setPosition(ccp(sceneSpriteSize.width * 0.5,sceneSpriteSize.height * 0.5 + 5));

	CCMenuItemSprite * sceneMenuItem = CCMenuItemSprite::create(sceneNormalBackgroundSprite,
		sceneSelectedBackgroundSprite,this,menu_selector(GameMenuLayer::menuCallbackStartGame));

	CCMenu *scene_menu = CCMenu::create(sceneMenuItem,NULL);
	this->addChild(scene_menu);
	scene_menu->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.2));

}

void GameMenuLayer::menuCallbackSelectScene(CCObject* sender)
{

}

void GameMenuLayer::menuCallbackStartGame(CCObject* sender)
{
	CCScene* loadingLayer = LoadingLayer::scene();
	CCDirector::sharedDirector()->replaceScene(loadingLayer);
}

GameMenuLayer::~GameMenuLayer()
{
}