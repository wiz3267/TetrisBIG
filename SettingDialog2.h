#if !defined(AFX_SETTINGDIALOG2_H__AE4A97C5_D6BE_4C1C_8E99_275862D248EB__INCLUDED_)
#define AFX_SETTINGDIALOG2_H__AE4A97C5_D6BE_4C1C_8E99_275862D248EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDialog2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog dialog

class CSettingDialog : public CDialog
{
// Construction
public:
	void LoadSetting();

	void WriteSetting();
	DWORD m_level;
	CSettingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDialog)
	enum { IDD = ID_DIALOG_SETTING };
	CComboBox	m_combo;
	BOOL	m_one_level;
	BOOL	m_all_level;
	BOOL	m_music;
	BOOL	m_sounds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDIALOG2_H__AE4A97C5_D6BE_4C1C_8E99_275862D248EB__INCLUDED_)
