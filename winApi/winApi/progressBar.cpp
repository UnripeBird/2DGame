#include "StdAfx.h"
#include "progressBar.h"

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, width, height);

	_progressBarDown = IMAGEMANAGER->addImage("barDown", "hpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_progressBarUp = IMAGEMANAGER->addImage("barUp", "hpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(),
		_progressBarDown->getHeight());
}

void progressBar::render(void)
{
	_progressBarDown->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2, 0, 0, _progressBarDown->getWidth(),
		_progressBarDown->getHeight());

	_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2, 0, 0, _width,
		_progressBarDown->getHeight());
}

void progressBar::setGuage(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}