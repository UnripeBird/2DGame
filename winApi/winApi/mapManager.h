#pragma once
#include "gameNode.h"
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

	POINT _playerPos;
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
	void update(POINT, vector<fieldObject*>, vector<enemy*>);
	void render(void);

	void mapChange(int);

	mapManager() {}
	~mapManager() {}
};

