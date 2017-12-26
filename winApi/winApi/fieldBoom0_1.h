#pragma once
#include "fieldObject.h"
class fieldBoom0_1 :
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
	void boomEffect();
	void bulletEffect();

	fieldBoom0_1(){}
	~fieldBoom0_1(){}
};

