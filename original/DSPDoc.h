// DSPDoc.h : interface of the CDSPDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPDOC_H__327A053F_A4AF_4668_88FF_36D6B9C20B5C__INCLUDED_)
#define AFX_DSPDOC_H__327A053F_A4AF_4668_88FF_36D6B9C20B5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSPDoc : public CDocument
{
protected: // create from serialization only
	CDSPDoc();
	DECLARE_DYNCREATE(CDSPDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSPDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPDOC_H__327A053F_A4AF_4668_88FF_36D6B9C20B5C__INCLUDED_)
