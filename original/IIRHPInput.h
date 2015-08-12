#if !defined(AFX_IIRHPINPUT_H__487C062B_28E0_4791_B233_3B85B28D79DB__INCLUDED_)
#define AFX_IIRHPINPUT_H__487C062B_28E0_4791_B233_3B85B28D79DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IIRHPInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIIRHPInput dialog

class CIIRHPInput : public CDialog
{
// Construction
public:
	CIIRHPInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIIRHPInput)
	enum { IDD = IDD_DIALOG6 };
	int		m_iirhp_carrier_am;
	int		m_iirhp_carrier_freq;
	int		m_iirhp_signal_am;
	int		m_iirhp_signal_freq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIIRHPInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIIRHPInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IIRHPINPUT_H__487C062B_28E0_4791_B233_3B85B28D79DB__INCLUDED_)
