#pragma once
#include "fieldObject.h"
class candyItem :
	public fieldObject
{
private:
	int count;
	float _boomTimer;
	float _boomWorldTimer;

public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void wind(POINT);
	void move();
	void flash();
	void absorption(POINT);

	candyItem(){}
	~candyItem(){}
};

