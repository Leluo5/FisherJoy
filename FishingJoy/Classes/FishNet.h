#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class FishNet :
public CCNode
{
public:
	FishNet(void);
	virtual ~FishNet(void);
	CREATE_FUNC(FishNet);
	bool init();
	void FishNet::showAt(CCPoint pos,int type =0);
	CCRect getCollisionArea();

protected:
	float getSpeed(int type);
	CCSprite* _fishNetSprite;
};
