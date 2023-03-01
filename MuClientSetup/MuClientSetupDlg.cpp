
// MuClientSetupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MuClientSetup.h"
#include "MuClientSetupDlg.h"
#include "ModuleDefine.h"
#include "GlobalMouseHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMuClientSetupDlg 对话框




CMuClientSetupDlg::CMuClientSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMuClientSetupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMuClientSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
}

BEGIN_MESSAGE_MAP(CMuClientSetupDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_MUSIC, &CMuClientSetupDlg::OnBnClickedCheckMusic)
	ON_BN_CLICKED(IDC_CHECK_TEXT_INPUT, &CMuClientSetupDlg::OnBnClickedCheckTextInput)
	ON_BN_CLICKED(IDC_CHECK_SOUND, &CMuClientSetupDlg::OnBnClickedCheckSound)
	ON_BN_CLICKED(IDC_CHECK_WINDOW_MODE, &CMuClientSetupDlg::OnBnClickedCheckWindowMode)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMuClientSetupDlg::OnBnClickedButtonOk)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, &CMuClientSetupDlg::OnCbnSelchangeComboResolution)
	//ON_BN_CLICKED(IDC_BUTTON_MOUSE_RIGHT_CLICK, &CMuClientSetupDlg::OnBnClickedButtonMouseRightClick)
	ON_BN_CLICKED(IDOK, &CMuClientSetupDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CMuClientSetupDlg 消息处理程序

BOOL CMuClientSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->InitComboResolution();
	this->SetupInitValue();

	BOOL bRet = ::RegisterHotKey(m_hWnd, GLOBAL_HOTKEY_CTRL_Y, MOD_CONTROL, 'Y');

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMuClientSetupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMuClientSetupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMuClientSetupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//非默认值
void UpdateKeyNoDefaultValue_DWORD(HKEY hKey, const char* strSubKey, const char* strValueName, DWORD dwValue)
{
	DWORD dwType = REG_DWORD;

	HKEY hSubKey;
	DWORD dispos;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	DWORD value = 1;
	long iret = RegCreateKeyEx(hKey, strSubKey, NULL, NULL,	REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &sa, &hSubKey, &dispos);

	if(ERROR_SUCCESS == iret)
	{
		DWORD dwSize = 0;
		DWORD dwOldValue = 100;
		RegQueryValueEx(hSubKey, strValueName, NULL, &dwType, (BYTE *)dwOldValue, &dwSize);

		LSTATUS ret = RegSetValueEx(hSubKey, strValueName, 0, dwType, (const BYTE*)&dwValue, sizeof(dwValue));
		if (ret != ERROR_SUCCESS)
		{
			char szBuffer[256] = "";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret, 0, szBuffer, 256, NULL);
			AfxMessageBox(szBuffer);
		}
	}

	RegCloseKey(hSubKey);
}

void UpdateKeyNoDefaultValue_String(HKEY hKey, const char* strSubKey, const char* strValueName, const char* strValue)
{
	DWORD dwType = REG_SZ;

	HKEY hSubKey;
	DWORD dispos;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	DWORD value = 1;
	long iret = RegCreateKeyEx(hKey, strSubKey, NULL, NULL,	REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &sa, &hSubKey, &dispos);

	if(ERROR_SUCCESS == iret)
	{
		DWORD dwSize = 0;
// 		char szOldValue[512] = "";
// 		RegQueryValueEx(hSubKey, strValueName, NULL, &dwType, (BYTE *)szOldValue, &dwSize);

		LSTATUS ret = RegSetValueEx(hSubKey, strValueName, 0, dwType, (const BYTE*)strValue, strlen(strValue));
		if (ret != ERROR_SUCCESS)
		{
			char szBuffer[256] = "";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret, 0, szBuffer, 256, NULL);
			AfxMessageBox(szBuffer);
		}
	}

	RegCloseKey(hSubKey);
}


void CMuClientSetupDlg::OnBnClickedCheckMusic()
{
	DWORD dwValue = this->IsDlgButtonChecked(IDC_CHECK_MUSIC) ? MUSIC_VALUE_ON : MUSIC_VALUE_OFF;
	UpdateKeyNoDefaultValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_MUSIC, dwValue);
}

void CMuClientSetupDlg::OnBnClickedCheckTextInput()
{
	DWORD dwValue = this->IsDlgButtonChecked(IDC_CHECK_TEXT_INPUT) ? TI_VALUE_ON : TI_VALUE_OFF;
	UpdateKeyNoDefaultValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_TEXTINPUT, dwValue);
}

void CMuClientSetupDlg::OnBnClickedCheckSound()
{
	DWORD dwValue = this->IsDlgButtonChecked(IDC_CHECK_SOUND) ? SOUND_VALUE_ON : SOUND_VALUE_OFF;
	UpdateKeyNoDefaultValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_SOUND, dwValue);
}

void CMuClientSetupDlg::OnBnClickedCheckWindowMode()
{
	DWORD dwValue = this->IsDlgButtonChecked(IDC_CHECK_WINDOW_MODE) ? WM_VALUE_WINDOW : WM_VALUE_FULL_SCREEN;
	UpdateKeyNoDefaultValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_WINDOWMODE, dwValue);
}

void CMuClientSetupDlg::OnBnClickedButtonOk()
{

}

void CMuClientSetupDlg::OnCbnSelchangeComboResolution()
{
	DWORD dwValue = m_comboResolution.GetCurSel();
	UpdateKeyNoDefaultValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_RESOULTION, dwValue);	
}

void CMuClientSetupDlg::InitComboResolution()
{
	m_comboResolution.InsertString(RESOLUTION_VALUE_640_480, "640x480");
	m_comboResolution.InsertString(RESOLUTION_VALUE_800_600, "800x600");
	m_comboResolution.InsertString(RESOLUTION_VALUE_1024_768, "1024x768");
	m_comboResolution.InsertString(RESOLUTION_VALUE_1280_1024, "1280x1024");
}

//////////////////////////////////////////////////////////////////////////
DWORD QueryRegValue_DWORD(HKEY hKey, const char* strSubKey, const char* strValueName)
{
	DWORD dwType = REG_DWORD;
	DWORD dwValue = 0;
	DWORD dwSize = sizeof(DWORD);

	HKEY hkey;
	::RegOpenKey(hKey,strSubKey,&hkey);
	::RegQueryValueEx(hkey, strValueName, NULL,&dwType, (LPBYTE)&dwValue, &dwSize);
	::RegCloseKey(hkey);

	return dwValue;
}

DWORD QueryRegValue_String(HKEY hKey, const char* strSubKey, const char* strValueName, char* strValue/*OUT*/, int nBufSize)
{
	DWORD dwType = REG_SZ;
	DWORD dwSize = nBufSize;

	HKEY hkey;
	::RegOpenKey(hKey,strSubKey,&hkey);
	::RegQueryValueEx(hkey, strValueName, NULL,&dwType, (LPBYTE)strValue, &dwSize);
	::RegCloseKey(hkey);

	return dwSize;
}

void CMuClientSetupDlg::SetupInitValue()
{
	DWORD dwValue = QueryRegValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_MUSIC);
	this->CheckDlgButton(IDC_CHECK_MUSIC, dwValue==MUSIC_VALUE_ON ? 1 : 0);

	dwValue = QueryRegValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_SOUND);
	this->CheckDlgButton(IDC_CHECK_SOUND, dwValue==SOUND_VALUE_ON ? 1 : 0);

	dwValue = QueryRegValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_WINDOWMODE);
	this->CheckDlgButton(IDC_CHECK_WINDOW_MODE, dwValue==WM_VALUE_WINDOW ? 1 : 0);

	dwValue = QueryRegValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_TEXTINPUT);
	this->CheckDlgButton(IDC_CHECK_TEXT_INPUT, dwValue==TI_VALUE_ON ? 1 : 0);

	dwValue = QueryRegValue_DWORD(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_RESOULTION);
	if (dwValue >= RESOLUTION_VALUE_640_480 && dwValue <= RESOLUTION_VALUE_1280_1024)
		m_comboResolution.SetCurSel(dwValue);

	char szRememberAccount[512] = "";
	QueryRegValue_String(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_ID, szRememberAccount, 512);
	this->SetDlgItemText(IDC_EDIT_REMEMBER_ACCOUNT, szRememberAccount);
}



void CMuClientSetupDlg::OnBnClickedButtonMouseRightClick()
{

}

void CMuClientSetupDlg::OnBnClickedOk()
{
	CString strID;
	this->GetDlgItemText(IDC_EDIT_REMEMBER_ACCOUNT, strID);
	UpdateKeyNoDefaultValue_String(HKEY_CURRENT_USER, REG_KEY_PATH, REG_KEY_ID, strID);

	// TODO: Add your control notification handler code here
	OnOK();
}

#define ON_TIMER_ID_MOUSE_RIGHT_DOWN 0
void CMuClientSetupDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case ON_TIMER_ID_MOUSE_RIGHT_DOWN:
		CGlobalMouseHook::Instance().OnTimer();
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CMuClientSetupDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	switch (nHotKeyId)
	{
	case GLOBAL_HOTKEY_CTRL_Y:
		{
			// TODO: Add your control notification handler code here
			if (CGlobalMouseHook::Instance().IsRightLongPress())
			{
				CGlobalMouseHook::Instance().StopRightLongPress();
				this->KillTimer(ON_TIMER_ID_MOUSE_RIGHT_DOWN);
				this->SetDlgItemText(IDC_STATIC_RD_ONOFF, "Closed");
			}
			else
			{
				CGlobalMouseHook::Instance().StartRightLongPress();
				this->SetTimer(ON_TIMER_ID_MOUSE_RIGHT_DOWN, 500, NULL);
				this->SetDlgItemText(IDC_STATIC_RD_ONOFF, "已打开");
			}
		}
		break;
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}
