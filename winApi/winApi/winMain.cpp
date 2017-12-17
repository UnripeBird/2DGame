#include "stdafx.h"
#include "mainGame.h"

//=====================
//	## 전역변수 ##
//=====================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

mainGame* _mg;

//======================
//	## 함수 전방선언 ##
//======================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//=======================
//	## 윈도우 메인함수 ##
//=======================
int APIENTRY WinMain(HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{

	_mg = new mainGame();

	//인스턴스를 전역변수에 담아둔다
	_hInstance = hInstance;

	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체

	//윈도우 구조체 선언 및 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//아이콘
	wndClass.hInstance = hInstance;									//인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//클래스 이름
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTARTX,				//윈도우 화면좌표 X
		WINSTARTY,				//윈도우 화면좌표 Y
		WINSIZEX,				//윈도우 화면 가로크기
		WINSIZEY,				//윈도우 화면 세로크기
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL					//윈도우 및 자식 윈도우를 생성하면 지정해주고 그렇지 않으면 NULL
	);

	//클라이언트 영역의 사이즈를 정확히 잡아준다
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, nCmdShow);

	//메인게임 클래스의 초기화 실패시 종료
	if (FAILED(_mg->init()))
	{
		return 0;
	}
	
	//MSG : 운영체제에서 발행하는 메세지 정보를 저장하기 위한 구조체
	MSG message;
	//메세지 루프
	//GetMessage : 메세지를 꺼내올 수 있을때까지 멈춰있는 함수
	//PeekMessage : 메세지가 없더라도 리턴되는 함수

	//게임용	
	while (true) 
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render(60.0f);
		}
	}
	

	//TranslateMessage : 키보드 입력메세지 처리를 담당
	//입력된 키가 문자키인지 확인후 대문자 혹은 소문자, 한글, 영문인지에 대한 
	//WM_CHAR 메세지 발생시킨다
	//DispatchMessage : 윈도우 프로시져에서 전달된 메세지를 실제 윈도우로 전달해준다

	//일반 프로그래밍용
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();

	//윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//윈도우 프로시져 : 메세지를 운영체제에 전달하고 코딩하는 구간
//hWnd : 어느 윈도우에서 발생한 메세지인지 구분
//iMessage : 메세지 구분 번호
//wParam : unsigned int 마우스 버튼의 상태, 키보드 조합키의 상태를 전달
//lParam : unsigned long 마우스 클릭 좌표를 전달(x, y)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//=================================================================
//	## 윈도우 크기 조정 ## (클라이언트 영역의 사이즈를 정확히 잡아준다)
//=================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	//위 렉트 정보로 윈도우 클라이언트 사이즈 셋팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}