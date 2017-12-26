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
	//�ڽ�
	IMAGEMANAGER->addFrameImage("�ڽ�������Ʈ", "image\\objectImage\\object.bmp", 48, 288, 1, 7);
	//Ŀ�� �극�� ��ȣ�ۿ� �ڽ� ����
	IMAGEMANAGER->addFrameImage("�����̹���", "image\\objectImage\\boomObject.bmp", 240, 48, 5, 1, true, RGB(149, 177, 200));
	//������
	IMAGEMANAGER->addFrameImage("������", "image\\objectImage\\item.bmp", 384, 384, 6, 6, true, RGB(12, 230, 248));
	//Ŀ�� �극�� ������Ʈ �浹�� �극�� ����
	IMAGEMANAGER->addFrameImage("�Ѿ�����", "image\\objectImage\\bulletBoom.bmp",276, 48, 6, 1, true, RGB(49, 0, 148));
	//�� ������Ʈ �̹���
	IMAGEMANAGER->addFrameImage("��������Ʈ", "image\\objectImage\\starObject.bmp", 48, 48,1,1, true, RGB(207, 176, 255));
	//������Ʈ ���� 
	IMAGEMANAGER->addFrameImage("����", "image\\objectImage\\mopObject.bmp", 246, 66, 4, 1, true, RGB(0, 219, 255));
	
	//�ʵ�0,1,2 ������Ʈ

	//0,1,2��� ������Ʈ ���߿�
	IMAGEMANAGER->addFrameImage("������", "image\\objectImage\\mapBoom.bmp",144, 144,3,3, true, RGB(255, 0, 255));
	
	//0�� ������Ʈ
	IMAGEMANAGER->addFrameImage("��01������Ʈ", "image\\objectImage\\map01.bmp", 387, 138,1,1, true, RGB(255, 0, 255));

	//1�� ������Ʈ
	IMAGEMANAGER->addFrameImage("��02������Ʈ", "image\\objectImage\\map02.bmp", 96 * 3, 54 * 3,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��02������Ʈ1", "image\\objectImage\\map02Obj.bmp", 97 * 3, 30 * 3, 1,1,true, RGB(255, 0, 255));

	//��2 ������Ʈ
	IMAGEMANAGER->addFrameImage("��03������Ʈ", "image\\objectImage\\map03Obj.bmp", 195, 96,1,1, true, RGB(255, 0, 255));


	//==================================== ������Ʈ ==============================================//
	//��Ÿ�ڽ� - �÷��̾� ��� ��ȣ�ۿ� : �÷��̾ ��ų���ְ� �������� ��밡�� / ��ź �������O
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

	//�� �ڽ� - �÷��̾� ��� ��ȣ�ۿ�: �÷��̾� ��ǥ�� ������ �̵� / ��ź������� X
	for (int i = 0; i < 7; i++)
	{
		fieldObject* ston;
		ston = new stonBox;
		ston->init("stonBox", stonbox, i * 0, PointMake(150 * (i + 5.0f), 300 * 2.0f));
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
		iron->init("ironBox", ironbox, i * 0, PointMake(100 * (i + 5.0f), 200 * 2.0f));
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

	for (int i = 0; i < 4; i++)
	{
		fieldObject* MOB;
		MOB = new mobBox;
		MOB->init("mob", mob, i * 0, PointMake(80, 60*(i + 5.0f)));
		_vObject.push_back(MOB);
	}
	//==================================== ������Ʈ �� ==============================================//

	//===================== ������ ============================//

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

	//���� ������ - ü��ȸ��ȿ�� - ������ �������
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
	//===================== ������ �� ============================//
	//===================== �� ������Ʈ ����==========================//

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
		//���ڽ�, ������ �÷��̾� ����� �������
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
