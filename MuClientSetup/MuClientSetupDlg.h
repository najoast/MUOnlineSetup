
// MuClientSetupDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMuClientSetupDlg 对话框
class CMuClientSetupDlg : public CDialog
{
// 构造
public:
	CMuClientSetupDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MUCLIENTSETUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckMusic();
	afx_msg void OnBnClickedCheckTextInput();
	afx_msg void OnBnClickedCheckSound();
	afx_msg void OnBnClickedCheckWindowMode();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnCbnSelchangeComboResolution();
	CComboBox m_comboResolution;

private:
	void InitComboResolution();
	void SetupInitValue();		// 取旧值设置给控件
public:
	afx_msg void OnBnClickedButtonMouseRightClick();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
