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
		//위험지역 추가
		void AddHazardPoint(int y, int x);
		
		//칼라블롭추가
		void AddColorBlobPoint(int y, int x);
		
		//이동?
		void move();
		//탐사 지점 추가함수
		void addExplorationPoint(int y, int x);
		//탐사 시작 함수
		void start();
	};
}
