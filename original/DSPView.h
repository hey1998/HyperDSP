// DSPView.h : interface of the CDSPView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPVIEW_H__257F7005_6426_4CFD_BA13_5494DCF30640__INCLUDED_)
#define AFX_DSPVIEW_H__257F7005_6426_4CFD_BA13_5494DCF30640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSPView : public CView
{
protected: // create from serialization only
	CDSPView();
	DECLARE_DYNCREATE(CDSPView)

// Attributes
public:
	CDSPDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
 
// Implementation
public:
	int n_filter_signal_freq;
	int n_filter_signal_am;
	int n_filter_carrier_freq;
	int n_filter_carrier_am;
	void IIRHP_main(CDC* pDC);
	void IIRAP_main(CDC* pDC);
	void IIRLP_main(CDC* pDC);
	void IIR_DrawCoord(CDC* pDC,int originalX, int originalY);
	int n_iirhp_carrier_freq;
	int n_iirhp_carrier_am;
	int n_iirhp_signal_freq;
	int n_iirhp_signal_am;
	int n_iirap_carrier_freq;
	int n_iirap_carrier_am;
	int n_iirap_signal_freq;
	int n_iirap_signal_am;
	int n_iirlp_carrier_freq;
	int n_iirlp_carrier_am;
	int n_iirlp_signal_freq;
	int n_iirlp_signal_am;
	int m_tri_pierod;
	int m_tri_count;
	int m_tri_amplitude;
	int m_dft_point;
	int m_SampleFreq;
	int m_Amplitude;
	int m_Period;
	int n_ditfft_count;
	int n_ditfft_pierod;
	int n_ditfft_amplitude;
	int n_ditfft_level;
	//int n_mCoordMode;
	
	enum 
	{
		COORD_GRID,
		COORD_DOT,
		SINSIGNAL_INPUT,
		DFT_TRI,
		DIT_FFT,
		IIR_LP,
		IIR_AP,
		IIR_HP,
		FILTER_TRI
	}n_mCoordMode ;

	typedef struct tagComplex
	{
		 float Re;//复数实部
		 float Im;//复数虚部
	}Complex;


	void DrawDotCoord6(CDC *pDC);
	void DrawDotCoord5(CDC *pDC);
	void DrawDotCoord1ByDftAm(CDC *pDC);
	void DrawDftAM(CDC *pDC);
	void DrawDitFFT(CDC *pDC);
	void DrawDotCoord4(CDC *pDC);
	void DrawDotCoord3(CDC* pDC);
	void DrawTriByPierodCount(CDC *pDC,int count,int pierod,int amplitude);
	void DrawTriSignal(CDC* pDC,int point,int pierod,int amplitude);
	void DrawSinsignal(CDC* pDC);
	void Filter_Tri_main(CDC*pDC);
	virtual ~CDSPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSPView)
	afx_msg void OnCoordGrid();
	afx_msg void OnCoordDot();
	afx_msg void OnUpdateCoordGrid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCoordDot(CCmdUI* pCmdUI);
	afx_msg void OnDrawSinInputpara();
	afx_msg void OnDrawTriDft();
	afx_msg void OnUpdateTriDft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSinInputpara(CCmdUI* pCmdUI);
	afx_msg void OnDitFft();
	afx_msg void OnUpdateDitFft(CCmdUI* pCmdUI);
	afx_msg void OnIirLp();
	afx_msg void OnUpdateIirLp(CCmdUI* pCmdUI);
	afx_msg void OnIirAp();
	afx_msg void OnUpdateIirAp(CCmdUI* pCmdUI);
	afx_msg void OnIirHp();
	afx_msg void OnUpdateIirHp(CCmdUI* pCmdUI);
	afx_msg void OnFilterTri();
	afx_msg void OnUpdateFilterTri(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DSPView.cpp
inline CDSPDoc* CDSPView::GetDocument()
   { return (CDSPDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPVIEW_H__257F7005_6426_4CFD_BA13_5494DCF30640__INCLUDED_)
