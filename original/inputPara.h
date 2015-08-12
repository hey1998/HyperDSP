#if !defined(AFX_INPUTPARA_H__0A0A862F_46B0_4806_A6A2_3FDCFF045757__INCLUDED_)
#define AFX_INPUTPARA_H__0A0A862F_46B0_4806_A6A2_3FDCFF045757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// inputPara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CinputPara dialog

class CinputPara : public CDialog
{
// Construction
public:
	CinputPara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CinputPara)
	enum { IDD = IDD_DIALOG1 };
	int		m_Period;
	int		m_Samplefreq;
	int		m_Amplitude;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CinputPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CinputPara)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTPARA_H__0A0A862F_46B0_4806_A6A2_3FDCFF045757__INCLUDED_)
