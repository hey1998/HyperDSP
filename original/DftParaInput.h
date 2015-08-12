#if !defined(AFX_DFTPARAINPUT_H__4769B107_0A9F_47C0_B37C_CFAB99F5FD07__INCLUDED_)
#define AFX_DFTPARAINPUT_H__4769B107_0A9F_47C0_B37C_CFAB99F5FD07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DftParaInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDftParaInput dialog

class CDftParaInput : public CDialog
{
// Construction
public:
	CDftParaInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDftParaInput)
	enum { IDD = IDD_DIALOG2 };
	int		m_dft_point;
	int		m_tri_amplitude;
	int		m_tri_count;
	int		m_tri_pierod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDftParaInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDftParaInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DFTPARAINPUT_H__4769B107_0A9F_47C0_B37C_CFAB99F5FD07__INCLUDED_)
