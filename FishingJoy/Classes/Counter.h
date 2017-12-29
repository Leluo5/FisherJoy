#ifndef _COUNTER_H
#define _COUNTER_H
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

enum{
    k_Counter_Action = 0
};

class Counter:public CCNode
{
public:
    static Counter* create(CCArray* presenters, int digit = 0); 
    CC_PROPERTY(int, _digit, Digit)
protected:
	bool init(CCArray* presenters, int digit = 0);
    virtual void visit();
    CCNode* _presenters;
    void animation();
private:
};

#endif