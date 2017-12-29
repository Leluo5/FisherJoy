#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class GoldCounterLayer:public CCNode
{
public:
    static GoldCounterLayer* create(int number = 0);
    void setNumber(int number,int ceiling = 999999);
protected:
	bool init(int number = 0);
	int _number;
private:
};
