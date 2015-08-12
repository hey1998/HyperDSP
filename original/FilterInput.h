#if !defined(AFX_FILTERINPUT_H__6DC842A8_F1F0_4F80_8D8D_3212D0A648F5__INCLUDED_)
#define AFX_FILTERINPUT_H__6DC842A8_F1F0_4F80_8D8D_3212D0A648F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterInput dialog

class CFilterInput : public CDialog
{
// Construction
public:
	CFilterInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterInput)
	enum { IDD = IDD_DIALOG7 };
	int		m_filter_carrier_am;
	int		m_filter_carrier_freq;
	int		m_filter_signal_am;
	int		m_filter_signal_freq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERINPUT_H__6DC842A8_F1F0_4F80_8D8D_3212D0A648F5__INCLUDED_)
