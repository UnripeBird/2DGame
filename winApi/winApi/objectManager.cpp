#include "stdafx.h"
#include "objectManager.h"
#include "moveBox.h"

HRESULT objectManager::init(void)
{
	for (int i = 0; i < 2; i++)
	{
		fieldObject* obj;
		obj = new moveBox;
		obj->init("¾øÀ½", box, i * 0, PointMake(300 * (i + 1), (150 * i) + 100));
		_vObject.push_back(obj);
	}
	return S_OK;
}

void objectManager::release(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end();)
	{
		(*_viObject)->release();
		SAFE_DELETE(*_viObject);
		_viObject = _vObject.erase(_viObject);
	}
}

void objectManager::update(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end();)
	{
		(*_viObject)->update();
		if ((*_viObject)->getState() == 2)
		{
			(*_viObject)->release();
			_viObject = _vObject.erase(_viObject);
		}
		else
		{
			++_viObject;
		}
	}
}
