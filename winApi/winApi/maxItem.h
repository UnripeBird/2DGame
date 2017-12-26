#pragma once
#include "fieldObject.h"
class maxItem :
	public fieldObject
{
private:
	int count;
	float _boomTimer;
	float _boomWorldTimer;
public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void flash();
	void absorption(POINT);

	maxItem() {}
	~maxItem(){}
};

