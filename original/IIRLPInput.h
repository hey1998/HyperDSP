#if !defined(AFX_IIRLPINPUT_H__12B068DE_8C58_4755_8796_5E26C459965F__INCLUDED_)
#define AFX_IIRLPINPUT_H__12B068DE_8C58_4755_8796_5E26C459965F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IIRLPInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIIRLPInput dialog

class CIIRLPInput : public CDialog
{
// Construction
public:
	CIIRLPInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIIRLPInput)
	enum { IDD = IDD_DIALOG4 };
	int		m_iirlp_carrier_am;
	int		m_iirlp_carrier_freq;
	int		m_iirlp_signal_freq;
	int		m_iirlp_signal_am;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIIRLPInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIIRLPInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IIRLPINPUT_H__12B068DE_8C58_4755_8796_5E26C459965F__INCLUDED_)
