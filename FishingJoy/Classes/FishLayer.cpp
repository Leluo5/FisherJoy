#include "FishLayer.h"
#include <ctime>

//#define FISH_MAX_COUNT 50

enum{
	k_Direction_Left = 0,
	k_Direction_Right,
	k_Direction_Top,
	k_Direction_Count
}DirectionType;

enum{
	k_DisplayDriection_Left = 0,
	k_DisplayDriection_Right,
	k_DisplayDirection_Top,
	k_DisplayDirection_Count
}DisplayDirectionType;

FishLayer::FishLayer(void)
{
}

bool FishLayer::init()
{
	do 
	{
		if (!CCLayer::init())
		{
			return false;
		}
		_fishes = CCArray::createWithCapacity(FISH_MAX_COUNT);
		CC_SAFE_RETAIN(_fishes);
		for(int i = 0; i < FISH_MAX_COUNT; i++){
			int type = CCRANDOM_0_1() * k_Fish_Type_Count - 1;
			Fish* fish = Fish::create((FishType)type);
			_fishes->addObject(fish);
		}
		srand((unsigned)time(0));
		this->schedule(schedule_selector(FishLayer::addFish), 2.0f);
		return true;
	} while (0);
	return false;
}

void FishLayer::addFish(float delta)
{
		int addToCount = CCRANDOM_0_1() * 5 + 1;
		int count = 0;
		CCObject* obj;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCARRAY_FOREACH(_fishes, obj)
		{
			Fish* fish = (Fish*)obj;
			if(fish->isRunning())
			{
				continue;
			}
			resetFish(fish);
			count++;
			if(count == addToCount)
			{
				break;
			}
		}
}

void FishLayer::resetFish(Fish* fish)
{
	int direction = CCRANDOM_0_1() * k_Direction_Count;
	int displayDriection = CCRANDOM_0_1() * k_DisplayDirection_Count;
	float startX=0, startY=0, endX=0, endY=0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish->getSize();
	if (direction == k_Direction_Left)
	{
		startX = winSize.width + fishSize.width / 2;
		startY = rand() % (int)(winSize.height - fishSize.height) + fishSize.height / 2;
		fish->setRotation(0);
		//endX = 0 - fishSize.width / 2;
	}
	else if (direction == k_Direction_Right)
	{
		startX = -fishSize.width / 2;
		startY = rand() % (int)(winSize.height - fishSize.height) + fishSize.height / 2;
		fish->setRotation(180);
	}
	else if (direction == k_Direction_Top)
	{
		startX = rand() % (int)(winSize.width - fishSize.width) + fishSize.width / 2;
		startY = winSize.height + fishSize.height / 2;
		fish->setRotation(-90);
	}

	if (displayDriection == k_DisplayDriection_Left)
	{
		endX = -fishSize.width / 2;
		endY = rand() % (int)(winSize.height - fishSize.height) + fishSize.height / 2;
	}
	else if (displayDriection == k_DisplayDriection_Right)
	{
		endX = winSize.width + fishSize.width / 2;
		endY = rand() % (int)(winSize.height - fishSize.height) + fishSize.height / 2;
	}
	else if (displayDriection == k_DisplayDirection_Top)
	{
		endX = rand() % (int)(winSize.width - fishSize.width) + fishSize.width / 2;
		endY = winSize.height + fishSize.height / 2;
	}
	
	addChild(fish);
	fish->setPosition(ccp(startX,startY));
	fish->moveTo(ccp(endX,endY));
}

FishLayer::~FishLayer(void)
{
}


