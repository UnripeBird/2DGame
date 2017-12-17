#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rc;
	int _x;
	int _y;
	float _width;

	image* _progressBarDown;
	image* _progressBarUp;

public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGuage(float currentScore, float maxScore);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	progressBar() {}
	virtual  ~progressBar() {}
};

