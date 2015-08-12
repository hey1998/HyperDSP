// IIRHPInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "IIRHPInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIIRHPInput dialog


CIIRHPInput::CIIRHPInput(CWnd* pParent /*=NULL*/)
	: CDialog(CIIRHPInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIIRHPInput)
	m_iirhp_carrier_am = 0;
	m_iirhp_carrier_freq = 0;
	m_iirhp_signal_am = 0;
	m_iirhp_signal_freq = 0;
	//}}AFX_DATA_INIT
}


void CIIRHPInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIIRHPInput)
	DDX_Text(pDX, IDC_IIRHP_CARRIER_AM, m_iirhp_carrier_am);
	DDV_MinMaxInt(pDX, m_iirhp_carrier_am, 0, 5);
	DDX_Text(pDX, IDC_IIRHP_CARRIER_FREQ, m_iirhp_carrier_freq);
	DDV_MinMaxInt(pDX, m_iirhp_carrier_freq, 1, 499);
	DDX_Text(pDX, IDC_IIRHP_SIGNAL_AM, m_iirhp_signal_am);
	DDV_MinMaxInt(pDX, m_iirhp_signal_am, 0, 5);
	DDX_Text(pDX, IDC_IIRHP_SIGNAL_FREQ, m_iirhp_signal_freq);
	DDV_MinMaxInt(pDX, m_iirhp_signal_freq, 1, 499);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIIRHPInput, CDialog)
	//{{AFX_MSG_MAP(CIIRHPInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIIRHPInput message handlers
