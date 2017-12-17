#include "stdafx.h"
#include "animation.h"

animation::animation() : _frameNum(0),
						 _frameWidth(0),
						 _frameHeight(0),
						 _frameNumWidth(0),
						 _frameNumHeight(0),
						 _loop(FALSE),
						 _frameUpdateSec(0),
						 _elapsedSec(0),
						 _nowPlayIdx(0),
						 _isPlay(FALSE)
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 수
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 리스트에 추가
			_frameList.push_back(framePos);
		}
	}

	//먼저 기본 프레임으로 셋팅
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{
}

//기본 프레임 셋팅
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//루프 돌건지
	_loop = loop;

	_playList.clear();

	//다시 돌아오냐?
	if (reverse)
	{
		//루프?
		if (_loop)
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//편도
	else 
	{
		//갈때 프레임
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//원하는 프레임만 재생
void animation::setPlayFrame(int * playArr, int arrLen, BOOL loop)
{
	//루프
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//갈때 프레임
	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//구간을 잘라서 재생
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.push_back(start);
		return;
	}

	if (start > end)
	{
		//다시 돌아오냐?
		if (reverse)
		{
			if (_loop)
			{
				//갈때 프레임
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				//올때 프레임
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				//갈때 프레임
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				//올때 프레임
				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		//편도
		else
		{
			//갈때 프레임
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				//갈때 프레임
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				//올때 프레임
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				//갈때 프레임
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				//올때 프레임
				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		//편도
		else
		{
			//갈때 프레임
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

//초당 프레임 갱신 횟수
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//프레임 업데이트
void animation::frameUpdate(float elpasedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elpasedTime;

		//프레임 업데이트 시간이 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{				
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_isPlay = false;
				}
			}
		}
	}
}

void animation::start(void)
{
	_isPlay = true;
	_nowPlayIdx = 0;
}

void animation::stop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void animation::pause(void)
{
	_isPlay = false;
}

void animation::resume(void)
{
	_isPlay = TRUE;
}