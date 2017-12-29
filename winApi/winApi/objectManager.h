#pragma once
#include "fieldObject.h"

class objectManager
{
private:
	vector<fieldObject*> _vObject;
	vector<fieldObject*>::iterator _viObject;

public:
	HRESULT init(void);
	void release(void);
	void update(POINT playerPosition, vector<bullet*> bulletPos, int curMapNum);
	void reStar();

	vector<fieldObject*> getObject() { return _vObject; }

	objectManager() {}
	~objectManager() {}
};

