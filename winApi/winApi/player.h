#pragma once
#include "fieldObject.h"
#include "enemy.h"
#include "animation.h"

#define PLAYERSPEED 2.5
#define FILENUM 4

class player
{
private:
	float _x;
	float _y;

	int _starFrame, _endFrame;

	string _fileName[FILENUM];
	int _fileNum;
	int _pose;
	bool _curRight;
	int _keyDownNum;
	bool _playAni;
	bool _alreadyMove;

	float DubbleKeyTimer;
	float DublleKeyWorldTimer;

	image* _image;
	animation* _ani;
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

	image* getImage() { return _image; }
	animation* getAni() { return _ani; }

	player() {}
	~player() {}
};

