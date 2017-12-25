// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN

// Windows 헤더 파일:
#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//======================================
//	## 내가 만든 헤더파일을 이곳에 추가 ##
//======================================
#include "commonMacroFiunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "sceneManager.h"

using namespace MY_UTIL;

//================================
//	## 싱글톤을 이곳에 추가한다 ##
//================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()

//================================
//	## 매크로 ## (윈도우창 초기화)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		400
#define WINSTARTY		100
#define WINSIZEX		800
#define WINSIZEY		500
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## 매크로 함수 ## (클래스에서 동적할당된 부분 해제)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## 전역변수 ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

typedef enum OBJECTDISCERN
{
	//스타박스 - 흡수 가능한 하얀색 별 박스
	//붐 박스 - 폭탄 오브젝트
	//스톤 박스 - 플레이어 흡수 시에만 움직이는 박스
	//물 - 오브젝트 안에 있을경우 수영 애니메이션 출력
	//아이언 - 폭탄 파괴 x 플레이어 흡수 x
	starbox,boombox,stonbox,water,ironbox,sandbox,

	//업 아이템 - 목숨 1 증가 아이템
	//캔디 아이템 - 체력 증가 - 지민이 맘대로
	//맥스 아이템 - 체력 풀 회복
	//고기 아이템 - 체력 회복 - 지민이 맘대로
	//음료 아이템 - 체력 회복 - 지민이 맘대로
	//체리 아이템 - 체력회복 - 지민이 맘대로
	upItem,candyitem,maxtem,meat,drink,cherry
};

typedef enum ENEMYDISCERN
{
	enemyBox,
	waddledee,
	Frog,
	Bronto,
	Burning,
	Spark,
	chilly
};