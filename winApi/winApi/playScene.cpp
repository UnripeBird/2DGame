#include "stdafx.h"
#include "playScene.h"

HRESULT playScene::init(void)
{
	IMAGEMANAGER->addImage("background0", "image\\background0.bmp", 1280, 569);
	IMAGEMANAGER->addImage("field0", "image\\field0.bmp", 1007 * 3, 200 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixel0", "image\\pixel0.bmp", 1007 * 3, 200 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("background1", "image\\background1.bmp", 1280, 569);
	IMAGEMANAGER->addImage("field1", "image\\field1.bmp", 1200 * 3, 200 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixel1", "image\\pixel1.bmp", 1200 * 3, 200 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("background2", "image\\background2.bmp", 1280, 570);	
	IMAGEMANAGER->addImage("field2", "image\\field2.bmp", 1280 * 3, 178 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixel2", "image\\pixel2.bmp", 1280 * 3, 178 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("bossmapback", "image\\treebossmapback.bmp", 358 * 4, 159 * 4);
	IMAGEMANAGER->addImage("bossmap", "image\\treebossmap.bmp", 300 * 3, 300 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossmappixel", "image\\treebosspixel.bmp", 300 * 3, 300 * 3, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("ending", "image\\endingBack.bmp", 1280, 570);
	IMAGEMANAGER->addImage("ending", "image\\endingBack.bmp", 1280, 570);
	IMAGEMANAGER->addImage("endingpixel", "image\\pixel4.bmp", 300 * 12, 300 * 3, true, RGB(255, 0, 255));

	_mapManager = new mapManager;
	_mapManager->init();

	_player = new player;
	_player->init();

	_objectManager = new objectManager;
	_objectManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_bulletManager = new bulletManager;
	_bulletManager->init();
	return S_OK;
}

void playScene::release(void)
{
	_mapManager->release();
	SAFE_DELETE(_mapManager);

	_player->release();
	SAFE_DELETE(_player);

	_objectManager->release();
	SAFE_DELETE(_objectManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_bulletManager->release();
	SAFE_DELETE(_bulletManager);
}

void playScene::update(void)
{
	_bulletManager->update();


	_player->update(_objectManager->getObject(), _enemyManager->getEnemy(),_mapManager->getPixelImage(), _bulletManager,_mapManager->getCurMapNum());

	_objectManager->update(_player->getPos(), _bulletManager->getBullet(), _mapManager->getCurMapNum());

	_enemyManager->update(_mapManager->getPixelImage(), _player->getPos(),_objectManager->getObject(),_bulletManager->getBullet(),_mapManager->getCurMapNum(), _bulletManager);

	_mapManager->update(_player, _objectManager->getObject(), _enemyManager->getEnemy(), _bulletManager->getBullet(), _bulletManager->getEnemyBullet());
}

void playScene::render(void)
{
	_mapManager->render();
}
