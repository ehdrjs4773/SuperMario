#pragma once
#include "gameNode.h"
#include "selectScene.h"
#include "stageScene.h"

class playGround : public gameNode
{
private:
	//============ 실 험 용 테 스 트 ==== by 동건===//
	float _x, _y; //화면 확대 움직임!!
	BOOL _BackGround; // 뒷배경 때문에 만든 실험용

	//============ 노 터 치 데 스 ======= by 동건 ==//


public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

	playGround();
	~playGround();
};

