#pragma once
#include "gameNode.h"

class jumpSample : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jumpSample() {}
	~jumpSample() {}
};

