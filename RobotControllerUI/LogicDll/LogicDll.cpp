// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "LogicDll.h"


namespace LogicDll 
{
	LogicWraper::LogicWraper() : m_pMoveInterface(new MovementInterface)
	{

	}
	LogicWraper::~LogicWraper()
	{
		if (m_pMoveInterface)
		{
			delete m_pMoveInterface;
			m_pMoveInterface = 0;
		}
	}
	void LogicWraper::init(int startY, int startX, int mapHeight, int mapWidth)
	{
		m_pMoveInterface->init(startY, startX, mapHeight, mapWidth);
	}
	void LogicWraper::AddHazardPoint(int y, int x)
	{
		m_pMoveInterface->AddHazardPoint(y,x);
	}
	void LogicWraper::AddColorBlobPoint(int y, int x)
	{
		m_pMoveInterface->AddColorBlobPoint(y, x);
	}
	void LogicWraper::move()
	{
		m_pMoveInterface->move();
	}
	void LogicWraper::addExplorationPoint(int y, int x)
	{
		m_pMoveInterface->addExplorationPoint(y, x);
	}
	void LogicWraper::start()
	{
		m_pMoveInterface->start();
	}
}