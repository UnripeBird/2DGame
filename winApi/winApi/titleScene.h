#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private:
	int _alpha;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	titleScene() {}
	~titleScene() {}
};

