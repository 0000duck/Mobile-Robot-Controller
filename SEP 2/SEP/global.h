#pragma once


#include <random>
#include <ctime>
#include <iostream>
#include <functional>
#include "Common.h"

using namespace std;

class Ran{
public:
	int get(){
		return distribution(engine);
	}
	Ran(){
		random_device rd;
		mt19937_64 _engine(rd());                    // MT19937 난수 엔진
		engine = _engine;
		uniform_int_distribution<int> _distribution(0, 100);       // 생성 범위
		distribution = _distribution;
	}
private:
	mt19937_64 engine;
	uniform_int_distribution<int> distribution;       // 생성 범위
};

//센서, 로봇, 가상로봇, 실제맵 모두 글로벌로 미리 선언한다.(가상맵은 제외)

static int rotateDirection[POSSIBLEDIRECTION] = { UP, RIGHT, DOWN, LEFT };
//int **mapInput;
//여기부터 실제정보
//비록 robot이 가지고 있지만, 센서가 이 값을
						//가지는 것은 global로 가지는게 적절하다고 판단하여 함
	//실제 지도
/*
map
0,0		1,0

0,1		1,1
*///	지도형식
//여기까지 실제 정보


//여기부터 가상 정보
