// DSPDoc.cpp : implementation of the CDSPDoc class
//

#include "stdafx.h"
#include "DSP.h"

#include "DSPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPDoc

IMPLEMENT_DYNCREATE(CDSPDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSPDoc, CDocument)
	//{{AFX_MSG_MAP(CDSPDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPDoc construction/destruction

CDSPDoc::CDSPDoc()
{
	// TODO: add one-time construction code here

}

CDSPDoc::~CDSPDoc()
{
}

BOOL CDSPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("çÑÖÇ»ª  111120043");
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSPDoc serialization

void CDSPDoc::Serialize(CArchive& ar)
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
// CDSPDoc diagnostics

#ifdef _DEBUG
void CDSPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPDoc commands
