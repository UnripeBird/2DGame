#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(void)
{
	IMAGEMANAGER->addImage("titleback", "image\\titleback.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("titlebar", "image\\titlebar.bmp", 713, 68);

	_alpha;
	return S_OK;
}

void titleScene::release(void)
{
}

void titleScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("play");
	}
	_alpha += 3;
	if (_alpha > 150) _alpha = 0;
}

void titleScene::render(void)
{
	IMAGEMANAGER->render("titleback", getMemDC());
	IMAGEMANAGER->alphaRender("titlebar", getMemDC(), 44, 366, _alpha);
}
