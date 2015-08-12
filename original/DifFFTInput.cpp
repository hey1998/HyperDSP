// DifFFTInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "DifFFTInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDifFFTInput dialog


CDifFFTInput::CDifFFTInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDifFFTInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDifFFTInput)
	m_ditfft_amplitude = 0;
	m_ditfft_count = 0;
	m_ditfft_pierod = 0;
	m_ditfft_level = 0;
	//}}AFX_DATA_INIT
}


void CDifFFTInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDifFFTInput)
	DDX_Text(pDX, IDC_DITFFT_AMPLITUDE, m_ditfft_amplitude);
	DDV_MinMaxInt(pDX, m_ditfft_amplitude, 1, 5);
	DDX_Text(pDX, IDC_DITFFT_COUNT, m_ditfft_count);
	DDV_MinMaxInt(pDX, m_ditfft_count, 1, 5);
	DDX_Text(pDX, IDC_DITFFT_PIEROD, m_ditfft_pierod);
	DDV_MinMaxInt(pDX, m_ditfft_pierod, 1, 160);
	DDX_Text(pDX, IDC_DITFFT_POINT, m_ditfft_level);
	DDV_MinMaxInt(pDX, m_ditfft_level, 1, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDifFFTInput, CDialog)
	//{{AFX_MSG_MAP(CDifFFTInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDifFFTInput message handlers
