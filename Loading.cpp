// Loading.cpp : implementation file
//

#include "stdafx.h"
#include "TetrisMFC.h"
#include "Loading.h"

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoading dialog


CLoading::CLoading(CWnd* pParent /*=NULL*/)
	: CDialog(CLoading::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoading)
	m_static = _T("");
	//}}AFX_DATA_INIT
}


void CLoading::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoading)
	DDX_Text(pDX, IDC_STATIC1, m_static);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoading, CDialog)
	//{{AFX_MSG_MAP(CLoading)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoading message handlers

DWORD WINAPI StartMusic(LPVOID param)
{
	while (1)
	{
	
		mciSendString("open music.mid alias snd",0,0,0);
		mciSendString("play snd",0,0,0);

		//Sleep(3000);
		Sleep( (5*60+32)*1000);
		mciSendString("close snd",0,0,0);
	}

	return 0;
}

void CLoading::OnTimer(UINT ID) 
{
	if (ID==1)// TODO: Add your message handler code here and/or call default
	OnOK();
	
	if (ID==3)
	{
		static CString z;
		z+=".";
		m_static="«агрузка"+z;
		UpdateData(false);
	}
	
	
	CDialog::OnTimer(ID);
}

BOOL CLoading::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	SetTimer(1,4500,NULL);	//общее врем€ жизни диалоговой панели
	SetTimer(3,120,NULL);
	StartMusic();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoading::StartMusic()
{

	CreateThread(0,0,::StartMusic,0,0,0);
}
