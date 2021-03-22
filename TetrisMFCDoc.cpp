// TetrisMFCDoc.cpp : implementation of the CTetrisMFCDoc class
//

#include "stdafx.h"
#include "TetrisMFC.h"

#include "TetrisMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCDoc

IMPLEMENT_DYNCREATE(CTetrisMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CTetrisMFCDoc, CDocument)
	//{{AFX_MSG_MAP(CTetrisMFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCDoc construction/destruction

CTetrisMFCDoc::CTetrisMFCDoc()
{
	// TODO: add one-time construction code here

}

CTetrisMFCDoc::~CTetrisMFCDoc()
{
}

BOOL CTetrisMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCDoc serialization

void CTetrisMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCDoc diagnostics

#ifdef _DEBUG
void CTetrisMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTetrisMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisMFCDoc commands
