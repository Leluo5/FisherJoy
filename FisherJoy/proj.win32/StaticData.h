//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : StaticData.h
//  @ Date : 2017/10/28
//  @ Author : 
//
//


#if !defined(_STATICDATA_H)
#define _STATICDATA_H
#include <string>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;


class StaticData {
public:
	StaticData* sharedStaticData();
	bool init();
	const char* stringFromKey(const std::string &key);
	int intFromKey(const std::string &key);
	int floatFromKey(const std::string &key);
	bool booleanFromKey(const std::string &key);
	cocos2d::CCPoint pointFromKey(const std::string &key);
	cocos2d::CCRect rectFromKey(const std::string &key);
	cocos2d::CCSize sizeFromKey(const std::string &key);
	void purge();
protected:
	cocos2d::CCDictionary _dictionary;
	std::string _staticFileName;
private:
	StaticData();
	~StaticData();
};

#endif  //_STATICDATA_H
