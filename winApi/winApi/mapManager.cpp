#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init(void)
{
	_mapBackImageVector.push_back(IMAGEMANAGER->findImage("background0"));
	_mapImageVector.push_back(IMAGEMANAGER->findImage("field0"));
	_mapPixelCollisionVector.push_back(IMAGEMANAGER->findImage("pixel0"));

	mapDC = CreateCompatibleDC(getMemDC()); // 그냥 써
	mapBit = NULL;
	mapOBit = NULL;

	mapChange(0);

	_cameraX = 0;
	_cameraY = 0;

	_afterMapNumber = 0;
	_curMapNumber = 0;
	return S_OK;
}

void mapManager::release(void)
{
	_mapBackImageVector.clear();
	_mapImageVector.clear();
	_mapPixelCollisionVector.clear();
}

void mapManager::update(player* playerPos, vector<fieldObject*> objectPos, vector<enemy*> enemyPos, vector<bullet*> bulletPos)
{
	_playerPos = playerPos;
	_objectPos = objectPos;
	_enemyPos = enemyPos;
	_bulletPos = bulletPos;

	POINT playerPosition = _playerPos->getPos();

	_cameraX = playerPosition.x - WINSIZEX / 2;
	_cameraY = playerPosition.y - WINSIZEY / 2;
	if (_cameraX < 0) _cameraX = 0;
	else if (_cameraX + WINSIZEX > _mapImageVector[_curMapNumber]->getWidth()) _cameraX = _mapImageVector[_curMapNumber]->getWidth() - WINSIZEX;
	if (_cameraY < 0) _cameraY = 0;
	else if (_cameraY + WINSIZEY > _mapImageVector[_curMapNumber]->getHeight()) _cameraY = _mapImageVector[_curMapNumber]->getHeight() - WINSIZEY;
}

void mapManager::render(void)
{
	POINT playerPosition = _playerPos->getPos();
	POINT playerImagePosition = _playerPos->getImagePos();

	_mapBackImageVector[_curMapNumber]->render(mapDC, _cameraX - ((_cameraX / (_mapBackImageVector[_curMapNumber]->getWidth() - WINSIZEX)) * 100), _cameraY);
	_mapImageVector[_curMapNumber]->render(mapDC, 0, 0);
	
	Rectangle(mapDC, playerPosition.x - 25, playerPosition.y - 25, playerPosition.x + 25, playerPosition.y + 25);
	_playerPos->getImage()->aniRender(mapDC, _playerPos->getImagePos().x, _playerPos->getImagePos().y, _playerPos->getAni());

	for (int i = 0; i < _objectPos.size(); i++)
	{
		if (_objectPos[i]->getAppearMapNum() == _curMapNumber)
		{
			//Rectangle(mapDC, _objectPos[i]->getrc().left, _objectPos[i]->getrc().top, _objectPos[i]->getrc().right, _objectPos[i]->getrc().bottom);
			_objectPos[i]->getImage()->frameRender(mapDC, _objectPos[i]->getrc().left, _objectPos[i]->getrc().top, _objectPos[i]->getObjNumberX(), _objectPos[i]->getObjNumberY());
		}
	}

	for (int i = 0; i < _enemyPos.size(); i++)
	{
		if (_enemyPos[i]->getAppearMapNum() == _curMapNumber)
		{
			Rectangle(mapDC, _enemyPos[i]->getrc().left, _enemyPos[i]->getrc().top, _enemyPos[i]->getrc().right, _enemyPos[i]->getrc().bottom);
			for (int j = 0; j < 4; j++)
			{
				Rectangle(mapDC, _enemyPos[i]->getprobex(j).left, _enemyPos[i]->getprobex(j).top, _enemyPos[i]->getprobex(j).right, _enemyPos[i]->getprobex(j).bottom);
				
			}
			
			if (_enemyPos[i]->getframex() != -1)
			{
				_enemyPos[i]->getimage()->frameRender(mapDC, _enemyPos[i]->getPos().x - (_enemyPos[i]->getimage()->getFrameWidth() / 2)
					, _enemyPos[i]->getPos().y - (_enemyPos[i]->getimage()->getFrameHeight() / 2) + 25,
					_enemyPos[i]->getframex(), _enemyPos[i]->getframey());
			}
			else
			{
				_enemyPos[i]->getimage()->aniRender(mapDC, _enemyPos[i]->getPos().x - (_enemyPos[i]->getimage()->getFrameWidth() / 2)
					, _enemyPos[i]->getPos().y - (_enemyPos[i]->getimage()->getFrameHeight() / 2) + 25,
					_enemyPos[i]->getAni());
			}
		}
	}

	for (int i = 0; i < _bulletPos.size(); i++)
	{
		_bulletPos[i]->getImage()->frameRender(mapDC,
			_bulletPos[i]->getPos().x - (_bulletPos[i]->getImage()->getFrameWidth() / 2),
			_bulletPos[i]->getPos().y - (_bulletPos[i]->getImage()->getFrameHeight() / 2),
			_bulletPos[i]->getImageFrame().x, _bulletPos[i]->getImageFrame().y);
	}

	BitBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, // 0 0,화면크기 고정: 
		mapDC, _cameraX, _cameraY, SRCCOPY);
}

void mapManager::mapChange(int nextMap)
{
	_afterMapNumber = _curMapNumber;
	_curMapNumber = nextMap;

	if (mapBit != NULL)
	{
		SelectObject(mapDC, mapOBit);
		DeleteObject(mapBit);
	}

	mapBit = (HBITMAP)CreateCompatibleBitmap(getMemDC(), _mapImageVector[nextMap]->getWidth(), _mapImageVector[nextMap]->getHeight()); //맵 크기만큼의 빈 비트맵을 생성한다
	mapOBit = (HBITMAP)SelectObject(mapDC, mapBit);
}
