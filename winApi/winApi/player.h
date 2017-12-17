#pragma once
#include "fieldObject.h"
#include "enemy.h"

#define PLAYERSPEED 3

class player
{
private:
	float _x;
	float _y;

	RECT _rc;

public:
	HRESULT init(void);
	void release(void);
	void update(vector<fieldObject*>, vector<enemy*>);

	void move(vector<fieldObject*>);
	void moveCollision(vector<fieldObject*>, int);

	bool objectCollision(vector<fieldObject*>);
	void objectCollisionReaction(vector<fieldObject*>, int);

	bool enemyCollision(vector<enemy*>);
	void enemyCollisionReaction(vector<enemy*>, int);

	POINT getPos() { return PointMake(_x, _y); }

	player() {}
	~player() {}
};

