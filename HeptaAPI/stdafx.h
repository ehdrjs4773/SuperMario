// stdafx.h : �̸� �����ϵ� ������� : ���� ����ϴ� �͵��� �̸� ������ �δ� ��
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"

// ��ü����
#include "groundDestroyManager.h"
#include "cameraManager.h"

using namespace std;
using namespace HEPTA_UTIL;

//=======================================================
// ## ������ ���� ������ ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("Hepta Window API")
#define WINSTARTX	50		//������ ������ǥ X
#define WINSTARTY	50		//������ ������ǥ Y
#define WINSIZEX	900		//������ ����ũ��
#define WINSIZEY	600		//������ ����ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define DATABASE		database::getSingleton()

// ��ü����
#define DESTROY			groundDestroyManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()

#define BLACK		RGB(0, 0, 0)
#define RED			RGB(255, 0, 0)
#define GREEN		RGB(0, 255, 0)
#define BLUE 		RGB(0, 0, 255)
#define MAGENTA		RGB(255, 0, 255)
#define CYAN		RGB(0, 255, 255)
#define YELLOW		RGB(255, 255, 0)
#define WHITE		RGB(255, 255, 255)

//=======================================================
// ## ��ũ�� ## 2017.11.15 ##
//=======================================================

#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}

//=======================================================
// ## ������ ���� extern ## 2017.11.08 ##
//=======================================================

extern HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
extern HWND			_hWnd;			//�ڵ�
extern POINT		_ptMouse;

extern bool _isDebug;