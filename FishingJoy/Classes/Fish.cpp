#include "Fish.h"

const static float s_dt = 0.05;

enum{
	k_Action_Animate = 0,
	k_Action_MoveTo
};
Fish::Fish(void)
{
}

Fish::~Fish(void)
{
}

Fish* Fish::create(FishType type)
{
	Fish* fish = new Fish;
	if (fish && fish->init(type))
	{
		fish->autorelease();
		return fish;
	}
	else
	{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
}

bool Fish::init(FishType type)
{
	do 
	{
		if (!CCNode::init())
		{
			return false;
		}
		if (type < k_Fish_Type_SmallFish || type >= k_Fish_Type_Count)
		{
			type = k_Fish_Type_SmallFish;
		}
		setType(type);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", _type + 1);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
		CC_BREAK_IF(!animation);
		CCAnimate* animate = CCAnimate::create(animation);
		_fishSprite = CCSprite::create();
		addChild(_fishSprite);
		_fishSprite->runAction(CCRepeatForever::create(animate));
		return true;
	} while (0);
	return false;
}

int Fish::getScore(void)
{
	return (_type-1)*3+1;
}

int Fish::getSpeed(void)
{
	return abs(_type-15)*10+150;
}

CCRect Fish::getCollisionArea()
{
	CCSize size = _fishSprite->getContentSize();
	CCPoint pos = getParent()->convertToWorldSpace(getPosition());
	return CCRect(pos.x - size.width / 2, pos.y - size.height/2, size.width, size.height);
}

void Fish::beCaught(){
	stopActionByTag(k_Action_MoveTo);
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc));
	CCSequence *sequence = CCSequence::create(CCDelayTime::create(1.0f),callFunc,NULL);
	CCBlink *blink = CCBlink::create(1.0f, 8);
	CCSpawn *spawn = CCSpawn::create(sequence, blink, NULL);
	_fishSprite->runAction(spawn);
}

void Fish::beCaught_CallFunc()
{
	if(isRunning())
	{
		getParent()->removeChild(this,false);
	}
}


void Fish::moveTo(CCPoint endPoint)
{
	CCPoint startPoint = getParent() ->convertToWorldSpace(this->getPosition());

	int direction1 = CCRANDOM_0_1() * 2;
	int direction2 = CCRANDOM_0_1() * 2;

	float controlX=0, controlY=0;
	if(direction1 == 0)
		controlX = startPoint.x + rand() % 250;
	else
		controlX = startPoint.x - rand() % 250;
	controlY = startPoint.y;
	CCPoint controlPoint1 = getParent() ->convertToWorldSpace(this->getPosition());
	
	if(direction2 == 0)
		controlX = startPoint.x + rand() % 250;
	else
		controlX = startPoint.x - rand() % 250;
	controlY = endPoint.y;
	CCPoint controlPoint2 = CCPointMake(controlX, controlY);

	ccBezierConfig bezier;
    bezier.controlPoint_1 = controlPoint1;
    bezier.controlPoint_2 = controlPoint2;
    bezier.endPosition = endPoint;

	float duration = ccpDistance(endPoint, startPoint)*1.5 / getSpeed();

	CCFiniteTimeAction* beizerAction=CCBezierTo::create(duration,bezier);
	CCCallFunc* callfunc =CCCallFunc::create(this,callfunc_selector(Fish::moveEnd));
	CCActionInterval * action =CCSpawn::create(beizerAction,NULL);
	CCSequence * sequence =CCSequence::create(action,callfunc,NULL);
	sequence->setTag(k_Action_MoveTo);
	this->runAction(sequence);

	//this->schedule(schedule_selector(Fish::refreshFish), s_dt); 

	/*

	CCPoint point = getParent() ->convertToWorldSpace(this->getPosition());
	float duration = ccpDistance(destination, point) / getSpeed();
	CCMoveTo* moveTo = CCMoveTo::create(duration ,destination);
	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));
	CCFiniteTimeAction *sequence = CCSequence::create(moveTo, callfunc, NULL);
	sequence->setTag(k_Action_MoveTo);
	this->runAction(sequence);
	*/
}


void Fish::moveEnd(){
	if (isRunning())
	{
		this->stopActionByTag(k_Action_MoveTo);
		getParent()->removeChild(this,false);
	}
}

CCSize Fish::getSize(){
	return _fishSprite->displayFrame()->getRect().size;
}

void Fish::refreshFish( float dt )  
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint curPoint = this->getPosition();  //获取鱼当前坐标  
	static CCPoint lastPoint = CCPointMake(0, winSize.height); 
    if (curPoint.x == lastPoint.x && curPoint.y == lastPoint.y)  //  
    {  
        this->unschedule(schedule_selector(Fish::refreshFish));  
        return ;  
    }
	/*
	float a = curPoint.x - lastPoint.x;
	float b = curPoint.y - curPoint.y;
	float c = pow(a,2) + pow(b,2);
	float d = curPoint.x-lastPoint.x;
	d = pow(d,2);

	float k = acos(d / c);
	if(curPoint.y > lastPoint.y)
		k=-k;
	float K = this->getRotation() + k;
	this->setRotation(K);
	//this->setRotation(K*180/3.14159265);

	/*
	float k = atan( (curPoint.x - lastPoint.x) / (curPoint.y - lastPoint.y) );
	float K = this->getRotation();
	this->setRotation(K+k);
    //this->setRotation(K*180/3.14159265);  
	*/

	float K = atan( (curPoint.x - lastPoint.x) / (curPoint.y - lastPoint.y) );  
    this->setRotation(K*360/3.14159265);  

    lastPoint = curPoint;  //保存当前的坐标给下一轮刷新使用  
}  