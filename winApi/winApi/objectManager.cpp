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
#include "mapObject01.h"
#include "mapObject02.h"
#include "mapObject02_1.h"
#include "mapObject03.h"
#include "fieldBoom0.h"
#include "fieldBoom0_1.h";
#include "fieldBoom2.h";
#include "fieldBoom2_1.h"
#include "fieldBoomleft.h"
#include "fieldBoomMid.h"
#include "fieldBoomRight.h"
#include "ending.h"

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
	IMAGEMANAGER->addFrameImage("맵01오브젝트", "image\\objectImage\\map01.bmp", 368, 77,1,1, true, RGB(255, 0, 255));

	//1맵 오브젝트
	IMAGEMANAGER->addFrameImage("맵02오브젝트", "image\\objectImage\\map02.bmp", 96 * 3, 54 * 3,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵02오브젝트1", "image\\objectImage\\map02Obj.bmp", 97 * 3, 30 * 3, 1,1,true, RGB(255, 0, 255));

	//맵2 오브젝트
	IMAGEMANAGER->addFrameImage("맵03오브젝트", "image\\objectImage\\map03Obj.bmp", 195, 96,1,1, true, RGB(255, 0, 255));

	//엔딩용 오브젝트
	IMAGEMANAGER->addFrameImage("log", "image/log.bmp", 400, 2000, 1, 1, true, RGB(255, 0, 255));



	fieldObject* _ending;
	_ending = new ending;
	_ending->init("end", ENDING, 4, PointMake(450, WINSIZEY+900 ));
	_vObject.push_back(_ending);
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

	for (int i = 0; i < 2; i++)
	{
		fieldObject* star;
		star = new StarBox;
		star->init("starBox", starbox,2, PointMake(607 + (i * 48.0f), 325));
		_vObject.push_back(star);
	}

	for (int i = 0; i < 2; i++)
	{
		fieldObject* star;
		star = new StarBox;
		star->init("starBox", starbox, 2, PointMake(1380 + (i * 48.0f), 131));
		_vObject.push_back(star);
	}

	fieldObject* star[3];
	star[0] = new StarBox;
	star[0]->init("starBox", starbox,3, PointMake(31 ,761));
	_vObject.push_back(star[0]);

	star[1] = new StarBox;
	star[1]->init("starBox", starbox, 3, PointMake(31, 500));
	_vObject.push_back(star[1]);

	fieldObject* meattem[4];
	meattem[0] = new meatItem;
	meattem[0]->init("meatItem", meat, 1, PointMake(2160, 117));
	_vObject.push_back(meattem[0]);

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			fieldObject* star;
			star = new StarBox;
			star->init("starBox", starbox, 1, PointMake(2130 + (j * 48.0f), 158 -(i * 40.0f)));
			_vObject.push_back(star);
		}
	}

	//돌 박스 - 플레이어 흡수 상호작용: 플레이어 좌표로 서서히 이동 / 폭탄연쇄반응 X

	fieldObject* boom[10];
	fieldObject* ston[3];

	boom[0] = new boomBox;
	boom[0]->init("boomBox", boombox, 0, PointMake(1200, 151));
	_vObject.push_back(boom[0]);

	ston[0] = new stonBox;
	ston[0]->init("stonBox", stonbox, 0, PointMake( 1200 , 151));
	_vObject.push_back(ston[0]);

	//폭탄 박스 - 플레이어 흡수X/폭탄 연쇄반응O
	boom[1] = new boomBox;
	boom[1]->init("boomBox", boombox, 0, PointMake(194, 296));
	_vObject.push_back(boom[1]);
	//2350,210
	boom[2] = new boomBox;
	boom[2]->init("boomBox", boombox, 0, PointMake(2360, 150));
	_vObject.push_back(boom[2]);
	//2200,407
	boom[3] = new boomBox;
	boom[3]->init("boomBox", boombox, 0, PointMake(2120, 407));
	_vObject.push_back(boom[3]);

	boom[4] = new boomBox;
	boom[4]->init("boomBox", boombox, 1, PointMake(1024, 80));
	_vObject.push_back(boom[4]);

	boom[5] = new boomBox;
	boom[5]->init("boomBox", boombox, 2, PointMake(459, 85));
	_vObject.push_back(boom[5]);

	boom[6] = new boomBox;
	boom[6]->init("boomBox", boombox, 2, PointMake(934, 58));
	_vObject.push_back(boom[6]);

	boom[7] = new boomBox;
	boom[7]->init("boomBox", boombox, 2, PointMake(1704, 418));
	_vObject.push_back(boom[7]);

	//아이언 박스 - 플레이어 흡수X/ 폭탄연쇄반응X
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, i * 0, PointMake(100 * (i + 5.0f), 200 * 2.0f));
		_vObject.push_back(iron);
	}
	for (int i = 0; i < 8; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 1, PointMake(21, 413 - (i * 40)));
		_vObject.push_back(iron);
	}
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 1, PointMake(1465, 416 - (i * 40)));
		_vObject.push_back(iron);
	}
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 1, PointMake(1465, 120 + (i * 40)));
		_vObject.push_back(iron);
	}
	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 1, PointMake(1465, 120 + (i * 40)));
		_vObject.push_back(iron);
	}
	for (int i = 0; i < 3; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 1, PointMake(1465 - (i * 48), 200));
		_vObject.push_back(iron);
	}

	for (int i = 0; i < 10; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 2, PointMake(31, 325 - (i * 40)));
		_vObject.push_back(iron);
	}

	for (int i = 0; i < 2; i++)
	{
		fieldObject* iron;
		iron = new ironBox;
		iron->init("ironBox", ironbox, 2, PointMake(990 - (i * 48), 420));
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
	for (int i = 0; i < 3; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 1, PointMake(1024, 40-(i*40.f)));
		_vObject.push_back(sand);
	}
	for (int i = 0; i < 8; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 1, PointMake(1024+(i*48.0f), -20));
		_vObject.push_back(sand);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fieldObject* sand;
			sand = new sandBox;
			sand->init("sandBox", sandbox, 1, PointMake(2850 + (i*48.0f), 480-(j*40.0f)));
			_vObject.push_back(sand);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fieldObject* sand;
			sand = new sandBox;
			sand->init("sandBox", sandbox, 0, PointMake(240 + (i * 48.0f), 455 -(j* 40.0f)));
			_vObject.push_back(sand);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 0, PointMake(2072 - (i * 48.0f), 407));
		_vObject.push_back(sand);
	}

	for (int i = 0; i < 4; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 2, PointMake(459,45 - (i * 40.0f)));
		_vObject.push_back(sand);
	}
	for (int i = 0; i < 10; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 2, PointMake(459+(i*48.0f), -115));
		_vObject.push_back(sand);
	}

	for (int i = 0; i < 10; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 2, PointMake(980 + (i*48.0f), -65));
		_vObject.push_back(sand);
	}

	for (int i = 0; i < 8; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(2172, 530 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
		for (int i = 0; i < 11; i++)
	{
		fieldObject* sand;
		sand = new sandBox;
		sand->init("sandBox", sandbox, 2, PointMake(2172 - (i*48.0f),570));
		_vObject.push_back(sand);
	}
	//몹 오브젝트 흡수x 연쇄 x 충돌시 플레이어에게 데미지
	fieldObject* MOB[8];
	MOB[0] = new mobBox;
	MOB[0]->init("mob", mob, 0, PointMake(2340,407));
	_vObject.push_back(MOB[0]);
	
	MOB[1] = new mobBox;
	MOB[1]->init("mob", mob, 1, PointMake(1465, 416));
	_vObject.push_back(MOB[1]);

	MOB[2] = new mobBox;
	MOB[2]->init("mob", mob, 1, PointMake(497, 118));
	_vObject.push_back(MOB[2]);
	MOB[3] = new mobBox;
	MOB[3]->init("mob", mob, 2, PointMake(938, 210));
	_vObject.push_back(MOB[3]);

	MOB[4] = new mobBox;
	MOB[4]->init("mob", mob, 2, PointMake(601, 30));
	_vObject.push_back(MOB[4]);

	MOB[5] = new mobBox;
	MOB[5]->init("mob", mob, 2, PointMake(3230, 160));
	_vObject.push_back(MOB[5]);

	MOB[6] = new mobBox;
	MOB[6]->init("mob", mob, 2, PointMake(2316, 20));
	_vObject.push_back(MOB[6]);
	//==================================== 오브젝트 끝 ==============================================//

	//===================== 아이템 ============================//

	//목숨업 아이템 - 플레이어 목숨 1 증가
	fieldObject* life[10];
	life[0] = new lifeItem;
	life[0]->init("lifeItem", upItem,0, PointMake(200, 200));
	_vObject.push_back(life[0]);

	life[2] = new lifeItem;
	life[2]->init("lifeItem", upItem, 2, PointMake(3581, 90));
	_vObject.push_back(life[2]);
	//493.118
	life[1] = new lifeItem;
	life[1]->init("lifeItem", upItem, 1, PointMake(493, 220));
	_vObject.push_back(life[1]);

	//캔디아이템 - 체력회복 효과 - 지민이 맘대로
	fieldObject* candy[10];
	candy[0] = new candyItem;
	candy[0]->init("candyItem", candyitem,0, PointMake(270, 200));
	_vObject.push_back(candy[0]);

	candy[1] = new candyItem;
	candy[1]->init("candyItem", candyitem, 1, PointMake(450, 220));
	_vObject.push_back(candy[1]);

	candy[2] = new candyItem;
	candy[2]->init("candyItem", candyitem, 2, PointMake(3437, 422));
	_vObject.push_back(candy[2]);

	//맥스 아이템 - 체력 풀 회복 효과
	fieldObject* max[4];
	max[0] = new maxItem;
	max[0]->init("maxItem", maxtem,0, PointMake(340, 200));
	_vObject.push_back(max[0]);

	max[1] = new maxItem;
	max[1]->init("maxItem", maxtem, 1, PointMake(1400, 120));
	_vObject.push_back(max[1]);

	//고기 아이템 - 체력 회복효과 - 지민이 맘대로
	meattem[1] = new meatItem;
	meattem[1]->init("meatItem", meat,0, PointMake(410, 200));
	_vObject.push_back(meattem[1]);

	meattem[2] = new meatItem;
	meattem[2]->init("meatItem", meat, 1, PointMake(530, 220));
	_vObject.push_back(meattem[2]);


	meattem[3] = new meatItem;
	meattem[3]->init("meatItem", meat, 2, PointMake(1181, 130));
	_vObject.push_back(meattem[3]);

	//음료 아이템 - 체력회뵥효과 - 지민이 마음대로
	fieldObject* drinktem[4];
	drinktem[0] = new drinkItem;
	drinktem[0]->init("drinkItem", drink,0, PointMake(480, 200));
	_vObject.push_back(drinktem[0]);

	drinktem[1] = new drinkItem;
	drinktem[1]->init("drinkItem", drink, 1, PointMake(2572, 419));
	_vObject.push_back(drinktem[1]);

	drinktem[2] = new drinkItem;
	drinktem[2]->init("drinkItem", drink, 2, PointMake(2619, 411));
	_vObject.push_back(drinktem[2]);

	//체리 아이템 - 체력회복효과 - 지민이 마음대로
	fieldObject* cherrytem[10];
	cherrytem[0] = new cherryItem;
	cherrytem[0]->init("cherryItem", cherry,0, PointMake(550, 200));
	_vObject.push_back(cherrytem[0]);

	cherrytem[1] = new cherryItem;
	cherrytem[1]->init("cherryItem", cherry, 0, PointMake(2000, 455));
	_vObject.push_back(cherrytem[1]);

	cherrytem[2] = new cherryItem;
	cherrytem[2]->init("cherryItem", cherry, 2, PointMake(175, 120));
	_vObject.push_back(cherrytem[2]);

	cherrytem[3] = new cherryItem;
	cherrytem[3]->init("cherryItem", cherry, 2, PointMake(318, 50));
	_vObject.push_back(cherrytem[3]);

	//===================== 아이템 끝 ============================//
	//===================== 맵 폭발 오브젝트 시작==========================//
	//맵1
	for (int i = 0; i < 10; i++)
	{
		fieldObject* level1_r;
		level1_r = new fieldBoom0;
		level1_r->init("sandBox", sandbox, 0, PointMake(2400,250 - (i* 40.0f)));
		_vObject.push_back(level1_r);
	}
	for (int i = 0; i < 10; i++)
	{
		fieldObject* level1_l;
		level1_l = new fieldBoom0_1;
		level1_l->init("sandBox", sandbox, 0, PointMake(2448, 250 - (i* 40.0f)));
		_vObject.push_back(level1_l);
	}
	//맵2 1187 437
	for (int i = 0; i < 20; i++)
	{
		fieldObject* level2_l;
		level2_l = new fieldBoomleft;
		level2_l->init("sandBox", sandbox, 1, PointMake(1187, 550 - (i* 40.0f)));
		_vObject.push_back(level2_l);
	}

	for (int i = 0; i < 10; i++)
	{
		fieldObject* level2_l;
		level2_l = new fieldBoomleft;
		level2_l->init("sandBox", sandbox, 1, PointMake(3434, 320 - (i* 40.0f)));
		_vObject.push_back(level2_l);
	}

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			fieldObject* level2_m;
			level2_m = new fieldBoomMid;
			level2_m->init("sandBox", sandbox, 1, PointMake(1235+(j*48.0f), 550 - (i* 40.0f)));
			_vObject.push_back(level2_m);
		}
	}

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			fieldObject* level2_m;
			level2_m = new fieldBoomMid;
			level2_m->init("sandBox", sandbox, 1, PointMake(3482 + (j*48.0f), 320 - (i* 40.0f)));
			_vObject.push_back(level2_m);
		}
	}

	for (int i = 0; i < 13; i++)
	{
		fieldObject* level2_r;
		level2_r = new fieldBoomRight;
		level2_r->init("sandBox", sandbox, 1, PointMake(1619, 550 - (i* 40.0f)));
		_vObject.push_back(level2_r);
	}

	boom[8] = new boomBox;
	boom[8]->init("boomBox", boombox, 1, PointMake(3434, 251));
	_vObject.push_back(boom[8]);
	ston[1] = new stonBox;
	ston[1]->init("stonBox", stonbox, 1, PointMake(3434, 251));
	_vObject.push_back(ston[1]);
	//839.365
	for (int i = 0; i < 3; i++)
	{
		fieldObject* level3_h;
		level3_h = new fieldBoom2_1;
		level3_h->init("sandBox", sandbox, 2, PointMake(1181 - (i* 48.0f), 175));
		_vObject.push_back(level3_h);
	}
	for (int i = 0; i < 13; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(839, 370 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 4; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(980, 55 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 13; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(1037, 175 + (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 8; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(1229, 175 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 8; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(2172, 530 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	//1704, 422
	for (int i = 0; i < 5; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(1704, 462 + (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 5; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(3296, 220 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	for (int i = 0; i < 12; i++)
	{
		fieldObject* level3_h;
		level3_h = new fieldBoom2_1;
		level3_h->init("sandBox", sandbox, 2, PointMake(3296 + (i* 48.0f), 220));
		_vObject.push_back(level3_h);
	}
	for (int i = 0; i < 5; i++)
	{
		fieldObject* level3_w;
		level3_w = new fieldBoom2;
		level3_w->init("sandBox", sandbox, 2, PointMake(3818, 422 - (i* 40.0f)));
		_vObject.push_back(level3_w);
	}
	boom[9] = new boomBox;
	boom[9]->init("boomBox", boombox, 2, PointMake(3818, 422));
	_vObject.push_back(boom[9]);
	ston[2] = new stonBox;
	ston[2]->init("stonBox", stonbox, 2, PointMake(3818, 422));
	_vObject.push_back(ston[2]);

	// =================== 맵 폭발 오브젝트 끝 ========================//
	//=======================맵 오브젝트 시작 =====================//
	fieldObject* map1_1[2];
	map1_1[0] = new mapObject01;
	map1_1[0]->init("map01_1", sandbox,0, PointMake(1200, 210));
	_vObject.push_back(map1_1[0]);

	map1_1[1] = new mapObject01;
	map1_1[1]->init("map01_1", sandbox, 0, PointMake(2060, 230));
	_vObject.push_back(map1_1[1]);

	//490.120

	//맵2
	fieldObject* map2_1[2];
	map2_1[0] = new mapObject02;
	map2_1[0]->init("map01_1", sandbox, 1, PointMake(490, 220));
	_vObject.push_back(map2_1[0]);
	//2229.120
	map2_1[1] = new mapObject02;
	map2_1[1]->init("map01_1", sandbox, 1, PointMake(2229, 220));
	_vObject.push_back(map2_1[1]);
	//2960.220
	fieldObject* map2_2[2];
	map2_2[0] = new mapObject02_1;
	map2_2[0]->init("map02_2", sandbox, 1, PointMake(2960, 220));
	_vObject.push_back(map2_2[0]);

	MOB[7] = new mobBox;
	MOB[7]->init("mob", mob, 1, PointMake(497, 118));
	_vObject.push_back(MOB[7]);

	fieldObject* map3[2];
	map3[0] = new mapObject03;
	map3[0]->init("map02_2", sandbox, 2, PointMake(1885, 100));
	_vObject.push_back(map3[0]);

	map3[1] = new mapObject03;
	map3[1]->init("map02_2", sandbox, 2, PointMake(1439, 200));
	_vObject.push_back(map3[1]);
	//======================맵 오브젝트 끝========================//
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

void objectManager::update(POINT playerPosition, vector<bullet*> bulletPos, int curMapNum)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end();)
	{
		if (curMapNum == (*_viObject)->getAppearMapNum())
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
		else
		{
			++_viObject;
		}
	}
}
