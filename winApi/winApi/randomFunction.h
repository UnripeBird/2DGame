#pragma once

#include "singletonBase.h"
#include <time.h>

//======================
//	## randomFunction ## 
//======================
class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num) { return rand() % num; }

	//주의사항 -> 0이 나오면 터진다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};

