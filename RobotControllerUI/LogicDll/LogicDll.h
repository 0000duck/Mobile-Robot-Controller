// LogicDll.h

#pragma once

#include "..\DE\MainFlow.h"

using namespace System;

namespace LogicDll {

	public ref class LogicWraper
	{
	protected:
		MovementInterface* m_pMoveInterface;
	public:
		LogicWraper();
		virtual ~LogicWraper();

		void init(int startY, int startX, int mapHeight, int mapWidth);
		//�������� �߰�
		void AddHazardPoint(int y, int x);
		
		//Į�����߰�
		void AddColorBlobPoint(int y, int x);
		
		//�̵�?
		void move();
		//Ž�� ���� �߰��Լ�
		void addExplorationPoint(int y, int x);
		//Ž�� ���� �Լ�
		void start();
	};
}
