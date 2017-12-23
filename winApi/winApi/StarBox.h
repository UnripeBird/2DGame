#pragma once
#include "fieldObject.h"
class StarBox : public fieldObject
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
	void absorption();

	StarBox() {}
	~StarBox() {}
};

