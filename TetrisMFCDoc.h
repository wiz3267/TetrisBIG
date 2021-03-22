// TetrisMFCDoc.h : interface of the CTetrisMFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISMFCDOC_H__41EDE44E_3B0D_462F_88DC_86EA3ECD723D__INCLUDED_)
#define AFX_TETRISMFCDOC_H__41EDE44E_3B0D_462F_88DC_86EA3ECD723D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glass.h"
#include "mylib\rectable.h"

class CTetrisMFCDoc : public CDocument
{
protected: // create from serialization only
	CTetrisMFCDoc();
	DECLARE_DYNCREATE(CTetrisMFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisMFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	RECTABLE * rectab;
	CGLASS * _glass_;
	virtual ~CTetrisMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTetrisMFCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISMFCDOC_H__41EDE44E_3B0D_462F_88DC_86EA3ECD723D__INCLUDED_)
