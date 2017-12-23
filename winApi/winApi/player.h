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
	int _curJump;
	int _maxJump;
	int _curSliding;
	int _maxSliding;
	int _gravity;

	int _starFrame, _endFrame;

	string _fileName[FILENUM];
	int _fileNum;
	int _pose;
	int _aniControl;
	int _keyDownNum;
	bool _curRight;
	bool _playAni;
	bool _curSwallow;

	float DubbleKeyTimer;
	float DublleKeyWorldTimer;

	image* _image;
	animation* _ani;
	RECT _rc;

	image* _pixelImage;
public:
	HRESULT init(void);
	void release(void);
	void update(vector<fieldObject*>, vector<enemy*>, image*);

	void move(vector<fieldObject*>);
	void moveCollision(vector<fieldObject*>, int);

	bool objectCollision(vector<fieldObject*>);
	void objectCollisionReaction(vector<fieldObject*>, int);

	bool enemyCollision(vector<enemy*>);
	void enemyCollisionReaction(vector<enemy*>, int);

	bool rightMove();
	bool leftMove();

	POINT getPos() { return PointMake(_x, _y); }

	image* getImage() { return _image; }
	animation* getAni() { return _ani; }

	player() {}
	~player() {}
};

