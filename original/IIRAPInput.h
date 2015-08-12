#if !defined(AFX_IIRAPINPUT_H__507F4FD8_649E_4D73_BD80_E3B4D431FBDA__INCLUDED_)
#define AFX_IIRAPINPUT_H__507F4FD8_649E_4D73_BD80_E3B4D431FBDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IIRAPInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIIRAPInput dialog

class CIIRAPInput : public CDialog
{
// Construction
public:
	CIIRAPInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIIRAPInput)
	enum { IDD = IDD_DIALOG5 };
	int		m_iirap_carrier_am;
	int		m_iirap_carrier_freq;
	int		m_iirap_signal_am;
	int		m_iirap_signal_freq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIIRAPInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIIRAPInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IIRAPINPUT_H__507F4FD8_649E_4D73_BD80_E3B4D431FBDA__INCLUDED_)
