#include "stdafx.h"
#include "objectManager.h"
#include "StarBox.h"

HRESULT objectManager::init(void)
{
	IMAGEMANAGER->addFrameImage("박스오브젝트", "image/objectImage/object.bmp", 48, 288, 1, 7);

	for (int i = 0; i < 7; i++)
	{
		fieldObject* obj;
		obj = new StarBox;
		obj->init("흡수박스", starbox, i * 0, PointMake(300 * (i + 1), (5 * i) + 100));
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
