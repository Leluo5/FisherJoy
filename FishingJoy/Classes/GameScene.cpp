#include "GameScene.h"
#include "FishingJoyData.h"
#include "PersonalAudioEngine.h"

GameScene::GameScene()
{
}

bool GameScene::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!backgroundLayer);
		this->addChild(backgroundLayer);

		fishLayer = FishLayer::create();
		CC_BREAK_IF(!fishLayer);
		this->addChild(fishLayer);

		layerWithBackground = LayerWithBackground::create();
		CC_BREAK_IF(!layerWithBackground);
		this->addChild(layerWithBackground);

		cannonLayer = CannonLayer::create();
		CC_BREAK_IF(!cannonLayer);
		this->addChild(cannonLayer);

		paneLayer = PaneLayer::create();
		CC_BREAK_IF(!paneLayer);
		this->addChild(paneLayer);

		menuLayer = MenuLayer::create(); 
		CC_BREAK_IF(!menuLayer);
		CC_SAFE_RETAIN(menuLayer); 

		touchLayer = TouchLayer::create();
		CC_BREAK_IF(!touchLayer);
		this->addChild(touchLayer);

		int gold = FishingJoyData::sharedFishingJoyData()->getGold();

		paneLayer->getGoldCounter()->setNumber(gold);

		this->scheduleUpdate();
		
		int i = CCRANDOM_0_1()*3;
		PersonalAudioEngine::sharedEngine()->playBackgroundMusic(i);
	
		return true;
	} while (0);
	return false;
}


GameScene::~GameScene()
{
	CC_SAFE_RELEASE(menuLayer);
}

void GameScene::cannonAimAt(CCPoint target)
{
	cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo(CCPoint target)
{
	int type = cannonLayer->getWeapon()->getCannon()->getType();
	int cost = (type+1) * 1;
	int currentGold = FishingJoyData::sharedFishingJoyData()->getGold();
	if(currentGold >= cost && cannonLayer->shootTo(target)){
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_fire.aif");
		this->alterGold(-cost);
	}
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet* bullet)
{
	CCPoint bulletPos = bullet->getCollosionPoint();
	CCArray* fishArray = fishLayer->getFishArray();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish =(Fish*)obj;
		if(fish->isRunning() && fish->getCollisionArea().containsPoint(bulletPos))
		{
			bullet->end();
			return true;
		}
	}
	return false;
}

void GameScene::checkOutCollision()
{
	CCArray* bullets = cannonLayer->getWeapon()->getBullets();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(bullets, obj)
	{
		Bullet* bullet = (Bullet*)obj;
		if(bullet->isVisible())
		{
			if(checkOutCollisionBetweenFishesAndBullet(bullet))
			{
				checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}
	}	
}

void GameScene::update(float delta)
{
	checkOutCollision();
}

void GameScene::fishWillBeCaught(Fish* fish)
{
	int cannonType = cannonLayer->getWeapon()->getCannonType();
	int fishType = fish->getType();
	float weaponPer = (float)(STATIC_DATA_STRING("weapon_percentage_%d"),cannonType);
	float fishPer =(float)(STATIC_DATA_STRING("fish _percentage_%d"),fishType);
	//改变抓取鱼的难度1.1
	if(CCRANDOM_0_1() < weaponPer * fishPer)
	{
		fish->beCaught();
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_net.mp3");
		int reward = (fishType+1)*10;
		this->alterGold(reward);
	}
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet(Bullet* bullet)
{
	Weapon* weapon = cannonLayer->getWeapon();
	CCRect rect = weapon->getCollisionArea(bullet);
	CCArray* fishArray = fishLayer->getFishArray();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish = (Fish*)obj;
		if(fish->isRunning() && rect.intersectsRect(fish->getCollisionArea()))
		{
			fishWillBeCaught(fish);
		}
	}
}

void GameScene::operateAllSchedulerAndActions(CCNode* node, OperateFlag flag)
{
	if(node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if(array != NULL && array->count()>0){
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void GameScene::pause()
{
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	touchLayer->setTouchEnabled(false);
	this->addChild(menuLayer);
}

void GameScene::resume()
{
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(menuLayer, false);
	touchLayer->setTouchEnabled(true);
}

void GameScene::alterGold(int delta)
{
	FishingJoyData::sharedFishingJoyData()->alterGold(delta);
	paneLayer->getGoldCounter()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}

void GameScene::scheduleTimeUp()
{
	this->alterGold(200);
}
