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
	void traipse(); // �÷��̾� ����� ������ ������Ʈ

	stonBox(){}
	~stonBox(){}
};

