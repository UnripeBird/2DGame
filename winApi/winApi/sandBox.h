#pragma once
#include "fieldObject.h"
class sandBox :
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
	void boomEffect();
	sandBox(){}
	~sandBox(){}
};
