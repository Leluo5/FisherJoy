#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class GameMenuLayer:public CCLayer
{
public:
	GameMenuLayer(void);
	CREATE_FUNC(GameMenuLayer)
	virtual bool init();
	virtual ~GameMenuLayer(void);
protected:
	void createMenu(void);
	void menuCallbackStartGame(CCObject *sender);
};

