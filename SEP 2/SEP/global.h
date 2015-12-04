#pragma once

#include "Common.h"

//센서, 로봇, 가상로봇, 실제맵 모두 글로벌로 미리 선언한다.(가상맵은 제외)

static int rotateDirection[POSSIBLEDIRECTION] = { 8, 6, 2, 4 };


static Position startP;
//int **mapInput;
//여기부터 실제정보
//비록 robot이 가지고 있지만, 센서가 이 값을
						//가지는 것은 global로 가지는게 적절하다고 판단하여 함
static int **GivingMapNode;		//실제 지도
/*
map
0,0		1,0

0,1		1,1
*///	지도형식
//여기까지 실제 정보


//여기부터 가상 정보
