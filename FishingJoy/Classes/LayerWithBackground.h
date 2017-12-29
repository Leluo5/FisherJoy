#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;
class LayerWithBackground:public CCLayer
{
public:
	LayerWithBackground(void);
	CREATE_FUNC(LayerWithBackground);
	virtual ~LayerWithBackground(void);
	virtual bool init();
};

