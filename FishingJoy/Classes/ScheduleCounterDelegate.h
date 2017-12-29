#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class ScheduleCounterDelegate
{
public:
	virtual void scheduleTimeUp() = 0;
	virtual void setScheduleNumber(int number){
		return;
	}
};
