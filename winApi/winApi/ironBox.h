#pragma once
#include "fieldObject.h"
class ironBox :
	public fieldObject
{
private:
	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();

	randomFunction* rand;

	int ironrand;

public:
	ironBox(){}
	~ironBox(){}
};

