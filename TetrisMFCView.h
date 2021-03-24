// TetrisMFCView.h : interface of the CTetrisMFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISMFCVIEW_H__4B51C746_1093_416E_A1BD_6AC4BA204891__INCLUDED_)
#define AFX_TETRISMFCVIEW_H__4B51C746_1093_416E_A1BD_6AC4BA204891__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glass.h"
#include "mylib\rectable.h"
#include "figure.h"
#include "settingdialog2.h"

class CTetrisMFCView : public CView
{
protected: // create from serialization only
	CTetrisMFCView();
	DECLARE_DYNCREATE(CTetrisMFCView)
	CSettingDialog settings;
	CGLASS * glass;
	RECTABLE rectable;
// Attributes
public:
	CTetrisMFCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisMFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadTetris();
	void SaveTetris();
	void GenerateNewFigure();
	void OnKeyDown(WPARAM wp, LPARAM lp);
	void OnKeyUp(WPARAM wp, LPARAM lp);
	void SetGameSpeed();
//	CFIGURE fig;
	virtual ~CTetrisMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTetrisMFCView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnAppExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuShowOnlyGlass();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TetrisMFCView.cpp
inline CTetrisMFCDoc* CTetrisMFCView::GetDocument()
   { return (CTetrisMFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISMFCVIEW_H__4B51C746_1093_416E_A1BD_6AC4BA204891__INCLUDED_)
