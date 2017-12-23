#pragma once
#include "fieldObject.h"
class stonBox :
	public fieldObject
{
private:
public:
	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(void);

	void move();
	void traipse(); // 플레이어 흡수에 끌리는 오브젝트

	stonBox(){}
	~stonBox(){}
};

