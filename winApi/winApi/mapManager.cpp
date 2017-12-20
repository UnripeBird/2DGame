#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init(void)
{
	_mapBackImageVector.push_back(IMAGEMANAGER->findImage("background0"));

	mapDC = CreateCompatibleDC(getMemDC()); // �׳� ��
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

void mapManager::update(player* playerPos, vector<fieldObject*> objectPos, vector<enemy*> enemyPos)
{
	_playerPos = playerPos;
	_objectPos = objectPos;
	_enemyPos = enemyPos;

	POINT playerPosition = _playerPos->getPos();

	_cameraX = playerPosition.x - WINSIZEX / 2;
	_cameraY = playerPosition.y - WINSIZEY / 2;
	if (_cameraX < 0) _cameraX = 0;
	else if (_cameraX + WINSIZEX > _mapBackImageVector[_curMapNumber]->getWidth()) _cameraX = _mapBackImageVector[_curMapNumber]->getWidth() - WINSIZEX;
	if (_cameraY < 0) _cameraY = 0;
	else if (_cameraY + WINSIZEY > _mapBackImageVector[_curMapNumber]->getHeight()) _cameraY = _mapBackImageVector[_curMapNumber]->getHeight() - WINSIZEY;
}

void mapManager::render(void)
{
	POINT playerPosition = _playerPos->getPos();

	_mapBackImageVector[_curMapNumber]->render(mapDC, 0, 0);
	
	Rectangle(mapDC, playerPosition.x - 25, playerPosition.y - 25, playerPosition.x + 25, playerPosition.y + 25);

	for (int i = 0; i < _objectPos.size(); i++)
	{
		if(_objectPos[i]->getAppearMapNum() == _curMapNumber)
			Rectangle(mapDC, _objectPos[i]->getrc().left, _objectPos[i]->getrc().top, _objectPos[i]->getrc().right, _objectPos[i]->getrc().bottom);
	}

	for (int i = 0; i < _enemyPos.size(); i++)
	{
		if (_enemyPos[i]->getAppearMapNum() == _curMapNumber)
			Rectangle(mapDC, _enemyPos[i]->getrc().left, _enemyPos[i]->getrc().top, _enemyPos[i]->getrc().right, _enemyPos[i]->getrc().bottom);
	}

	BitBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, // 0 0,ȭ��ũ�� ����: 
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

	mapBit = (HBITMAP)CreateCompatibleBitmap(getMemDC(), _mapBackImageVector[nextMap]->getWidth(),_mapBackImageVector[nextMap]->getHeight()); //�� ũ�⸸ŭ�� �� ��Ʈ���� �����Ѵ�
	mapOBit = (HBITMAP)SelectObject(mapDC, mapBit);
}