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
	void update(void);

	vector<fieldObject*> getObject() { return _vObject; }

	objectManager() {}
	~objectManager() {}
};

