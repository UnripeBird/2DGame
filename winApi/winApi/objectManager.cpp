#include "stdafx.h"
#include "player.h"
#include "objectManager.h"
#include "bullet.h"
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
#include "mobBox.h"

HRESULT objectManager::init(void)
{
	//박스
	IMAGEMANAGER->addFrameImage("박스오브젝트", "image\\objectImage\\object.bmp", 48, 288, 1, 7);
	//커비 브레스 상호작용 박스 폭발
	IMAGEMANAGER->addFrameImage("폭발이미지", "image\\objectImage\\boomObject.bmp", 240, 48, 5, 1, true, RGB(149, 177, 200));
	//아이템
	IMAGEMANAGER->addFrameImage("아이템", "image\\objectImage\\item.bmp", 384, 384, 6, 6, true, RGB(12, 230, 248));
	//커비 브레스 오브젝트 충돌시 브레스 폭발
	IMAGEMANAGER->addFrameImage("총알폭발", "image\\objectImage\\bulletBoom.bmp",276, 48, 6, 1, true, RGB(49, 0, 148));
	//별 오브젝트 이미지
	IMAGEMANAGER->addFrameImage("별오브젝트", "image\\objectImage\\starObject.bmp", 48, 48,1,1, true, RGB(207, 176, 255));
	//오브젝트 몬스터 
	IMAGEMANAGER->addFrameImage("지뢰", "image\\objectImage\\mopObject.bmp", 246, 66, 4, 1, true, RGB(0, 219, 255));
	
	//필드0,1,2 오브젝트

	//0,1,2배경 오브젝트 폭발용
	IMAGEMANAGER->addFrameImage("맵폭발", "image\\objectImage\\mapBoom.bmp",144, 144,3,3, true, RGB(255, 0, 255));
	
	//0맵 오브젝트
	IMAGEMANAGER->addFrameImage("맵01오브젝트", "image\\objectImage\\map01.bmp", 387, 138,1,1, true, RGB(255, 0, 255));

	//1맵 오브젝트
	IMAGEMANAGER->addFrameImage("맵02오브젝트", "image\\objectImage\\map02.bmp", 96 * 3, 54 * 3,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵02오브젝트1", "image\\objectImage\\map02Obj.bmp", 97 * 3, 30 * 3, 1,1,true, RGB(255, 0, 255));

	//맵2 오브젝트
	IMAGEMANAGER->addFrameImage("맵03오브젝트", "image\\objectImage\\map03Obj.bmp", 195, 96,1,1, true, RGB(255, 0, 255));


	//==================================== 오브젝트 ==============================================//
	//스타박스 - 플레이어 흡수 상호작용 : 플레이어가 삼킬수있고 공격으로 사용가능 / 폭탄 연쇄반응O
	for (int i = 0; i < 7; i++)
	{
		fieldObject* star;
		star = new StarBox;
		star->init("starBox", starbox,i*0, PointMake(48 * (i + 5.0f), 148 *2.0f));
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
		ston->init("stonBox", stonbox, i * 0, PointMake(150 * (i + 5.0f), 300 * 2.0f));
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
		iron->init("ironBox", ironbox, i * 0, PointMake(100 * (i + 5.0f), 200 * 2.0f));
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

	for (int i = 0; i < 4; i++)
	{
		fieldObject* MOB;
		MOB = new mobBox;
		MOB->init("mob", mob, i * 0, PointMake(80, 60*(i + 5.0f)));
		_vObject.push_back(MOB);
	}
	//==================================== 오브젝트 끝 ==============================================//

	//===================== 아이템 ============================//

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

	//음료 아이템 - 체력회뵥효과 - 지민이 마음대로
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
	//===================== 아이템 끝 ============================//
	//===================== 맵 오브젝트 시작==========================//

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

void objectManager::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end();)
	{
		(*_viObject)->update(playerPosition, bulletPos);
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
		//별박스, 아이템 플레이어 흡수시 사라지게
		case 4:
		{
			(*_viObject)->release();
			_viObject = _vObject.erase(_viObject);
		}
			break;
		//case 9:
		//{
		//	for (int i = 0; i < _vObject.size(); i++)
		//	{
		//		for (int j = 0; i < _vObject.size(); j++)
		//		{
		//			if (IntersectRect(&_vObject[i]->getItemRc(), &_vObject[i]->getrc(), &_vObject[j]->getrc()))
		//			{
		//				_vObject[i]->setPos(PointMake(_vObject[i]->getPos().x - 24, _vObject[i]->getPos().y));
		//			}
		//		}
		//	}
		//}
		//break;
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
