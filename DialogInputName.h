#if !defined(AFX_DIALOGINPUTNAME_H__DF6F8E1D_9A45_4D52_8ED8_F65E4CF877C2__INCLUDED_)
#define AFX_DIALOGINPUTNAME_H__DF6F8E1D_9A45_4D52_8ED8_F65E4CF877C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogInputName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DialogInputName dialog

class DialogInputName : public CDialog
{
// Construction
public:
	DialogInputName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DialogInputName)
	enum { IDD = IDD_DIALOG1 };
	CString	m_InputName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialogInputName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DialogInputName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGINPUTNAME_H__DF6F8E1D_9A45_4D52_8ED8_F65E4CF877C2__INCLUDED_)
