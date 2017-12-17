#pragma once
#include "fieldObject.h"
class moveBox : public fieldObject
{
private:

public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(void);

	void move();

	moveBox() {}
	~moveBox() {}
};

