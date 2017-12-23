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
	IMAGEMANAGER->addFrameImage("�ڽ�������Ʈ", "image/objectImage/object.bmp", 48, 288, 1, 7);
	IMAGEMANAGER->addFrameImage("�����̹���", "image/objectImage/boomObject.bmp", 240, 48, 5, 1, true, RGB(149, 177, 200));
	IMAGEMANAGER->addFrameImage("������", "image/objectImage/item.bmp", 384, 384, 6, 6, true, RGB(12, 230, 248));

	//��Ÿ�ڽ� - �÷��̾� ��� ��ȣ�ۿ� : �÷��̾ ��ų���ְ� �������� ��밡�� / ��ź �������O
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

	//�� �ڽ� - �÷��̾� ��� ��ȣ�ۿ�: �÷��̾� ��ǥ�� ������ �̵� / ��ź������� X
	for (int i = 0; i < 7; i++)
	{
		fieldObject* ston;
		ston = new stonBox;
		ston->init("stonBox", stonbox, i * 0, PointMake(150 * (i + 5.0f), 8 * 2.0f));
		_vObject.push_back(ston);
	}

	//��ź �ڽ� - �÷��̾� ���X/��ź �������O
	for (int i = 0; i < 1; i++)
	{
		fieldObject* boom;
		boom = new boomBox;
		boom->init("boomBox", boombox, i * 0, PointMake(194, 296));
		_vObject.push_back(boom);
	}

	//���̾� �ڽ� - �÷��̾� ���X/ ��ź�������X
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, i * 0, PointMake(170 * (i + 5.0f), 200 * 2.0f));
		_vObject.push_back(iron);
	}
	//���� �ڽ� - �÷��̾� ���x / ��ź�������O 
	for (int i = 0; i < 3; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, i * 0, PointMake(48 * (i + 5.0f), 188 * 2.0f));
		_vObject.push_back(sand);
	}

	//����� ������ - �÷��̾� ��� 1 ����
	for (int i = 0; i < 1; i++)
	{
		fieldObject* life;
		life = new lifeItem;
		life->init("lifeItem", upItem, i * 0, PointMake(200, 200));
		_vObject.push_back(life);
	}
	//ĵ������� - ü��ȸ�� ȿ�� - ������ �����
	for (int i = 0; i < 1; i++)
	{
		fieldObject* candy;
		candy = new candyItem;
		candy->init("candyItem", candyitem, i * 0, PointMake(270, 200));
		_vObject.push_back(candy);
	}
	//�ƽ� ������ - ü�� Ǯ ȸ�� ȿ��
	for (int i = 0; i < 1; i++)
	{
		fieldObject* max;
		max = new maxItem;
		max->init("maxItem", maxtem, i * 0, PointMake(340, 200));
		_vObject.push_back(max);
	}
	//��� ������ - ü�� ȸ��ȿ�� - ������ �����
	for (int i = 0; i < 1; i++)
	{
		fieldObject* meattem;
		meattem = new meatItem;
		meattem->init("meatItem", meat, i * 0, PointMake(410, 200));
		_vObject.push_back(meattem);
	}

	//���� ������ - ü��ȸ����� - ������ �������
	for (int i = 0; i < 1; i++)
	{
		fieldObject* drinktem;
		drinktem = new drinkItem;
		drinktem->init("drinkItem", drink, i * 0, PointMake(480, 200));
		_vObject.push_back(drinktem);
	}

	//ü�� ������ - ü��ȸ��ȿ�� - ������ �������
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
					//�浹 ���� üũ LEFT
				case 0:
					pt.x = (*_viObject)->getPos().x - 25;
					pt.y = (*_viObject)->getPos().y;
					break;
					//�浹 ���� üũ TOP
				case 1:
					pt.x = (*_viObject)->getPos().x;
					pt.y = (*_viObject)->getPos().y - 25;
					break;
					//�浹 ���� üũ RIGHT
				case 2:
					pt.x = (*_viObject)->getPos().x + 25;
					pt.y = (*_viObject)->getPos().y;
					break;
					//�浹 ���� üũ BOTTOM
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
		//			//�浹 ���� üũ LEFT
		//		case 0:
		//			pt.x = (*_viObject)->getPos().x-25;
		//			pt.y = (*_viObject)->getPos().y;
		//			break;
		//			//�浹 ���� üũ TOP
		//		case 1:
		//			pt.x = (*_viObject)->getPos().x;
		//			pt.y = (*_viObject)->getPos().y-25;
		//			break;
		//			//�浹 ���� üũ RIGHT
		//		case 2:
		//			pt.x = (*_viObject)->getPos().x+25;
		//			pt.y = (*_viObject)->getPos().y;
		//			break;
		//			//�浹 ���� üũ BOTTOM
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
