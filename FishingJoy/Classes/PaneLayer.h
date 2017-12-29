#pragma once
#include "cocos2d.h"
#include "StaticData.h"
#include "GoldCounterLayer.h"
#include "ScheduleCounterDelegate.h"

USING_NS_CC;

class PaneLayer:public cocos2d::CCLayer,public ScheduleCounterDelegate
{
public:
	virtual bool init();
	PaneLayer(void);
	~PaneLayer(void);
    CREATE_FUNC(PaneLayer)
    CC_SYNTHESIZE_READONLY(GoldCounterLayer *, _goldCounter, GoldCounter)
	void scheduleTimeUp();
	void setScheduleNumber(int number);
protected:
	void pause(CCObject *sender);
	CCLabelTTF* _scheduleLabel;
};

