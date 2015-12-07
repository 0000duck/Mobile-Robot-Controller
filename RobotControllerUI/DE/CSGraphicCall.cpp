

#include"CSGraphicCall.h"


CSGraphicCall::CSGraphicCall()
{
	CSInterface = NULL;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_InterfaceImplement, NULL, CLSCTX_INPROC_SERVER, IID_iLibInterface, reinterpret_cast<void**>(&CSInterface));
	int a = GetLastError();
	Loaded = SUCCEEDED(hr);

}

CSGraphicCall::~CSGraphicCall()
{
	if (Loaded) CoUninitialize();
}

void CSGraphicCall::CreateObject(int UnitKind, float X, float Y)
{
	if (!Loaded) return;
	CSInterface->CreateObj(UnitKind, X, Y);
}

void CSGraphicCall::Start()
{
	if (!Loaded) return;
	CSInterface->Start();
}
void CSGraphicCall::End()
{
	if (!Loaded) return;
	CSInterface->End();
}
void CSGraphicCall::Move(int Dir)
{
	if (!Loaded) return;
	CSInterface->MoveRobot(Dir);
}
