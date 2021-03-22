// DialogInputName.cpp : implementation file
//

#include "stdafx.h"
#include "TetrisMFC.h"
#include "DialogInputName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DialogInputName dialog


DialogInputName::DialogInputName(CWnd* pParent /*=NULL*/)
	: CDialog(DialogInputName::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialogInputName)
	m_InputName = _T("");
	//}}AFX_DATA_INIT
}


void DialogInputName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogInputName)
	DDX_Text(pDX, IDC_EDIT1, m_InputName);
	DDV_MaxChars(pDX, m_InputName, 14);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogInputName, CDialog)
	//{{AFX_MSG_MAP(DialogInputName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogInputName message handlers

void DialogInputName::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
