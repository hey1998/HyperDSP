// DftParaInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "DftParaInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDftParaInput dialog


CDftParaInput::CDftParaInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDftParaInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDftParaInput)
	m_dft_point = 0;
	m_tri_amplitude = 0;
	m_tri_count = 0;
	m_tri_pierod = 0;
	//}}AFX_DATA_INIT
}


void CDftParaInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDftParaInput)
	DDX_Text(pDX, IDC_DFT_POINT, m_dft_point);
	DDV_MinMaxInt(pDX, m_dft_point, 1, 160);
	DDX_Text(pDX, IDC_TRI_AMPLITUDE, m_tri_amplitude);
	DDV_MinMaxInt(pDX, m_tri_amplitude, 1, 5);
	DDX_Text(pDX, IDC_TRI_COUNT, m_tri_count);
	DDV_MinMaxInt(pDX, m_tri_count, 1, 5);
	DDX_Text(pDX, IDC_TRI_PIEROD, m_tri_pierod);
	DDV_MinMaxInt(pDX, m_tri_pierod, 1, 160);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDftParaInput, CDialog)
	//{{AFX_MSG_MAP(CDftParaInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDftParaInput message handlers
