// SettingDialog2.cpp : implementation file
//

#include "stdafx.h"
#include "TetrisMFC.h"
#include "SettingDialog2.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog dialog
static CString path="Software\\TetrisMFC";

CSettingDialog::CSettingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDialog)
	m_one_level = FALSE;
	m_all_level = FALSE;
	m_music = FALSE;
	m_sounds = FALSE;
	//}}AFX_DATA_INIT
}


void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDialog)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Check(pDX, IDC_CHECK1, m_one_level);
	DDX_Check(pDX, IDC_CHECK2, m_all_level);
	DDX_Check(pDX, IDC_CHECK3, m_music);
	DDX_Check(pDX, IDC_CHECK4, m_sounds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog message handlers

BOOL CSettingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_combo.AddString("Уровень 0");
	m_combo.AddString("Уровень 1");
	m_combo.AddString("Уровень 2");
	m_combo.AddString("Уровень 3");
	m_combo.AddString("Уровень 4");
	m_combo.AddString("Уровень 5");
	m_combo.AddString("Уровень 6");
	m_combo.AddString("Уровень 7");
	m_combo.AddString("Уровень 8");
	m_combo.AddString("Уровень 9");

	CRegKey reg;
	if (reg.Open(HKEY_CURRENT_USER,path) == ERROR_SUCCESS)
	{
		LoadSetting();
		m_combo.SetCurSel(m_level);
		UpdateData(false);
	}
	else
	{
		m_all_level=1;
		m_one_level=0;
		m_level=1;
		UpdateData(false);
		m_combo.SetCurSel(m_level);
		WriteSetting();
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDialog::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_one_level=true;
	m_all_level=false;
	UpdateData(false);
}

void CSettingDialog::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_one_level=0;
	m_all_level=1;
	UpdateData(false);
	
}

void CSettingDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	WriteSetting();
	OnOK();
}

void CSettingDialog::WriteSetting()
{
	
	UpdateData();

	CRegKey reg;
	reg.Create(HKEY_CURRENT_USER,path);
	reg.SetValue(m_one_level,"OneLevel");
	reg.SetValue(m_all_level,"AllLevel");
	
	m_level=m_combo.GetCurSel();

	reg.SetValue(m_level,"LevelNumber");
	reg.SetValue(m_music,"Music");
	reg.SetValue(m_sounds,"Sounds");


}

void CSettingDialog::LoadSetting()
{
	CRegKey reg;
	if (reg.Open(HKEY_CURRENT_USER,path) == ERROR_SUCCESS)
	{
		DWORD temp;

		reg.QueryValue(temp,"OneLevel");
		m_one_level=temp;

		reg.QueryValue(temp,"AllLevel");
		m_all_level=temp;
		
		reg.QueryValue(m_level,"LevelNumber");

		reg.QueryValue(temp,"Music");
		m_music=temp;

		reg.QueryValue(temp,"Sounds");
		m_sounds=temp;

		reg.Close();
	}
}
