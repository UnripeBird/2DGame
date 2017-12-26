#pragma once
#include "fieldObject.h"
class mapObject03 :
	public fieldObject
{
private:

	int count;
	float _boomTimer;
	float _boomWorldTimer;

	int bullectCount;
	float _bullectTimer;
	float _bullectWorldTimer;
public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void bulletEffect();
	mapObject03(){}
	~mapObject03(){}
};

