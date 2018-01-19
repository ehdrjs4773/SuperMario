#pragma once
#include "singletonBase.h"
#include <vector>

// 터지는 모드
enum DESTROY_MODE
{
	DESTROY_CIRCLE,		// 땅이 둥글게 파임
	DESTROY_RECTANGLE,	// 땅이 네모나게 파임
	DESTROY_NAPALM,		// 네이팜 처리
	DESTROY_END
};

class groundDestroyManager : public singletonBase<groundDestroyManager>
{
public:
	groundDestroyManager();
	~groundDestroyManager();

			// 그려질 dc, 파괴된 곳 매꿔줄 컬러, 터질 위치, 터지는 각도, 터지는 크기, 터지는 횟수, 줄어들 비율, 터지는 모드
	void destroy(HDC hdc, COLORREF color, POINT point, float angle, float radius, int num, float ratio, DESTROY_MODE mode);
			// 그려질 dc, 파괴된 곳 매꿔줄 컬러, 터질 위치들 담은 벡터
	void napalm(HDC hdc, COLORREF color, vector<POINT> point);
};

