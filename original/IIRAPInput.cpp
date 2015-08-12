// IIRAPInput.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "IIRAPInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIIRAPInput dialog


CIIRAPInput::CIIRAPInput(CWnd* pParent /*=NULL*/)
	: CDialog(CIIRAPInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIIRAPInput)
	m_iirap_carrier_am = 0;
	m_iirap_carrier_freq = 0;
	m_iirap_signal_am = 0;
	m_iirap_signal_freq = 0;
	//}}AFX_DATA_INIT
}


void CIIRAPInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIIRAPInput)
	DDX_Text(pDX, IDC_IIRAP_CARRIER_AM, m_iirap_carrier_am);
	DDV_MinMaxInt(pDX, m_iirap_carrier_am, 0, 5);
	DDX_Text(pDX, IDC_IIRAP_CARRIER_FREQ, m_iirap_carrier_freq);
	DDV_MinMaxInt(pDX, m_iirap_carrier_freq, 1, 499);
	DDX_Text(pDX, IDC_IIRAP_SIGNAL_AM, m_iirap_signal_am);
	DDV_MinMaxInt(pDX, m_iirap_signal_am, 0, 5);
	DDX_Text(pDX, IDC_IIRAP_SIGNAL_FREQ, m_iirap_signal_freq);
	DDV_MinMaxInt(pDX, m_iirap_signal_freq, 1, 499);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIIRAPInput, CDialog)
	//{{AFX_MSG_MAP(CIIRAPInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIIRAPInput message handlers
