// DSP.h : main header file for the DSP application
//

#if !defined(AFX_DSP_H__5BBCE364_6AF8_4D93_A362_430E26D38F0C__INCLUDED_)
#define AFX_DSP_H__5BBCE364_6AF8_4D93_A362_430E26D38F0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDSPApp:
// See DSP.cpp for the implementation of this class
//

class CDSPApp : public CWinApp
{
public:
	CDSPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDSPApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSP_H__5BBCE364_6AF8_4D93_A362_430E26D38F0C__INCLUDED_)
