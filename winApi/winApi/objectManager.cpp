#include "stdafx.h"
#include "objectManager.h"
#include "StarBox.h"
#include"stonBox.h"
#include "boomBox.h"
#include "ironBox.h"
#include "sandBox.h"
#include "lifeItem.h"
#include "candyItem.h"
#include "maxItem.h"
#include "meatItem.h"
#include "drinkItem.h"
#include "cherryItem.h"
HRESULT objectManager::init(void)
{
	IMAGEMANAGER->addFrameImage("박스오브젝트", "image/objectImage/object.bmp", 48, 288, 1, 7);
	IMAGEMANAGER->addFrameImage("폭발이미지", "image/objectImage/boomObject.bmp", 240, 48, 5, 1, true, RGB(149, 177, 200));
	IMAGEMANAGER->addFrameImage("아이템", "image/objectImage/item.bmp", 384, 384, 6, 6, true, RGB(12, 230, 248));

	//스타박스 - 플레이어 흡수 상호작용 : 플레이어가 삼킬수있고 공격으로 사용가능 / 폭탄 연쇄반응O
	for (int i = 0; i < 7; i++)
	{
		fieldObject* star;
		star = new StarBox;
		star->init("starBox", starbox, i * 0, PointMake(48 * (i + 5.0f), 148 *2.0f));
		_vObject.push_back(star);
	}
	for (int i = 0; i < 7; i++)
	{
		fieldObject* star;
		star = new StarBox;
		star->init("starBox", starbox, i * 0, PointMake(48 * (i + 5.0f), 168 * 2.0f));
		_vObject.push_back(star);
	}

	//돌 박스 - 플레이어 흡수 상호작용: 플레이어 좌표로 서서히 이동 / 폭탄연쇄반응 X
	for (int i = 0; i < 7; i++)
	{
		fieldObject* ston;
		ston = new stonBox;
		ston->init("stonBox", stonbox, i * 0, PointMake(150 * (i + 5.0f), 8 * 2.0f));
		_vObject.push_back(ston);
	}

	//폭탄 박스 - 플레이어 흡수X/폭탄 연쇄반응O
	for (int i = 0; i < 1; i++)
	{
		fieldObject* boom;
		boom = new boomBox;
		boom->init("boomBox", boombox, i * 0, PointMake(194, 296));
		_vObject.push_back(boom);
	}

	//아이언 박스 - 플레이어 흡수X/ 폭탄연쇄반응X
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, i * 0, PointMake(170 * (i + 5.0f), 200 * 2.0f));
		_vObject.push_back(iron);
	}
	//샌드 박스 - 플레이어 흡수x / 폭탄연쇄반응O 
	for (int i = 0; i < 3; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, i * 0, PointMake(48 * (i + 5.0f), 188 * 2.0f));
		_vObject.push_back(sand);
	}

	//목숨업 아이템 - 플레이어 목숨 1 증가
	for (int i = 0; i < 1; i++)
	{
		fieldObject* life;
		life = new lifeItem;
		life->init("lifeItem", upItem, i * 0, PointMake(200, 200));
		_vObject.push_back(life);
	}
	//캔디아이템 - 체력회복 효과 - 지민이 맘대로
	for (int i = 0; i < 1; i++)
	{
		fieldObject* candy;
		candy = new candyItem;
		candy->init("candyItem", candyitem, i * 0, PointMake(270, 200));
		_vObject.push_back(candy);
	}
	//맥스 아이템 - 체력 풀 회복 효과
	for (int i = 0; i < 1; i++)
	{
		fieldObject* max;
		max = new maxItem;
		max->init("maxItem", maxtem, i * 0, PointMake(340, 200));
		_vObject.push_back(max);
	}
	//고기 아이템 - 체력 회복효과 - 지민이 맘대로
	for (int i = 0; i < 1; i++)
	{
		fieldObject* meattem;
		meattem = new meatItem;
		meattem->init("meatItem", meat, i * 0, PointMake(410, 200));
		_vObject.push_back(meattem);
	}

	//음료 아이템 - 체력회뵥요과 - 지민이 마음대로
	for (int i = 0; i < 1; i++)
	{
		fieldObject* drinktem;
		drinktem = new drinkItem;
		drinktem->init("drinkItem", drink, i * 0, PointMake(480, 200));
		_vObject.push_back(drinktem);
	}

	//체리 아이템 - 체력회복효과 - 지민이 마음대로
	for (int i = 0; i < 1; i++)
	{
		fieldObject* cherrytem;
		cherrytem = new cherryItem;
		cherrytem->init("cherryItem", cherry, i * 0, PointMake(550, 200));
		_vObject.push_back(cherrytem);
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
		switch ((*_viObject)->getState())
		{
		case 2:
		{
			for (int j = 0; j < 4; j++)
			{
				POINT pt;
				switch (j)
				{
					//충돌 범위 체크 LEFT
				case 0:
					pt.x = (*_viObject)->getPos().x - 25;
					pt.y = (*_viObject)->getPos().y;
					break;
					//충돌 범위 체크 TOP
				case 1:
					pt.x = (*_viObject)->getPos().x;
					pt.y = (*_viObject)->getPos().y - 25;
					break;
					//충돌 범위 체크 RIGHT
				case 2:
					pt.x = (*_viObject)->getPos().x + 25;
					pt.y = (*_viObject)->getPos().y;
					break;
					//충돌 범위 체크 BOTTOM
				case 3:
					pt.x = (*_viObject)->getPos().x;
					pt.y = (*_viObject)->getPos().y + 25;
					break;
				}
				for (int i = 0; i < _vObject.size(); i++)
				{
					if (PtInRect(&_vObject[i]->getrc(), pt))
					{
						_vObject[i]->boomEffect();
						_vObject[i]->setState(3);
					}
				}
			}
			(*_viObject)->release();
			_viObject = _vObject.erase(_viObject);
		}
			break;
		default:
		{
			++_viObject;
		}
			break;
		}

		//if ((*_viObject)->getState() == 2)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		POINT pt;
		//		switch (j)
		//		{
		//			//충돌 범위 체크 LEFT
		//		case 0:
		//			pt.x = (*_viObject)->getPos().x-25;
		//			pt.y = (*_viObject)->getPos().y;
		//			break;
		//			//충돌 범위 체크 TOP
		//		case 1:
		//			pt.x = (*_viObject)->getPos().x;
		//			pt.y = (*_viObject)->getPos().y-25;
		//			break;
		//			//충돌 범위 체크 RIGHT
		//		case 2:
		//			pt.x = (*_viObject)->getPos().x+25;
		//			pt.y = (*_viObject)->getPos().y;
		//			break;
		//			//충돌 범위 체크 BOTTOM
		//		case 3:
		//			pt.x = (*_viObject)->getPos().x;
		//			pt.y = (*_viObject)->getPos().y + 25;
		//			break;
		//		}
		//		for (int i = 0; i < _vObject.size(); i++)
		//		{
		//			if (PtInRect(&_vObject[i]->getrc(), pt))
		//			{
		//				_vObject[i]->boomEffect();
		//				_vObject[i]->setState(3);
		//			}
		//		}
		//	}
		//	(*_viObject)->release();
		//	_viObject = _vObject.erase(_viObject);
		//}
		//else
		//{
		//	++_viObject;
		//}
	}
}
