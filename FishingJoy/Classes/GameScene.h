#pragma once
#include "cocos2d.h"
#include "StaticData.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "MenuLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"
#include "Fish.h"
#include "PaneLayer.h"
#include "FishingJoyData.h"
#include "LayerWithBackground.h"

USING_NS_CC;

typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

class GameScene :
	public CCScene
{
public:
	GameScene(void);
	CREATE_FUNC(GameScene)
	virtual bool init();
	virtual ~GameScene();
	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);

	void pause();
	void resume();
	void sound();
	void music();
	void reset();
	//void transToMainMenu();

	void scheduleTimeUp();

protected:
	BackgroundLayer* backgroundLayer;
	FishLayer* fishLayer;
	LayerWithBackground* layerWithBackground;
	CannonLayer* cannonLayer;
	PaneLayer* paneLayer;
	MenuLayer* menuLayer;
	TouchLayer* touchLayer;
	
	bool checkOutCollisionBetweenFishesAndBullet(Bullet* bullet);
	void checkOutCollision();
	virtual void update(float delta);
	void fishWillBeCaught(Fish* fish);
	void alterGold(int delta);
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet* bulet);
	void operateAllSchedulerAndActions(CCNode* node, OperateFlag flag);
};

