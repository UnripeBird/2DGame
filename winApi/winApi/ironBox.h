#pragma once
#include "fieldObject.h"
class ironBox :
	public fieldObject
{
private:

	int count;
	float _boomTimer;
	float _boomWorldTimer;

public:
	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void bulletEffect();

	randomFunction* rand;

	int ironrand;
	ironBox(){}
	~ironBox(){}
};

