// inputPara.cpp : implementation file
//

#include "stdafx.h"
#include "DSP.h"
#include "inputPara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CinputPara dialog


CinputPara::CinputPara(CWnd* pParent /*=NULL*/)
	: CDialog(CinputPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CinputPara)
	m_Period = 0;
	m_Samplefreq = 0;
	m_Amplitude = 0;
	//}}AFX_DATA_INIT
}


void CinputPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CinputPara)
	DDX_Text(pDX, IDC_INPUTPARA_PERIOD, m_Period);
	DDV_MinMaxInt(pDX, m_Period, 4, 320);
	DDX_Text(pDX, IDC_INPUTPARA_SAMPFREQ, m_Samplefreq);
	DDV_MinMaxInt(pDX, m_Samplefreq, 1, 159);
	DDX_Text(pDX, IDC_INPUTPARA_AMPLITUDE, m_Amplitude);
	DDV_MinMaxInt(pDX, m_Amplitude, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CinputPara, CDialog)
	//{{AFX_MSG_MAP(CinputPara)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CinputPara message handlers
