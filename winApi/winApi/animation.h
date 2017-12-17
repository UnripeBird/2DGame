#pragma once

class animation 
{
private:
	//프레임 리스트
	typedef vector<POINT> _vFrameList;	
	//프레임 플레이 리스트
	typedef vector<int> _vPlayList;	

private:
	int _frameNum;			//프레임 수

	_vFrameList _frameList;	//프레임 위치 리스트
	_vPlayList _playList;	//플레이 리스트

	int _frameWidth;		//프레임 가로크기
	int _frameHeight;		//프레임 세로크기

	int _frameNumWidth;		//가로 프레임 총 갯수
	int _frameNumHeight;	//세로 프레임 총 갯수

	BOOL _loop;				//루프?
	float _frameUpdateSec;	//초당 프레임 업데이트수
	float _elapsedSec;		//프레임과 프레임 사이의 시간

	DWORD _nowPlayIdx;		//현재 플레이 인덱스
	BOOL _isPlay;			//플레이 중이냐?
	
public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setDefPlayFrame(BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(int* playArr = NULL, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(int start, int end, BOOL reverse = NULL, BOOL loop = NULL);

	//초당 프레임 갱신 횟수
	void setFPS(int framePerSec);

	//프레임 업데이트
	void frameUpdate(float elpasedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	//플레이 중이냐?
	inline BOOL isPlay(void) { return _isPlay; }

	//프레임위치 얻어온다
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	//현재 애니메이션 프레임 위치 순서를 얻어온다
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;
		return frameX + frameY * _frameNumWidth;
	}

	//프레임 가로크기를 얻어온다
	inline int getFrameWidth(void) { return _frameWidth; }

	//프레임 세로크기를 얻어온다
	inline int getFrameHeight(void) { return _frameHeight; }

	//현재 몇번쨰 프레임 순서인지 얻는다
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	animation(void);
	~animation() {}
};

