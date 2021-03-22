#if !defined(AFX_LOADING_H__520C1B2D_156D_4180_88F2_0361E3B2C436__INCLUDED_)
#define AFX_LOADING_H__520C1B2D_156D_4180_88F2_0361E3B2C436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Loading.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoading dialog

class CLoading : public CDialog
{
// Construction
public:
	void StartMusic();
	CLoading(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoading)
	enum { IDD = IDD_LOADING };
	CString	m_static;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoading)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoading)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADING_H__520C1B2D_156D_4180_88F2_0361E3B2C436__INCLUDED_)
