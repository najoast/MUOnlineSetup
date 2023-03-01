#pragma once

class CGlobalMouseHook
{
public:
	static CGlobalMouseHook& Instance();

private:
	CGlobalMouseHook(void);
	~CGlobalMouseHook(void);

public:
	bool InstallMouseHook(HINSTANCE hInstance);	

	void StartRightLongPress();
	void StopRightLongPress();
	bool IsRightLongPress()		{ return m_bRightLongPress; }

	void OnTimer();

public:
	HHOOK m_hMouseHook;	
	bool m_bRightLongPress;


//////////////////////////////////////////////////////////////////////////
private:
	static LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam);
};
