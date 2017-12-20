#pragma once
#include "gameNode.h"
#include "mapManager.h"
#include "player.h"
#include "objectManager.h"
#include "enemyManager.h"

class playScene : public gameNode
{
private:
	mapManager* _mapManager;
	player* _player;
	objectManager* _objectManager;
	enemyManager* _enemyManager;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playScene() {}
	~playScene() {}
};
