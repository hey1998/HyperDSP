// IIRLPInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "IIRLPInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIIRLPInput dialog


CIIRLPInput::CIIRLPInput(CWnd* pParent /*=NULL*/)
	: CDialog(CIIRLPInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIIRLPInput)
	m_iirlp_carrier_am = 0;
	m_iirlp_carrier_freq = 0;
	m_iirlp_signal_freq = 0;
	m_iirlp_signal_am = 0;
	//}}AFX_DATA_INIT
}


void CIIRLPInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIIRLPInput)
	DDX_Text(pDX, IDC_IIRLP_CARRIER_AM, m_iirlp_carrier_am);
	DDV_MinMaxInt(pDX, m_iirlp_carrier_am, 0, 5);
	DDX_Text(pDX, IDC_IIRLP_CARRIER_FREQ, m_iirlp_carrier_freq);
	DDV_MinMaxInt(pDX, m_iirlp_carrier_freq, 1, 499);
	DDX_Text(pDX, IDC_IIRLP_SIGNAL_FREQ, m_iirlp_signal_freq);
	DDV_MinMaxInt(pDX, m_iirlp_signal_freq, 1, 499);
	DDX_Text(pDX, IDC_IIRLP_SINGNAL_AM, m_iirlp_signal_am);
	DDV_MinMaxInt(pDX, m_iirlp_signal_am, 0, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIIRLPInput, CDialog)
	//{{AFX_MSG_MAP(CIIRLPInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIIRLPInput message handlers
