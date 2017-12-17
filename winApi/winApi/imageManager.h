#pragma once
#include "singletonBase.h"
#include "image.h"

/*STL 맵의 핵심*/
//키, 값 을 잊지 말자
//첫번째 first -> 키
//두번째 second -> 값
//추가하는 방법은 insert를 사용하고 키와 밸류 두개를 동시에 추가해야 하니 
//pair와 make_pair를 사용하여 추가하면 된다

class imageManager : public singletonBase<imageManager>
{
private:
	//맵으로 만든 이미지목록
	typedef map<string, image*> mapImageList;
	//맵으로 만든 이미지목록의 반복자
	typedef map<string, image*>::iterator mapImageIter;

private:
	//실제 이미지클래스를 담을 맵
	mapImageList _mImageList;

public:
	//이미지매니져 초기화
	HRESULT init(void);
	//이미지매니져 해제
	void release(void);

	//빈 비트맵으로 초기화
	image* addImage(string strKey, int width, int height);
	//이미지 파일로 초기화(주 사용)
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 초기화(주 사용)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll();

	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파 렌더 (내가 지정한 좌표에 알파값과 함께 이미지 출력한다)
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 렌더 
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//루프렌더	
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	
	imageManager() {}
	~imageManager() {}
};

