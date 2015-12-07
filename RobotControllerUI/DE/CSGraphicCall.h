#pragma once
#import"GraphicControl.tlb" no_namespace named_guids

class CSGraphicCall
{
public:
	static const int CS_UP = 0;
	static const int CS_DOWN = 1;
	static const int CS_LEFT = 2;
	static const int CS_RIGHT = 3;

	static const int CS_HAZARD = 2;
	static const int CS_COLOR = 3;


	iLibInterface *CSInterface;
	bool Loaded;

	explicit CSGraphicCall();
	virtual ~CSGraphicCall();

	void CreateObject(int UnitKind, float X, float Y);
	void Start();
	void End();
	//  public const int UP = 0;
    //  const int DOWN = 1;
	//	public const int LEFT = 2;
	//	public const int RIGHT = 3;
	
	void Move(int Dir);
};