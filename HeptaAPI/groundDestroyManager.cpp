#include "stdafx.h"
#include "groundDestroyManager.h"



groundDestroyManager::groundDestroyManager()
{
}


groundDestroyManager::~groundDestroyManager()
{
}

									// 그려질 dc, 파괴된 곳 매꿔줄 컬러, 터질 위치,  터지는 각도, 터지는 크기, 터지는 횟수, 줄어들 비율, 터지는 모드
void groundDestroyManager::destroy(HDC hdc, COLORREF color, POINT point, float angle, float radius, int num, float ratio, DESTROY_MODE mode)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oPen = (HPEN)SelectObject(hdc, pen);
	switch(mode)
	{
		case DESTROY_CIRCLE:
			for (int i = 0; i < num; ++i)
			{
				EllipseMakeCenter(hdc, point.x, point.y, radius * 2, radius * 2);
				point.x += cos(angle) * radius;
				point.y += -sin(angle) * radius;
				radius *= ratio;

				if (radius < 0) break;
			}
		break;

		case DESTROY_RECTANGLE:
			for (int i = 0; i < num; ++i)
			{
				RectangleMakeCenter(hdc, point.x, point.y, radius * 2, radius * 2);
				point.x += cos(angle) * radius;
				point.y += -sin(angle) * radius;
				radius *= ratio;

				if (radius < 0) break;
			}
		break;
	}
	SelectObject(hdc, oBrush);
	SelectObject(hdc, oPen);
	DeleteObject(brush);
	DeleteObject(pen);
	DeleteObject(oBrush);
	DeleteObject(oPen);
}

// 그려질 dc, 파괴된 곳 매꿔줄 컬러, 터질 위치들 담은 벡터
void groundDestroyManager::napalm(HDC hdc, COLORREF color, vector<POINT> point)
{
	int radius = 3;
	float angle = -PI / 2;

	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oPen = (HPEN)SelectObject(hdc, pen);

	for (int count = 0; count < point.size(); ++count)
	{
		radius = 3;

		for (int i = 0; i < 3; ++i)
		{
			EllipseMakeCenter(hdc, point[count].x, point[count].y, radius * 2, radius);
			point[count].x += cos(angle) * radius / 2;
			point[count].y += -sin(angle) * radius / 2;
			radius--;

			if (radius < 0) break;
		}
	}

	SelectObject(hdc, oBrush);
	SelectObject(hdc, oPen);
	DeleteObject(brush);
	DeleteObject(pen);
	DeleteObject(oBrush);
	DeleteObject(oPen);
}