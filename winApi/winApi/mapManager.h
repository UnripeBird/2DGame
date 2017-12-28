#pragma once
#include "gameNode.h"
#include "player.h"
#include "fieldObject.h"
#include "enemy.h"
#include "bullet.h"

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
	vector<bullet*> _bulletPos;
	vector<bullet*> _enemyBullet;

	float _cameraX;
	float _cameraY;

	HDC mapDC;
	HBITMAP mapBit;
	HBITMAP mapOBit;

public:
	HRESULT init(void);
	void release(void);
	void update(player*, vector<fieldObject*>, vector<enemy*>, vector<bullet*>, vector<bullet*>);
	void render(void);

	void mapChange(int);

	image* getPixelImage() { return _mapPixelCollisionVector[_curMapNumber]; }
	int getCurMapNum() { return _curMapNumber; }
	mapManager() {}
	~mapManager() {}
};

