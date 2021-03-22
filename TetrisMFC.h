// TetrisMFC.h : main header file for the TETRISMFC application
//

#if !defined(AFX_TETRISMFC_H__87AE9461_C3EA_4022_A482_7704DD02A7B4__INCLUDED_)
#define AFX_TETRISMFC_H__87AE9461_C3EA_4022_A482_7704DD02A7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCApp:
// See TetrisMFC.cpp for the implementation of this class
//

class CTetrisMFCApp : public CWinApp
{
public:
	CTetrisMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTetrisMFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISMFC_H__87AE9461_C3EA_4022_A482_7704DD02A7B4__INCLUDED_)
