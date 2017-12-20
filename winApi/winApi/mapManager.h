#pragma once
#include "gameNode.h"
#include "player.h"
#include "fieldObject.h"
#include "enemy.h"

class mapManager : public gameNode
{
private:
	vector<image*> _mapImageVector;
	vector<image*> _mapBackImageVector;
	vector<image*> _mapPixelCollisionVector;

	int _afterMapNumber;
	int _curMapNumber;

	player* _playerPos;
	vector<fieldObject*> _objectPos;
	vector<enemy*> _enemyPos;

	float _cameraX;
	float _cameraY;

	HDC mapDC;
	HBITMAP mapBit;
	HBITMAP mapOBit;

public:
	HRESULT init(void);
	void release(void);
	void update(player*, vector<fieldObject*>, vector<enemy*>);
	void render(void);

	void mapChange(int);

	mapManager() {}
	~mapManager() {}
};
