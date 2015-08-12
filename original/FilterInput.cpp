// FilterInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "FilterInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterInput dialog


CFilterInput::CFilterInput(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterInput)
	m_filter_carrier_am = 0;
	m_filter_carrier_freq = 0;
	m_filter_signal_am = 0;
	m_filter_signal_freq = 0;
	//}}AFX_DATA_INIT
}


void CFilterInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterInput)
	DDX_Text(pDX, IDC_FILTER_CARRIER_AM, m_filter_carrier_am);
	DDV_MinMaxInt(pDX, m_filter_carrier_am, 0, 5);
	DDX_Text(pDX, IDC_FILTER_CARRIER_FREQ, m_filter_carrier_freq);
	DDV_MinMaxInt(pDX, m_filter_carrier_freq, 0, 1000);
	DDX_Text(pDX, IDC_FILTER_SIGNAL_AM, m_filter_signal_am);
	DDV_MinMaxInt(pDX, m_filter_signal_am, 0, 5);
	DDX_Text(pDX, IDC_FILTER_SIGNAL_FREQ, m_filter_signal_freq);
	DDV_MinMaxInt(pDX, m_filter_signal_freq, 1, 501);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterInput, CDialog)
	//{{AFX_MSG_MAP(CFilterInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterInput message handlers
