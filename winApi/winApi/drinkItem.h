#pragma once
#include "fieldObject.h"
class drinkItem :
	public fieldObject
{
private:
	int count;
	float _boomTimer;
	float _boomWorldTimer;

public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(void);

	void move();
	void flash();

	drinkItem(){}
	~drinkItem(){}
};

