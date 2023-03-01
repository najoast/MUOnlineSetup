#include "StdAfx.h"
#include "GlobalMouseHook.h"
#include "BaseFunc.h"

CGlobalMouseHook& CGlobalMouseHook::Instance()
{
	static CGlobalMouseHook s_instance;
	return s_instance;
}

CGlobalMouseHook::CGlobalMouseHook(void)
:m_hMouseHook(NULL)
,m_bRightLongPress(false)
{
}

CGlobalMouseHook::~CGlobalMouseHook(void)
{
	if (m_hMouseHook)
		::UnhookWindowsHookEx(m_hMouseHook);
}

void CGlobalMouseHook::StartRightLongPress()
{
	m_bRightLongPress = true;
}

void CGlobalMouseHook::StopRightLongPress()
{
	m_bRightLongPress = false;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		const int INPUT_SIZE = 1; 
		INPUT input[INPUT_SIZE]; 
		ZeroMemory( &input, sizeof(INPUT)*INPUT_SIZE);

		//鼠标右键按下 
		input[0].type = INPUT_MOUSE; 
		input[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP; 

		//发送鼠标右键单击 
		SendInput( 
			INPUT_SIZE,                // count of input events 
			input,                    // array of input events 
			sizeof(INPUT)            // size of structure 
			); 
	}
}

//参考教程：http://www.it610.com/article/585788.htm
//当按下"Ctrl+鼠标左键" 或 "数字键盘减号键 + 鼠标左键"时，模拟鼠标右键 
/*LRESULT CALLBACK LowLevelMouseProc(int nCode, 
						 WPARAM wParam, 
						 LPARAM lParam) 
{ 
	if(nCode == HC_ACTION)
	{ 
		//左Ctrl键按下 
		BOOL bLeftCtrlDown = (GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0; 
		//数字键盘减号"-"键按下 
		BOOL bNumpadSubtractDown = (GetAsyncKeyState(VK_SUBTRACT) & 0x8000) != 0; 

		//当按下"Ctrl+鼠标左键" 或 "数字键盘减号键+鼠标左键"时，模拟鼠标右键 
		if( (wParam == WM_LBUTTONDOWN) && (bLeftCtrlDown || bNumpadSubtractDown) )    
		{ 
			const int INPUT_SIZE = 2; 
			INPUT input[INPUT_SIZE]; 
			ZeroMemory( &input, sizeof(INPUT)*INPUT_SIZE);//初始化INPUT结构体 

			//鼠标右键按下 
			input[0].type = INPUT_MOUSE; 
			input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; 

			//鼠标右键弹起 
			input[1].type = INPUT_MOUSE; 
			input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP; 

			//发送鼠标右键单击 
			SendInput( 
				INPUT_SIZE,                // count of input events 
				input,                    // array of input events 
				sizeof(INPUT)            // size of structure 
				); 

			//发送模拟的鼠标右键单击后，不再响应鼠标左键单击消息 
			return 1;    
		} 

	} 

	//如果不是"Ctrl+鼠标左键"按下，则向后传递鼠标消息。 
	return CallNextHookEx(NULL,nCode,wParam,lParam); 
} 

LRESULT CALLBACK CGlobalMouseHook::MouseProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if (CGlobalMouseHook::Instance().m_bRightLongPress)
	{
		const int INPUT_SIZE = 1; 
		INPUT input[INPUT_SIZE]; 
		ZeroMemory( &input, sizeof(INPUT)*INPUT_SIZE);//初始化INPUT结构体 

		//鼠标右键按下 
		input[0].type = INPUT_MOUSE; 
		input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; 

		//鼠标右键弹起 
		input[1].type = INPUT_MOUSE; 
		input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP; 

		//发送鼠标右键单击 
		SendInput( 
			INPUT_SIZE,                // count of input events 
			input,                    // array of input events 
			sizeof(INPUT)            // size of structure 
			); 

		//发送模拟的鼠标右键单击后，不再响应鼠标左键单击消息 
		//return 1;
	}

	return CallNextHookEx(NULL,nCode,wParam,lParam);
}*/

bool CGlobalMouseHook::InstallMouseHook(HINSTANCE hInstance)
{
// 	if (m_hMouseHook != NULL)
// 		return true;
// 
// 	m_hMouseHook = SetWindowsHookEx( 
// 		WH_MOUSE_LL,					// hook type 
// 		CGlobalMouseHook::MouseProc,	// hook procedure 
// 		hInstance,						// handle to application instance 
// 		0								// thread identifier:为0表示全局钩子 
// 		);
// 
// 	if(m_hMouseHook == NULL)
// 	{
// 		MessageBox(NULL,"Install MouseHook failed!","InstallMouseHook()",MB_OK);
// 		return false;
// 	}

	return true; 
}

void CGlobalMouseHook::OnTimer()
{
// 	SHORT sRet = GetAsyncKeyState(VK_RBUTTON);
// 	MyLogSave("zy", "%d\t\t%d", sRet, sRet & 0x8000);

	if (m_bRightLongPress && !(GetAsyncKeyState(VK_RBUTTON) & 0x8000))
	{
		const int INPUT_SIZE = 1; 
		INPUT input[INPUT_SIZE]; 
		ZeroMemory( &input, sizeof(INPUT)*INPUT_SIZE);//初始化INPUT结构体 

		//鼠标右键按下 
		input[0].type = INPUT_MOUSE; 
		input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; 

		//鼠标右键弹起 
// 		input[1].type = INPUT_MOUSE; 
// 		input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP; 

		//发送鼠标右键单击 
		SendInput( 
			INPUT_SIZE,                // count of input events 
			input,                    // array of input events 
			sizeof(INPUT)            // size of structure 
			); 
	}	
}