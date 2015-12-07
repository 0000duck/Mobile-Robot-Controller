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
		mt19937_64 _engine(rd());                    // MT19937 ���� ����
		engine = _engine;
		uniform_int_distribution<int> _distribution(0, 100);       // ���� ����
		distribution = _distribution;
	}
private:
	mt19937_64 engine;
	uniform_int_distribution<int> distribution;       // ���� ����
};

//����, �κ�, ����κ�, ������ ��� �۷ι��� �̸� �����Ѵ�.(������� ����)

static int rotateDirection[POSSIBLEDIRECTION] = { UP, RIGHT, DOWN, LEFT };
//int **mapInput;
//������� ��������
//��� robot�� ������ ������, ������ �� ����
						//������ ���� global�� �����°� �����ϴٰ� �Ǵ��Ͽ� ��
	//���� ����
/*
map
0,0		1,0

0,1		1,1
*///	��������
//������� ���� ����


//������� ���� ����
