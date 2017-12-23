#pragma once
#include "fieldObject.h"
class ironBox :
	public fieldObject
{
private:
	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(void);

	void move();

	randomFunction* rand;

	int ironrand;

public:
	ironBox(){}
	~ironBox(){}
};

