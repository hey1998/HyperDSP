#if !defined(AFX_DIFFFTINPUT_H__3195E931_9ACB_42B3_9D4E_AFC32B04D17E__INCLUDED_)
#define AFX_DIFFFTINPUT_H__3195E931_9ACB_42B3_9D4E_AFC32B04D17E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DifFFTInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDifFFTInput dialog

class CDifFFTInput : public CDialog
{
// Construction
public:
	CDifFFTInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDifFFTInput)
	enum { IDD = IDD_DIALOG3 };
	int		m_ditfft_amplitude;
	int		m_ditfft_count;
	int		m_ditfft_pierod;
	int		m_ditfft_level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDifFFTInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDifFFTInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIFFFTINPUT_H__3195E931_9ACB_42B3_9D4E_AFC32B04D17E__INCLUDED_)
