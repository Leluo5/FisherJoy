#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class ProgressDelegate
{
public:
	virtual void loadingFinished() = 0;
	virtual void progressPercentageSetter(float percentage)=0;
	ProgressDelegate(void);
	virtual ~ProgressDelegate(void);
};

