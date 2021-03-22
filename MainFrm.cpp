// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TetrisMFC.h"

#include "MainFrm.h"
#include "glass.h"

#include "tetrisMFCDoc.h"
#include "dialoginputname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT cr)
{
	if (CFrameWnd::OnCreate(cr) == -1)
		return -1;

	int cy=GetSystemMetrics(SM_CYFULLSCREEN);
	int cx=GetSystemMetrics(SM_CXFULLSCREEN);
	MoveWindow(0,0,cx,cy);
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.hMenu=0;
//	cs.

	//CreateWindow


	cs.style &= ~WS_CAPTION;
	cs.style |= WS_DLGFRAME; 
	int cy=GetSystemMetrics(SM_CYFULLSCREEN);
	int cx=GetSystemMetrics(SM_CXFULLSCREEN);

	//cs.cx=cx;
	//cs.cy=cy;
	//cs.x=(cx-cs.cx)/2;
	//cs.y=(cy-cs.cy)/2;

	HINSTANCE hInst=GetModuleHandle(NULL);

	WNDCLASS wc;
	
	GetClassInfo(
	hInst,//HINSTANCE hInstance,    // handle to application instance
  cs.lpszClass ,//LPCTSTR lpClassName,    // class name
  &wc);//L9PWNDCLASS lpWndClass   // class data
//);

	wc.hbrBackground=0;

	cy=GetSystemMetrics(SM_CYFULLSCREEN);
	cx=GetSystemMetrics(SM_CXFULLSCREEN);
	cs.cx=cx;
	cs.cy=cy;


	UnregisterClass(cs.lpszClass, hInst);
	RegisterClass(&wc);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{

	CTetrisMFCDoc *doc=((CTetrisMFCDoc *)GetActiveDocument());

	// TODO: Add your command handler code here
	CGLASS * glass=doc->_glass_;
	if (glass->Score > doc->rectab->GetMinScore())
	{

				if (MessageBox(
					" Уверены, что хотите выйти ", "В Н И М А Н И Е ! ! !",
					MB_OKCANCEL) == IDOK)
				{


					DialogInputName di;
					di.DoModal();

					doc->rectab->PutNewRecord(
						glass->Score,
						glass->Lines, 
						int(glass->Second), 
						di.m_InputName.GetBuffer(0));
					
				}
				else return;
		}
			
	CFrameWnd::OnClose();

	// TODO: Add your message handler code here and/or call default
//	GetActiveDocument()->_glass
/*	if (MessageBox(
		"Хотите выйти из игры 'TETRIS' ?\n\r"
		"В случае положительного ответа на этот\n\r"
		"вопрос, Ваш текущий рекорд бует безвозратно утерян!\n\r",
		" В Н И М А Н И Е !", MB_OKCANCEL) == IDOK)
	*/
}

/*void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.TextOut(0,0, "STRING");
	// TODO: Add your message handler code here
	// Do not call CFrameWnd::OnPaint() for painting messages
}*/

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMaxSize.y=200;
	lpMMI->ptMinTrackSize.y=320;

	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
