#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init(void)
{
	IMAGEMANAGER->addImage("스타트", "image/시작화면.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("알파", "image/알파(시작).bmp", 1000, 100, true, RGB(255, 0, 255));

	_alpha = 255;

	return S_OK;
}

void startScene::release(void)
{
}

void startScene::update(void)
{
	_alpha -= 3.0f;
	if (_alpha <= 0) _alpha = 255;
}

void startScene::render(void)
{
	IMAGEMANAGER->render("스타트", getMemDC());

	IMAGEMANAGER->alphaRender("알파", getMemDC(), 130, WINSIZEY / 2 + 220, _alpha);
}
