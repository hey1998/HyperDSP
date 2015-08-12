// DSPView.cpp : implementation of the CDSPView class
//

#include "stdafx.h"
#include "DSP.h"

#include "DSPDoc.h"
#include "DSPView.h"
#include "math.h"
#include "inputPara.h"
#include "DftParaInput.h"
#include "DifFFTInput.h"
#include "IIRLPInput.h"
#include "IIRAPInput.h"
#include "IIRHPInput.h"
#include "FilterInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////const Variable Definition


int ORIGINX = 20;
int ORIGINY = 300;
int ORIGINX1 = 20;
int ORIGINY1 = 120;
int ORIGINX2= 20;
int ORIGINY2 = 340;
int ORIGINX3= 20;
int ORIGINY3 = 150;
int ORIGINX4= 20;
int ORIGINY4 = 300;
int ORIGINX5= 720;
int ORIGINY5 = 440;
int ORIGINX6= 20;
int ORIGINY6 = 470;
int XMAX = 320;
int XMAX_COORD3 = 160;
int XMAX_COORD4 = 160;
int XMAX_COORD5 = 160;
int XMAX_COORD6 = 160;
int XGAP = 4;
int YGAP = 20;
int YGAP_C6 = 10;
int MARKLENGTH = 4;
int YP_AMOUT = 12;
int YN_AMOUT = 15;
int Y_COUNTER = 5;
int Y_COUNTER_COORD5 = 20;


const double PI =3.1415926;
//const int MultiplyEachUnitOnX = XGAP*20;
//const int MultiplyEachUnitOnY = YGAP*8;




/////////////////////////////////////////////////////////////////////////////
// CDSPView

IMPLEMENT_DYNCREATE(CDSPView, CView)

BEGIN_MESSAGE_MAP(CDSPView, CView)
	//{{AFX_MSG_MAP(CDSPView)
	ON_COMMAND(ID_COORD_GRID, OnCoordGrid)
	ON_COMMAND(ID_COORD_DOT, OnCoordDot)
	ON_UPDATE_COMMAND_UI(ID_COORD_GRID, OnUpdateCoordGrid)
	ON_UPDATE_COMMAND_UI(ID_COORD_DOT, OnUpdateCoordDot)
	ON_COMMAND(ID_SIN_INPUTPARA, OnDrawSinInputpara)
	ON_COMMAND(ID_TRI_DFT, OnDrawTriDft)
	ON_UPDATE_COMMAND_UI(ID_TRI_DFT, OnUpdateTriDft)
	ON_UPDATE_COMMAND_UI(ID_SIN_INPUTPARA, OnUpdateSinInputpara)
	ON_COMMAND(ID_DIT_FFT, OnDitFft)
	ON_UPDATE_COMMAND_UI(ID_DIT_FFT, OnUpdateDitFft)
	ON_COMMAND(ID_IIR_LP, OnIirLp)
	ON_UPDATE_COMMAND_UI(ID_IIR_LP, OnUpdateIirLp)
	ON_COMMAND(ID_IIR_AP, OnIirAp)
	ON_UPDATE_COMMAND_UI(ID_IIR_AP, OnUpdateIirAp)
	ON_COMMAND(ID_IIR_HP, OnIirHp)
	ON_UPDATE_COMMAND_UI(ID_IIR_HP, OnUpdateIirHp)
	ON_COMMAND(ID_FILTER_TRI, OnFilterTri)
	ON_UPDATE_COMMAND_UI(ID_FILTER_TRI, OnUpdateFilterTri)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPView construction/destruction

CDSPView::CDSPView()
{
	// TODO: add construction code here
	m_Amplitude = 5 ;
	m_Period = XGAP*20;
	m_SampleFreq = 1;
	
	m_dft_point = 128;
	m_tri_amplitude = 4;
	m_tri_count = 3;
	m_tri_pierod = 10;
	
	n_ditfft_level = 7;
	n_ditfft_amplitude = 4;
	n_ditfft_count = 3;
	n_ditfft_pierod = 10;
	
	n_iirhp_carrier_freq = 200;
	n_iirhp_carrier_am = 1;
	n_iirhp_signal_freq = 10;
	n_iirhp_signal_am = 1;
	
	n_iirap_carrier_freq = 200;
	n_iirap_carrier_am = 1;
	n_iirap_signal_freq =10;
	n_iirap_signal_am = 1;
	
	n_iirlp_carrier_freq = 200;
	n_iirlp_carrier_am = 1;
	n_iirlp_signal_freq = 10;
	n_iirlp_signal_am = 1;

	n_filter_carrier_freq = 50;
	n_filter_carrier_am = 2;
	n_filter_signal_freq = 500;
	n_filter_signal_am = 2;

}

CDSPView::~CDSPView()
{
}

BOOL CDSPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
void DrawGridCoord(CDC* pDC)
{
	CString str;
	int XUNIT = 0;
	int YUNIT = 0;
	pDC->MoveTo(ORIGINX,ORIGINY);//设置原点
				
	for(XUNIT = 0;XUNIT < XMAX; XUNIT++)
		{
			if(XUNIT%10)//绘制非整数刻度
			{
				pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY);
				pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH);
				pDC->MoveTo(ORIGINX+XUNIT*XGAP,ORIGINY);
			}
			else//绘制整数刻度和纵向网格线
			{
				pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY);
				pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY-YP_AMOUT*YGAP);
				pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY+YN_AMOUT*YGAP);
				//if(XUNIT%2==0)
				{
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX+XUNIT*XGAP,ORIGINY,str);
				}
				//COUNT+=1;
				pDC->MoveTo(ORIGINX+XUNIT*XGAP,ORIGINY);
			}
		}
		pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY);//绘制X轴箭头
		pDC->LineTo(ORIGINX+XUNIT*XGAP-5,ORIGINY+5);
		pDC->MoveTo(ORIGINX+XUNIT*XGAP,ORIGINY);
		pDC->LineTo(ORIGINX+XUNIT*XGAP-5,ORIGINY-5);	
		pDC->TextOut(ORIGINX+XUNIT*XGAP-5,ORIGINY+5,"X(t/s)");

		pDC->MoveTo(ORIGINX,ORIGINY);//绘制Y轴刻度和横向网格线
		for(YUNIT=-YN_AMOUT;YUNIT<=YP_AMOUT;YUNIT++)
		{
			pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);
			pDC->LineTo(ORIGINX+XMAX*XGAP,ORIGINY-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX,ORIGINY-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);//绘制Y轴箭头
		pDC->LineTo(ORIGINX-5,ORIGINY-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);
		pDC->LineTo(ORIGINX+5,ORIGINY-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX-18,ORIGINY-YUNIT*YGAP-8,"Y");
		for(int m=-3;m<3;m++)//输出Y轴刻度
		{
			str.Format("%d",m*5);
			pDC->TextOut(ORIGINX-20,ORIGINY-m*5*YGAP-10,str);
		}//y轴刻度		

}
void DrawDotCoord(CDC* pDC)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX,ORIGINY);
		pDC->LineTo(ORIGINX+XMAX*XGAP,ORIGINY);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY);
			pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX+XUNIT*XGAP,ORIGINY,str);
				}
			pDC->MoveTo(ORIGINX+XUNIT*XGAP,ORIGINY);	
			
		}
		pDC->LineTo(ORIGINX+XUNIT*XGAP,ORIGINY);//X轴箭头
		pDC->LineTo(ORIGINX+XUNIT*XGAP-5,ORIGINY+5);
		pDC->MoveTo(ORIGINX+XUNIT*XGAP,ORIGINY);
		pDC->LineTo(ORIGINX+XUNIT*XGAP-5,ORIGINY-5);	
		pDC->TextOut(ORIGINX+XUNIT*XGAP-5,ORIGINY+5,"X(t/s)");

		pDC->MoveTo(ORIGINX,ORIGINY);//Y轴
		for(YUNIT=-YN_AMOUT;YUNIT<=YP_AMOUT;YUNIT++)
		{
			pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);
			pDC->LineTo(ORIGINX+MARKLENGTH,ORIGINY-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX,ORIGINY-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(ORIGINX-5,ORIGINY-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX,ORIGINY-YUNIT*YGAP);
		pDC->LineTo(ORIGINX+5,ORIGINY-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX-18,ORIGINY-YUNIT*YGAP-8,"Y");
		for(int m=-3;m<3;m++)
		{
			str.Format("%d",m*5);
			pDC->TextOut(ORIGINX-20,ORIGINY-m*5*YGAP-10,str);
		}//y轴刻度

		CBrush bgBrush(BLACK_BRUSH);//绘制坐标内点状
		pDC->SelectObject(bgBrush);
		for(X_STAR=ORIGINX;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY-YGAP*YP_AMOUT);Y_STAR<=(ORIGINY+YGAP*YN_AMOUT);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}


}

void DrawDotCoord2(CDC* pDC)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX2,ORIGINY2);
		pDC->LineTo(ORIGINX2+XMAX*XGAP,ORIGINY2);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX2+XUNIT*XGAP,ORIGINY2);
			//pDC->LineTo(ORIGINX2+XUNIT*XGAP,ORIGINY2-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX2+XUNIT*XGAP,ORIGINY2-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX2+XUNIT*XGAP,ORIGINY2,str);
				}
			pDC->MoveTo(ORIGINX2+XUNIT*XGAP,ORIGINY2);	
			
		}
		pDC->LineTo(ORIGINX2+XUNIT*XGAP,ORIGINY2);//X轴箭头
		pDC->LineTo(ORIGINX2+XUNIT*XGAP-5,ORIGINY2+5);
		pDC->MoveTo(ORIGINX2+XUNIT*XGAP,ORIGINY2);
		pDC->LineTo(ORIGINX2+XUNIT*XGAP-5,ORIGINY2-5);	
		pDC->TextOut(ORIGINX2+XUNIT*XGAP-5,ORIGINY2+5,"X(t/s)");

		pDC->MoveTo(ORIGINX2,ORIGINY2);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			pDC->LineTo(ORIGINX2,ORIGINY2-YUNIT*YGAP);
			pDC->LineTo(ORIGINX2+MARKLENGTH,ORIGINY2-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX2,ORIGINY2-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX2,ORIGINY2-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(ORIGINX2-5,ORIGINY2-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX2,ORIGINY2-YUNIT*YGAP);
		pDC->LineTo(ORIGINX2+5,ORIGINY2-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX2-18,ORIGINY2-YUNIT*YGAP-8,"Y");
		for(int m=-4;m<5;m++)
		{
			//if(m%5==0)
				{
					str.Format("%d",m);
					pDC->TextOut(ORIGINX2-20,ORIGINY2-m*YGAP-10,str);
				}
		}//y轴刻度

		CBrush bgBrush(BLACK_BRUSH);//绘制坐标内点状
		pDC->SelectObject(bgBrush);
		for(X_STAR=ORIGINX2;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY2-YGAP*Y_COUNTER);Y_STAR<=(ORIGINY2+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}


}
void DrawDotCoord1(CDC* pDC)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX1,ORIGINY1);
		pDC->LineTo(ORIGINX1+XMAX*XGAP,ORIGINY1);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1);
			//pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX1+XUNIT*XGAP,ORIGINY1,str);
				}
			pDC->MoveTo(ORIGINX1+XUNIT*XGAP,ORIGINY1);	
			
		}
		pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1);//X轴箭头
		pDC->LineTo(ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5);
		pDC->MoveTo(ORIGINX1+XUNIT*XGAP,ORIGINY1);
		pDC->LineTo(ORIGINX1+XUNIT*XGAP-5,ORIGINY1-5);	
		pDC->TextOut(ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5,"X(t/s)");

		pDC->MoveTo(ORIGINX1,ORIGINY1);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);
			pDC->LineTo(ORIGINX1+MARKLENGTH,ORIGINY1-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(ORIGINX1-5,ORIGINY1-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);
		pDC->LineTo(ORIGINX1+5,ORIGINY1-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX1-18,ORIGINY1-YUNIT*YGAP-8,"Y");
		for(int m=-4;m<5;m++)
		{
			//if(m%5==0)
				{
					str.Format("%d",m);
					pDC->TextOut(ORIGINX1-20,ORIGINY1-m*YGAP-10,str);
				}
		}//y轴刻度

		CBrush bgBrush(BLACK_BRUSH);//绘制坐标内点状
		pDC->SelectObject(bgBrush);
		for(X_STAR=ORIGINX1;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY1-YGAP*Y_COUNTER);Y_STAR<=(ORIGINY1+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}


}


/////////////////////////////////////////////////////////////////////////////
// CDSPView drawing

void CDSPView::OnDraw(CDC* pDC)
{

	//int COUNT = 0;


	CString str;
	CDSPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	

	switch(n_mCoordMode)
	{
		case COORD_GRID://绘制网格坐标
			{DrawDotCoord(pDC);
				//pDC->MoveTo(ORIGINX,ORIGINY);//设置原点
				//DrawGridCoord(pDC);
			//	break;
			}
		case COORD_DOT://绘制点状坐标
			{
				DrawDotCoord(pDC);
				break;
			}
		case SINSIGNAL_INPUT:
			{
				DrawDotCoord1(pDC);
				DrawDotCoord2(pDC);
				DrawSinsignal(pDC);
				break;
			}
		case DFT_TRI://绘制网格坐标
			{
				DrawDotCoord3(pDC);
				DrawTriByPierodCount(pDC,m_tri_count,m_tri_pierod,m_tri_amplitude);	
				DrawDotCoord4(pDC);
				DrawTriSignal(pDC,m_dft_point,m_tri_pierod,m_tri_amplitude);
				DrawDotCoord5(pDC);
				DrawDotCoord6(pDC);
				DrawDftAM(pDC);
				break;
			}
		case DIT_FFT:
			{
				int point = (int)pow(2,n_ditfft_level);
				DrawDotCoord3(pDC);
				DrawTriByPierodCount(pDC,n_ditfft_count,n_ditfft_pierod,n_ditfft_amplitude);
				DrawDotCoord4(pDC);
				DrawTriSignal(pDC,point,n_ditfft_pierod,n_ditfft_amplitude);
				DrawDotCoord5(pDC);
				DrawDotCoord6(pDC);
				//DrawDitFFT(pDC);
				m_tri_count=n_ditfft_count;
				m_tri_pierod=n_ditfft_pierod;
				m_tri_amplitude=n_ditfft_amplitude;
				m_dft_point=point;
				DrawDftAM(pDC);
				break;
			}
		case IIR_LP:
			{
				IIR_DrawCoord(pDC,ORIGINX1, ORIGINY1);
				IIR_DrawCoord(pDC,ORIGINX2, ORIGINY2);
				IIRLP_main(pDC);
				break;
			}
		case IIR_AP:
			{
				IIR_DrawCoord(pDC,ORIGINX1, ORIGINY1);
				IIR_DrawCoord(pDC,ORIGINX2, ORIGINY2);
				IIRAP_main(pDC);
				break;
			}
		case IIR_HP:
			{
				IIR_DrawCoord(pDC,ORIGINX1, ORIGINY1);
				IIR_DrawCoord(pDC,ORIGINX2, ORIGINY2);
				IIRHP_main(pDC);
				break;
			}
		case FILTER_TRI:
			{
				IIR_DrawCoord(pDC,ORIGINX1, ORIGINY1);
				IIR_DrawCoord(pDC,ORIGINX2, ORIGINY2);
				Filter_Tri_main( pDC);
				break;
			}
		default:
			{
				//DrawDotCoord(pDC);
				break;
			}
		

		}
	
	

}

/////////////////////////////////////////////////////////////////////////////
// CDSPView printing

BOOL CDSPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDSPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
	
}

void CDSPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDSPView diagnostics

#ifdef _DEBUG
void CDSPView::AssertValid() const
{
	CView::AssertValid();
}

void CDSPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSPDoc* CDSPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSPDoc)));
	return (CDSPDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPView message handlers

void CDSPView::OnCoordGrid() 
{
	// TODO: Add your command handler code here
	n_mCoordMode = COORD_GRID;
	Invalidate(TRUE);
}

void CDSPView::OnCoordDot() 
{
	// TODO: Add your command handler code here
	n_mCoordMode = COORD_DOT;
	Invalidate(TRUE);
	
}

void CDSPView::OnUpdateCoordGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
		if(n_mCoordMode == COORD_GRID)
			flag = 1;
		pCmdUI->SetCheck(flag);
	
}

void CDSPView::OnUpdateCoordDot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		int flag = 0;
		if(n_mCoordMode == COORD_DOT)
			flag = 1;
		pCmdUI->SetCheck(flag);	
}




void CDSPView::OnDrawSinInputpara() 
{
	// TODO: Add your command handler code here
	CinputPara InpPara;
	InpPara.m_Amplitude = m_Amplitude;
	InpPara.m_Period = m_Period;
	InpPara.m_Samplefreq = m_SampleFreq;
	n_mCoordMode = SINSIGNAL_INPUT;

	if(InpPara.DoModal()==IDOK)
	{
		m_Amplitude = InpPara.m_Amplitude;
		m_Period = InpPara.m_Period;
		m_SampleFreq= InpPara.m_Samplefreq ;
		Invalidate(TRUE);
	}
	
}

void CDSPView::DrawSinsignal(CDC *pDC)
{
	CString st1;
	CString st2;
	CString st3;
	CPen PenRed(PS_SOLID,1,RGB(0,255,0));
	pDC->SelectObject(PenRed);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetTextColor(RGB(0,0,255));
	st1.Format("%d",m_Period);
	st2.Format("%d",m_Amplitude);
	st3.Format("%d",m_SampleFreq);
	pDC->TextOut(ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-8*YGAP,"输入SIN正弦函数:");
	pDC->TextOut(ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-7*YGAP,"周期="+st1);
	pDC->TextOut(ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-6*YGAP,"幅度="+st2);
	pDC->TextOut(ORIGINX2+(XMAX-20)*XGAP,ORIGINY2-6*YGAP,"抽样频率="+st3);

	pDC->MoveTo(ORIGINX1,ORIGINY1);//画连续SIN信号
	for(double i = 0;i< 200; i+=0.01)//XMAX
		{
			double j = sin(PI/(m_Period/2)*i)*m_Amplitude;
			pDC->SetPixel(ORIGINX1+i*XGAP,j*YGAP+ORIGINY1,RGB(255,0,0));
			
		}
	pDC->MoveTo(ORIGINX2,ORIGINY2);//画抽样后的信号

	for(double m = 0;m< 200;m+=m_SampleFreq)//XMAX
		{
			double n = sin(PI/(m_Period/2)*m)*m_Amplitude;
			pDC->MoveTo(ORIGINX2+m*XGAP,ORIGINY2);
			pDC->LineTo(ORIGINX2+m*XGAP,ORIGINY2+ n*YGAP);
			pDC->Ellipse(ORIGINX2+m*XGAP-2,ORIGINY2+ n*YGAP+2,ORIGINX2+m*XGAP+2,ORIGINY2+ n*YGAP-2);
			
		}
	CPen PenBlack(PS_SOLID,1,RGB(255,255,255));
	pDC->SelectObject(PenRed);
	

}

void CDSPView::OnDrawTriDft() 
{
	// TODO: Add your command handler code here
	CDftParaInput InpPara;
	InpPara.m_dft_point = m_dft_point;
	InpPara.m_tri_amplitude = m_tri_amplitude;
	InpPara.m_tri_count = m_tri_count;
	InpPara.m_tri_pierod = m_tri_pierod;
	n_mCoordMode = DFT_TRI;

	if(InpPara.DoModal()==IDOK)
	{
		m_dft_point = InpPara.m_dft_point;
		m_tri_amplitude = InpPara.m_tri_amplitude;
		m_tri_count= InpPara.m_tri_count ;
		m_tri_pierod= InpPara.m_tri_pierod ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
	
}

void CDSPView::DrawTriSignal(CDC *pDC,int point,int pierod,int amplitude)
{//pierod=160;
	CString st1;
	int signal_xstart ;
	int signal_ystart ;
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,255,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX4,ORIGINY4);
	int middle_value = 0;
	int dsitance_value = 0;
	for(signal_xstart =0;signal_xstart<point;signal_xstart+=1)
		{
			if(signal_xstart<pierod)
			{
				middle_value = pierod/2;
				dsitance_value = abs(signal_xstart-middle_value);
				signal_ystart = amplitude*YGAP*(middle_value-dsitance_value)/middle_value;
				pDC->LineTo(ORIGINX4+signal_xstart*XGAP,ORIGINY4-signal_ystart);
				pDC->Ellipse(ORIGINX4+signal_xstart*XGAP-2,ORIGINY4-signal_ystart+2,ORIGINX4+signal_xstart*XGAP+2,ORIGINY4-signal_ystart-2);
				pDC->MoveTo(ORIGINX4+(signal_xstart+1)*XGAP,ORIGINY4);	
				
			}
			else
			{
				signal_ystart = 0;
				pDC->Ellipse(ORIGINX4+signal_xstart*XGAP-2,ORIGINY4-signal_ystart+2,ORIGINX4+signal_xstart*XGAP+2,ORIGINY4-signal_ystart-2);
			}
		}
	pDC->SelectObject(PenOld);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetTextColor(RGB(0,0,255));
	st1.Format("%d",point);
	pDC->TextOut(ORIGINX4+(XMAX_COORD4-30)*XGAP,ORIGINY4-4*YGAP,"幅频特性");
	pDC->TextOut(1000,ORIGINY4-4*YGAP,"DFT取点数=128");
	pDC->SetTextColor(RGB(0,0,0));
}

void CDSPView::OnUpdateTriDft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == DFT_TRI)
		flag = 1;
	pCmdUI->SetCheck(flag);	
	
}

void CDSPView::OnUpdateSinInputpara(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == SINSIGNAL_INPUT)
		flag = 1;
	pCmdUI->SetCheck(flag);	
	
	
}

void CDSPView::DrawTriByPierodCount(CDC *pDC,int count,int pierod,int amplitude)
{
	CString st1;
	CString st2;
	CString st3;
	int signal_xstart = ORIGINX3 ;
	int signal_ystart = ORIGINY3;
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX3,ORIGINY3);
	for(int m =1;m<=2*count;m++)
		{
			if(signal_xstart<=XMAX_COORD3*XGAP)
			{
				signal_xstart=signal_xstart+(pierod*XGAP/2);
				if(m%2)
				{
					signal_ystart = ORIGINY3 - amplitude*YGAP;
					pDC->LineTo(signal_xstart,signal_ystart);
					pDC->MoveTo(signal_xstart,signal_ystart);
				}
				else
				{
					signal_ystart = ORIGINY3;
					pDC->LineTo(signal_xstart,signal_ystart);
					pDC->MoveTo(signal_xstart,signal_ystart);				
				}
			}
		}
		pDC->SelectObject(PenOld);
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(55,55,55));
		st1.Format("%d",pierod);
		st2.Format("%d",amplitude);
		st3.Format("%d",count);
		pDC->TextOut(ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-7*YGAP,"三角波周期="+st1);
		pDC->TextOut(ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-6*YGAP,"幅度="+st2);
		pDC->TextOut(ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-5*YGAP,"周期个数="+st3);
		pDC->SetTextColor(RGB(0,0,0));
}

void CDSPView::DrawDotCoord3(CDC *pDC)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
	pDC->MoveTo(ORIGINX3,ORIGINY3);
	pDC->LineTo(ORIGINX3+XMAX_COORD3*XGAP,ORIGINY3);
	for(XUNIT = 0;XUNIT < XMAX_COORD3; XUNIT++)//绘制X轴和X轴刻度
	{
		pDC->LineTo(ORIGINX3+XUNIT*XGAP,ORIGINY3);
		pDC->LineTo(ORIGINX3+XUNIT*XGAP,ORIGINY3-MARKLENGTH);
		
			
		if(XUNIT%10==0)
			{
				pDC->LineTo(ORIGINX3+XUNIT*XGAP,ORIGINY3-MARKLENGTH*2);
				pDC->MoveTo(ORIGINX3+XUNIT*XGAP,ORIGINY3);
				pDC->LineTo(ORIGINX3+XUNIT*XGAP,ORIGINY3+MARKLENGTH*2);
				str.Format("%d",XUNIT);
				pDC->TextOut(ORIGINX3+XUNIT*XGAP,ORIGINY3,str);
			}
		pDC->MoveTo(ORIGINX3+XUNIT*XGAP,ORIGINY3);	
		
	}
	pDC->LineTo(ORIGINX3+XUNIT*XGAP,ORIGINY3);//X轴箭头
	pDC->LineTo(ORIGINX3+XUNIT*XGAP-5,ORIGINY3+5);
	pDC->MoveTo(ORIGINX3+XUNIT*XGAP,ORIGINY3);
	pDC->LineTo(ORIGINX3+XUNIT*XGAP-5,ORIGINY3-5);	
	pDC->TextOut(ORIGINX3+XUNIT*XGAP-5,ORIGINY3+5,"T(s)");

	pDC->MoveTo(ORIGINX3,ORIGINY3);//Y轴
	for(YUNIT=0;YUNIT<Y_COUNTER;YUNIT++)
	{
		pDC->LineTo(ORIGINX3,ORIGINY3-YUNIT*YGAP);
		pDC->LineTo(ORIGINX3+MARKLENGTH,ORIGINY3-YUNIT*YGAP);
		pDC->MoveTo(ORIGINX3,ORIGINY3-YUNIT*YGAP);  
	}
	pDC->LineTo(ORIGINX3,ORIGINY3-YUNIT*YGAP);//Y轴箭头
	pDC->LineTo(ORIGINX3-5,ORIGINY3-YUNIT*YGAP+5);
	pDC->LineTo(ORIGINX3,ORIGINY3-YUNIT*YGAP);
	pDC->LineTo(ORIGINX3+5,ORIGINY3-YUNIT*YGAP+5);
	pDC->TextOut(ORIGINX3-18,ORIGINY3-(YUNIT+1)*YGAP,"幅度");
	for(int m=0;m<5;m++)
	{	
			{
				str.Format("%d",m);
				pDC->TextOut(ORIGINX3-20,ORIGINY3-m*YGAP-10,str);
			}
	}//y轴刻度

}

void CDSPView::DrawDotCoord4(CDC *pDC)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
	pDC->MoveTo(ORIGINX4,ORIGINY4);
	pDC->LineTo(ORIGINX4+XMAX_COORD4*XGAP,ORIGINY4);
	for(XUNIT = 0;XUNIT < XMAX_COORD4; XUNIT++)//绘制X轴和X轴刻度
	{
		pDC->LineTo(ORIGINX4+XUNIT*XGAP,ORIGINY4);
		pDC->LineTo(ORIGINX4+XUNIT*XGAP,ORIGINY4-MARKLENGTH);
		
			
		if(XUNIT%10==0)
			{
				pDC->LineTo(ORIGINX4+XUNIT*XGAP,ORIGINY4-MARKLENGTH*2);
				pDC->MoveTo(ORIGINX4+XUNIT*XGAP,ORIGINY4);
				pDC->LineTo(ORIGINX4+XUNIT*XGAP,ORIGINY4+MARKLENGTH*2);
				str.Format("%d",XUNIT);
				pDC->TextOut(ORIGINX4+XUNIT*XGAP,ORIGINY4,str);
			}
		pDC->MoveTo(ORIGINX4+XUNIT*XGAP,ORIGINY4);	
		
	}
	pDC->LineTo(ORIGINX4+XUNIT*XGAP,ORIGINY4);//X轴箭头
	pDC->LineTo(ORIGINX4+XUNIT*XGAP-5,ORIGINY4+5);
	pDC->MoveTo(ORIGINX4+XUNIT*XGAP,ORIGINY4);
	pDC->LineTo(ORIGINX4+XUNIT*XGAP-5,ORIGINY4-5);	
	pDC->TextOut(ORIGINX4+XUNIT*XGAP-5,ORIGINY4+5,"N");

	pDC->MoveTo(ORIGINX4,ORIGINY4);//Y轴
	for(YUNIT=0;YUNIT<Y_COUNTER;YUNIT++)
	{
		pDC->LineTo(ORIGINX4,ORIGINY4-YUNIT*YGAP);
		pDC->LineTo(ORIGINX4+MARKLENGTH,ORIGINY4-YUNIT*YGAP);
		pDC->MoveTo(ORIGINX4,ORIGINY4-YUNIT*YGAP);  
	}
	pDC->LineTo(ORIGINX4,ORIGINY4-YUNIT*YGAP);//Y轴箭头
	pDC->LineTo(ORIGINX4-5,ORIGINY4-YUNIT*YGAP+5);
	pDC->LineTo(ORIGINX4,ORIGINY4-YUNIT*YGAP);
	pDC->LineTo(ORIGINX4+5,ORIGINY4-YUNIT*YGAP+5);
	pDC->TextOut(ORIGINX4-18,ORIGINY4-(YUNIT+1)*YGAP,"幅度");
	for(int m=0;m<5;m++)
	{	
			{
				str.Format("%d",m);
				pDC->TextOut(ORIGINX4-20,ORIGINY4-m*YGAP-10,str);
			}
	}//y轴刻度	
}

void CDSPView::DrawDftAM(CDC *pDC)
{
	CString str1;
	CString str2;
	double array_sample[320]={0};
	double array_Re[320]={0};
	double array_Im[320]={0};
	double array_AmValue[320]={0};
	double phase_value[320]={0};

	double Basic_value = 2*PI/m_dft_point;
	double middle_value = 0;
	double dsitance_value = 0;
	for(int i = 0;i<m_dft_point;i++)
		{
			if(i < m_tri_pierod)
				{
					middle_value =(double)m_tri_pierod/2;
					dsitance_value = abs(i-middle_value);
					array_sample[i] = m_tri_amplitude*(middle_value-dsitance_value)/middle_value;
				}
			else{
					array_sample[i] = 0;
				}
		}
	for(int N = 0;N < m_dft_point;N++)
		{
			double Re_value = 0;
			double Im_value = 0;
			for(int M = 0 ;M < m_dft_point; M++ )
				{
					Re_value+=(float)(array_sample[M]*cos(Basic_value*M*N));
					Im_value+=(float)(-(array_sample[M])*sin(Basic_value*M*N));
				}
			array_AmValue[N] = pow(Re_value*Re_value+Im_value*Im_value,0.5);
			phase_value[N] = atan(-Im_value/Re_value)*180/PI;
		}
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	for(int K = 0;K < m_dft_point;K++)
		{
			pDC->MoveTo(ORIGINX5+K*XGAP,ORIGINY5); 
			pDC->LineTo(ORIGINX5+K*XGAP,(int)(ORIGINY5-array_AmValue[K]*YGAP)); 
			pDC->Ellipse(ORIGINX5+K*XGAP-2,(int)(ORIGINY5-array_AmValue[K]*YGAP-2),
						ORIGINX5+K*XGAP+2,(int)(ORIGINY5-array_AmValue[K]*YGAP+2));
		}
	for(int  M = 0;M < m_dft_point;M++)
		{
			pDC->MoveTo(ORIGINX6+M*XGAP,ORIGINY6); 
			pDC->LineTo(ORIGINX6+M*XGAP,(int)(ORIGINY6-phase_value[M])); 
			pDC->Ellipse(ORIGINX6+M*XGAP-2,(int)(ORIGINY6-phase_value[M]-2),
						ORIGINX6+M*XGAP+2,(int)(ORIGINY6-phase_value[M]+2));
		}
	pDC->SelectObject(PenOld);

}

void CDSPView::DrawDotCoord1ByDftAm(CDC *pDC)
{
	CString str;
	CString st1;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX1,ORIGINY1+5*YGAP);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP);
				
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP,str);
				}
			pDC->MoveTo(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP);	
			
		}
		pDC->LineTo(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP);//X轴箭头
		pDC->LineTo(ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5*YGAP+5);
		pDC->MoveTo(ORIGINX1+XUNIT*XGAP,ORIGINY1+5*YGAP);
		pDC->LineTo(ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5*YGAP-5);	
		pDC->TextOut(ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5*YGAP+5,"|X(n)|");

		pDC->MoveTo(ORIGINX1,ORIGINY1+5*YGAP);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);
			pDC->LineTo(ORIGINX1+MARKLENGTH,ORIGINY1-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(ORIGINX1-5,ORIGINY1-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX1,ORIGINY1-YUNIT*YGAP);
		pDC->LineTo(ORIGINX1+5,ORIGINY1-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX1-18,ORIGINY1-YUNIT*YGAP-8,"Y");
		for(int m=0;m<10;m++)
		{
			str.Format("%d",m);
			pDC->TextOut(ORIGINX1-20,ORIGINY1+5*YGAP-m*YGAP-10,str);
		}//y轴刻度

		CBrush bgBrush(BLACK_BRUSH);//绘制坐标内点状
		pDC->SelectObject(bgBrush);
		for(X_STAR=ORIGINX1;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY1-YGAP*Y_COUNTER);Y_STAR<=(ORIGINY1+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(0,0,255));
		st1.Format("%d",m_dft_point);
		pDC->TextOut(ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-4*YGAP,"幅度");
		pDC->SetTextColor(RGB(0,0,0));


}

void CDSPView::DrawDotCoord5(CDC *pDC)
{
	CString str;
	CString st1;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX5,ORIGINY5);
		for(XUNIT = 0;XUNIT < XMAX_COORD5; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX5+XUNIT*XGAP,ORIGINY5);
			pDC->LineTo(ORIGINX5+XUNIT*XGAP,ORIGINY5-MARKLENGTH);
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX5+XUNIT*XGAP,ORIGINY5-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX5+XUNIT*XGAP,ORIGINY5,str);
				}
			pDC->MoveTo(ORIGINX5+XUNIT*XGAP,ORIGINY5);	
			
		}
		pDC->LineTo(ORIGINX5+XUNIT*XGAP,ORIGINY5);//X轴箭头
		pDC->LineTo(ORIGINX5+XUNIT*XGAP-5,ORIGINY5+5);
		pDC->MoveTo(ORIGINX5+XUNIT*XGAP,ORIGINY5);
		pDC->LineTo(ORIGINX5+XUNIT*XGAP-5,ORIGINY5-5);	
		pDC->TextOut(ORIGINX5+XUNIT*XGAP-5,ORIGINY5+5,"N");

		pDC->MoveTo(ORIGINX5,ORIGINY5);//Y轴
		for(YUNIT=0;YUNIT<Y_COUNTER_COORD5;YUNIT++)
		{
			pDC->LineTo(ORIGINX5,ORIGINY5-YUNIT*YGAP);
			pDC->LineTo(ORIGINX5+MARKLENGTH,ORIGINY5-YUNIT*YGAP);
			pDC->MoveTo(ORIGINX5,ORIGINY5-YUNIT*YGAP);  
		}
		pDC->LineTo(ORIGINX5,ORIGINY5-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(ORIGINX5-5,ORIGINY5-YUNIT*YGAP+5);
		pDC->LineTo(ORIGINX5,ORIGINY5-YUNIT*YGAP);
		pDC->LineTo(ORIGINX5+5,ORIGINY5-YUNIT*YGAP+5);
		pDC->TextOut(ORIGINX5-18,ORIGINY5-(YUNIT+1)*YGAP,"|X(n)|");
		for(int m=0;m<Y_COUNTER_COORD5;m++)
		{
			str.Format("%d",m);
			pDC->TextOut(ORIGINX5-20,ORIGINY5-m*YGAP-10,str);
		}//y轴刻度

		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(55,55,55));
		st1.Format("%d",m_dft_point);
		pDC->TextOut(ORIGINX5+(XMAX_COORD5-20)*XGAP,ORIGINY5-Y_COUNTER_COORD5*YGAP,"幅度特性");
		pDC->SetTextColor(RGB(0,0,0));


}

void CDSPView::DrawDotCoord6(CDC *pDC)
{
	CString str;
	CString st1;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(ORIGINX6,ORIGINY6);
		pDC->LineTo(ORIGINX6+XMAX_COORD6*XGAP,ORIGINY6);
		for(XUNIT = 0;XUNIT < XMAX_COORD6; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(ORIGINX6+XUNIT*XGAP,ORIGINY6);
			pDC->LineTo(ORIGINX6+XUNIT*XGAP,ORIGINY6-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					pDC->LineTo(ORIGINX6+XUNIT*XGAP,ORIGINY6-MARKLENGTH*2);
					str.Format("%d",XUNIT);
					pDC->TextOut(ORIGINX6+XUNIT*XGAP,ORIGINY6,str);
				}
			pDC->MoveTo(ORIGINX6+XUNIT*XGAP,ORIGINY6);	
			
		}
		pDC->LineTo(ORIGINX6+XUNIT*XGAP,ORIGINY6);//X轴箭头
		pDC->LineTo(ORIGINX6+XUNIT*XGAP-5,ORIGINY6+5);
		pDC->MoveTo(ORIGINX6+XUNIT*XGAP,ORIGINY6);
		pDC->LineTo(ORIGINX6+XUNIT*XGAP-5,ORIGINY6-5);	
		pDC->TextOut(ORIGINX6+XUNIT*XGAP-5,ORIGINY6+5,"N");

		pDC->MoveTo(ORIGINX6,ORIGINY6);//Y轴
		for(YUNIT=-9;YUNIT<=9;YUNIT++)
		{
			pDC->LineTo(ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);
			pDC->LineTo(ORIGINX6+MARKLENGTH,ORIGINY6-YUNIT*YGAP_C6);
			pDC->MoveTo(ORIGINX6,ORIGINY6-YUNIT*10);  
		}
		pDC->LineTo(ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);//Y轴箭头
		pDC->LineTo(ORIGINX6-5,ORIGINY6-YUNIT*YGAP_C6+5);
		pDC->LineTo(ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);
		pDC->LineTo(ORIGINX6+5,ORIGINY6-YUNIT*YGAP_C6+5);
		pDC->TextOut(ORIGINX6-18,ORIGINY6-(YUNIT+2)*YGAP_C6,"arg[X[n]]");
		for(int m=-9;m<=9;m++)
		{
			if(m%2)
				{
					str.Format("%d",m*10);
					pDC->TextOut(ORIGINX6-30,ORIGINY6-m*10,str);
				}
		}//y轴刻度
		for(X_STAR=ORIGINX6;X_STAR<=(160+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY6-YGAP_C6*5);Y_STAR<=(ORIGINY6+YGAP_C6*9);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(55,55,55));
		pDC->TextOut(ORIGINX6+(XMAX_COORD6-20)*XGAP,ORIGINY6-5*YGAP,"相位特性");
		pDC->SetTextColor(RGB(0,0,0));

}

void CDSPView::OnDitFft() 
{
	// TODO: Add your command handler code here
	CDifFFTInput InpPara;
	InpPara.m_ditfft_level= n_ditfft_level;
	InpPara.m_ditfft_amplitude = n_ditfft_amplitude;
	InpPara.m_ditfft_count = n_ditfft_count;
	InpPara.m_ditfft_pierod =n_ditfft_pierod;
	n_mCoordMode = DIT_FFT;

	if(InpPara.DoModal()==IDOK)
	{
		n_ditfft_level = InpPara.m_ditfft_level;
		n_ditfft_amplitude = InpPara.m_ditfft_amplitude;
		n_ditfft_count= InpPara.m_ditfft_count ;
		n_ditfft_pierod= InpPara.m_ditfft_pierod ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
	
}

void CDSPView::OnUpdateDitFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		int flag = 0;
	if(n_mCoordMode == DIT_FFT)
		flag = 1;
	pCmdUI->SetCheck(flag);	
	
}
void CDSPView::DrawDitFFT(CDC *pDC)
{

	
	double middle_value = 0;
	double dsitance_value = 0;
	
	float am_value = 0.0f;
	float phase_value = 0.0f;
	int M = n_ditfft_level;
	int N=(INT)pow(2,M);
	
	Complex 	A[160];
	for( int j = 0;j<N-1;j++)
	{
		if(j< n_ditfft_pierod)
			{
				middle_value =(double)n_ditfft_pierod/2;
				dsitance_value = abs(j-middle_value);
				A[j].Re= n_ditfft_amplitude*(middle_value-dsitance_value)/middle_value;
				A[j].Im= 0;
			}
		else
			{
				A[j].Re = 0;
				A[j].Im = 0;
			}
	}

/////////////////倒位序/////////////
	//ReverseOrder(A[0], N);
	int NV2=N/2;
	int NM1=N-1;
	int I1,J1,K1=0;
	Complex T1;
	I1=J1=1;
	while(I1<=NM1)
		{
			if(I1<J1)
			{
				T1=A[J1-1];
				A[J1-1]=A[I1-1];
				A[I1-1]=T1;
			}
			K1=NV2;
			while(K1<J1)
				{
					J1-=K1;
					K1/=2;
				}
			J1+=K1;
			I1++;		
		}
///////////////////////////DFT-FFT//////
	//double URe,UIm,WRe,WIm,TRe,TIm;
	Complex U,W,T2;
	int LE,LE1,I2,J2,IP;
	int L=1;
	while(L<=M)
		{
			LE=(int)pow(2,L);
			LE1=LE/2;
			U.Re=1.0;
			U.Im=0.0;
			W.Re=(float)cos(PI/(1.0*LE1));
			W.Im=(float)-1.0*sin(PI/(1.0*LE1));
			if(abs(W.Re)<1.0e-12)W.Re=0.0f;
			if(abs(W.Im)<1.0e-12)W.Re=0.0f;
			J2=1;
			while(J2<=LE1)
				{
					I2=J2;
					while(I2<=N)
						{
							IP=I2+LE1;
							T2.Re=(float)A[IP-1].Re*U.Re-A[IP-1].Im*U.Im;//计算复数运算A*U
							T2.Im=(float)A[IP-1].Re*U.Im+A[IP-1].Im*U.Re;
							A[IP-1].Re=(float)A[I2-1].Re-T2.Re;//计算复数运算A-T
							A[IP-1].Im=(float)A[I2-1].Im-T2.Im;
							A[I2-1].Re+=T2.Re;//计算复数运算A+T
							A[I2-1].Im+=T2.Im;
							I2+=LE;
						}
					float temp =U.Re;
					U.Re=(float)U.Re*W.Re-U.Im*W.Im;
					U.Im=(float)temp*W.Im+U.Im*W.Re;
					J2++;
				}
			L++;
			
		}
//////////////////////////////////////画值
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	for(int K2 = 0;K2 < N;K2++)
		{
			
			am_value=sqrt(A[K2].Re*A[K2].Re+A[K2].Im*A[K2].Im);
			pDC->MoveTo(ORIGINX5+K2*XGAP,ORIGINY5); 
			pDC->LineTo(ORIGINX5+K2*XGAP,(int)(ORIGINY5-am_value*YGAP)); 
			pDC->Ellipse(ORIGINX5+K2*XGAP-2,(int)(ORIGINY5-am_value*YGAP-2),
						ORIGINX5+K2*XGAP+2,(int)(ORIGINY5-am_value*YGAP+2));
		}
	for(int  M2 = 0;M2 < N;M2++)
		{
			
			phase_value = atan(-A[M2].Im/A[M2].Re)*180/PI;
			pDC->MoveTo(ORIGINX6+M2*XGAP,ORIGINY6); 
			pDC->LineTo(ORIGINX6+M2*XGAP,(int)(ORIGINY6-phase_value)); 
			pDC->Ellipse(ORIGINX6+M2*XGAP-2,(int)(ORIGINY6-phase_value-2),
						ORIGINX6+M2*XGAP+2,(int)(ORIGINY6-phase_value+2));
		}
	pDC->SelectObject(PenOld);	
}


void CDSPView::OnIirLp() 
{	
	// TODO: Add your command handler code here
	CIIRLPInput InpPara;
	InpPara.m_iirlp_carrier_am= n_iirlp_carrier_am;
	InpPara.m_iirlp_carrier_freq = n_iirlp_carrier_freq;
	InpPara.m_iirlp_signal_freq = n_iirlp_signal_freq;
	InpPara.m_iirlp_signal_am = n_iirlp_signal_am;
	n_mCoordMode = IIR_LP;

	if(InpPara.DoModal()==IDOK)
	{
		n_iirlp_carrier_am = InpPara.m_iirlp_carrier_am;
		n_iirlp_carrier_freq = InpPara.m_iirlp_carrier_freq;
		n_iirlp_signal_freq= InpPara.m_iirlp_signal_freq ;
		n_iirlp_signal_am= InpPara.m_iirlp_signal_am ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
}

void CDSPView::OnUpdateIirLp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == IIR_LP)
		flag = 1;
	pCmdUI->SetCheck(flag);	
}

void CDSPView::OnIirAp() 
{	
	// TODO: Add your command handler code here
	CIIRAPInput InpPara;
	InpPara.m_iirap_carrier_am= n_iirap_carrier_am;
	InpPara.m_iirap_carrier_freq = n_iirap_carrier_freq;
	InpPara.m_iirap_signal_freq = n_iirap_signal_freq;
	InpPara.m_iirap_signal_am = n_iirap_signal_am;
	n_mCoordMode = IIR_AP;

	if(InpPara.DoModal()==IDOK)
	{
		n_iirap_carrier_am = InpPara.m_iirap_carrier_am;
		n_iirap_carrier_freq = InpPara.m_iirap_carrier_freq;
		n_iirap_signal_freq= InpPara.m_iirap_signal_freq ;
		n_iirap_signal_am= InpPara.m_iirap_signal_am ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
}

void CDSPView::OnUpdateIirAp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == IIR_AP)
		flag = 1;
	pCmdUI->SetCheck(flag);	
}

void CDSPView::OnIirHp() 
{	
	// TODO: Add your command handler code here
	CIIRHPInput InpPara;
	InpPara.m_iirhp_carrier_am= n_iirhp_carrier_am;
	InpPara.m_iirhp_carrier_freq = n_iirhp_carrier_freq;
	InpPara.m_iirhp_signal_freq = n_iirhp_signal_freq;
	InpPara.m_iirhp_signal_am = n_iirhp_signal_am;
	n_mCoordMode = IIR_HP;

	if(InpPara.DoModal()==IDOK)
	{
		n_iirhp_carrier_am = InpPara.m_iirhp_carrier_am;
		n_iirhp_carrier_freq = InpPara.m_iirhp_carrier_freq;
		n_iirhp_signal_freq= InpPara.m_iirhp_signal_freq ;
		n_iirhp_signal_am= InpPara.m_iirhp_signal_am ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
}

void CDSPView::OnUpdateIirHp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == IIR_HP)
		flag = 1;
	pCmdUI->SetCheck(flag);	
}

void CDSPView::IIR_DrawCoord(CDC *pDC, int originalX, int originalY)
{
	CString str;
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		pDC->MoveTo(originalX,originalY);
		pDC->LineTo(originalX+XMAX*XGAP,originalY);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			pDC->LineTo(originalX+XUNIT*XGAP,originalY);
				
			if(XUNIT*5%100==0)
				{
					pDC->LineTo(originalX+XUNIT*XGAP,originalY-MARKLENGTH*2);
					if(n_mCoordMode==FILTER_TRI)
						{
							str.Format("%d",XUNIT/2);
						}
					else
						{
							str.Format("%d",XUNIT*XGAP);
						}
					pDC->TextOut(originalX+XUNIT*XGAP,originalY,str);
				}
			pDC->MoveTo(originalX+XUNIT*XGAP,originalY);	
			
		}
		pDC->LineTo(originalX+XUNIT*XGAP,originalY);//X轴箭头
		pDC->LineTo(originalX+XUNIT*XGAP-5,originalY+5);
		pDC->MoveTo(originalX+XUNIT*XGAP,originalY);
		pDC->LineTo(originalX+XUNIT*XGAP-5,originalY-5);	
		pDC->TextOut(originalX+XUNIT*XGAP-5,originalY+5,"X(t/ms)");

		pDC->MoveTo(originalX,originalY);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			pDC->LineTo(originalX,originalY-YUNIT*YGAP);
			pDC->LineTo(originalX+MARKLENGTH,originalY-YUNIT*YGAP);
			pDC->MoveTo(originalX,originalY-YUNIT*YGAP);  
		}
		pDC->LineTo(originalX,originalY-YUNIT*YGAP);//Y轴箭头
		pDC->LineTo(originalX-5,originalY-YUNIT*YGAP+5);
		pDC->LineTo(originalX,originalY-YUNIT*YGAP);
		pDC->LineTo(originalX+5,originalY-YUNIT*YGAP+5);
		pDC->TextOut(originalX-18,originalY-YUNIT*YGAP-8,"Y");
		for(int m=-4;m<5;m++)
		{
			//if(m%5==0)
				{
					str.Format("%d",m);
					pDC->TextOut(originalX-20,originalY-m*YGAP-10,str);
				}
		}//y轴刻度

		CBrush bgBrush(BLACK_BRUSH);//绘制坐标内点状
		pDC->SelectObject(bgBrush);
		for(X_STAR=originalX;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(originalY-YGAP*Y_COUNTER);Y_STAR<=(originalY+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						pDC->SetPixel(X_STAR,Y_STAR,RGB(0,125,125));
					}
			}


}

void CDSPView::IIRLP_main(CDC *pDC)
{
	CString st1;
	CString st2;
	CString st3;
	CString st4;
	double signal[1200]={0},signal_pass[1200]={0},
		ww1[1200]={0},wy1[1200]={0},
		ww2[1200]={0},wy2[1200]={0},
		ww3[1200]={0},wy3[1200]={0};
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX1, ORIGINY1);
	for(int i=0;i<(XMAX-20)*XGAP;i++ )
		{
			signal[i]=n_iirlp_signal_am*sin(2*PI*n_iirlp_signal_freq*i*0.001)+n_iirlp_carrier_am*sin(2*PI*n_iirlp_carrier_freq*i*0.001);
			pDC->LineTo(ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
		}
//------低通滤波器核心程序---------------
		ww1[0]=signal[0];
		ww1[1]=signal[1]+1.2971*signal[0];
		ww2[0]=signal[0];
		ww2[1]=signal[1]+1.0691*signal[0];
		ww3[0]=signal[0];
		ww3[1]=signal[1]+0.9972*signal[0];
		wy1[0]=0.2871*ww1[0];
		wy1[1]=0.2871*ww1[1]-0.4466*ww1[0];
		wy2[0]=-2.1428*ww2[0];
		wy2[1]=-2.1428*ww2[1]+1.1454*ww2[0];
		wy3[0]=1.8558*ww3[0];
		wy3[1]=1.8558*ww3[1]-0.6304*ww3[0];
		signal_pass[0]=wy3[0]+wy2[0]+wy1[0];
		signal_pass[1]=wy3[1]+wy2[1]+wy1[1];
		for (i=2;i<=(XMAX-20)*XGAP;i++)
		{
			ww1[i]=signal[i]+1.2971*ww1[i-1]-0.6949*ww1[i-2];
			ww2[i]=signal[i]+1.0691*ww2[i-1]-0.3699*ww2[i-2];
			ww3[i]=signal[i]+0.9972*ww3[i-1]-0.2570*ww3[i-2];
			wy1[i]=0.2871*ww1[i]-0.4466*ww1[i-1];
			wy2[i]=-2.1428*ww2[i]+1.1454*ww2[i-1];
			wy3[i]=1.8558*ww3[i]-0.6304*ww3[i-1];
			signal_pass[i]=wy3[i]+wy2[i]+wy1[i];
		}  
		
		pDC->MoveTo(ORIGINX2,ORIGINY2);
		for (i=0;i<=(XMAX-20)*XGAP;i++)
		{
			pDC->LineTo(ORIGINX2+i,ORIGINY2-(int)(signal_pass[i]*YGAP));
		}

		pDC->SelectObject(PenOld);
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(0,0,255));
		st1.Format("%d",n_iirlp_signal_am);
		st2.Format("%d Hz",n_iirlp_signal_freq);
		st3.Format("%d",n_iirlp_carrier_am);
		st4.Format("%d Hz",n_iirlp_carrier_freq);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-9*YGAP,"信号幅度="+st1);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-8*YGAP,"信号频率="+st2);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,"载波幅度="+st3);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,"载波频率="+st4);
		pDC->TextOut(ORIGINX2+(XMAX_COORD3-30)*XGAP,ORIGINY2-6*YGAP,"低通滤波后:");
		pDC->SetTextColor(RGB(0,0,0));

}

void CDSPView::IIRAP_main(CDC *pDC)
{
	CString st1;
	CString st2;
	CString st3;
	CString st4;
	double signal[1200]={0},signal_pass[1200]={0};
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX1, ORIGINY1);
	for(int i=0;i<(XMAX-20)*XGAP;i++ )
		{
			signal[i]=n_iirap_signal_am*sin(2*PI*n_iirap_signal_freq*i*0.001)+n_iirap_carrier_am*sin(2*PI*n_iirap_carrier_freq*i*0.001);
			pDC->LineTo(ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
		}
	pDC->MoveTo(ORIGINX2,ORIGINY2);
	for (i=0;i<=(XMAX-20)*XGAP;i++)
		{
			signal_pass[i]=signal[i];
			pDC->LineTo(ORIGINX2+i,ORIGINY2-(int)(signal_pass[i]*YGAP));
		}

		pDC->SelectObject(PenOld);
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetTextColor(RGB(0,0,255));
		st1.Format("%d",n_iirap_signal_am);
		st2.Format("%d Hz",n_iirap_signal_freq);
		st3.Format("%d",n_iirap_carrier_am);
		st4.Format("%d Hz" ,n_iirap_carrier_freq);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-9*YGAP,"信号幅度="+st1);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-8*YGAP,"信号频率="+st2);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,"载波幅度="+st3);
		pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,"载波频率="+st4);
		pDC->TextOut(ORIGINX2+(XMAX_COORD3-30)*XGAP,ORIGINY2-6*YGAP,"全通滤波后:");
		pDC->SetTextColor(RGB(0,0,0));
}

void CDSPView::IIRHP_main(CDC *pDC)
{
	CString st1;
	CString st2;
	CString st3;
	CString st4;
	double signal[1200]={0};
	double w1[1200]={0};
	double yy[1200]={0};
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(100,100,100));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX1, ORIGINY1);
	for(int i=0;i<(200)*XGAP;i++ )
		{
			signal[i]=n_iirhp_signal_am*sin(2*PI*n_iirhp_signal_freq*i*0.001)+n_iirhp_carrier_am*sin(2*PI*n_iirhp_carrier_freq*i*0.001);
			pDC->LineTo(ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
		}
	///高通滤波器核心程序
	w1[0]=signal[0];               
	yy[0]=0.5812137*w1[0];
	w1[1]=signal[1]+0.8606758*w1[0]; 
	yy[1]=0.5812137*w1[1]-1.1624274*w1[0];
	for(i=2;i<=(200)*XGAP;i++)
	{
		w1[i]=signal[i]+0.8606758*w1[i-1]-0.3133033*w1[i-2];
		yy[i]=0.5812137*w1[i]-1.1624274*w1[i-1]+0.5812137*w1[i-2];
	}

	pDC->MoveTo(ORIGINX2,ORIGINY2);
	for(i=1;i<=(200)*XGAP;i++)//XMAX
	{
		pDC->LineTo(ORIGINX2+i,(int)(ORIGINY2-yy[i]*YGAP));
	} 
	pDC->SelectObject(PenOld);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetTextColor(RGB(0,0,255));
	st1.Format("%d",n_iirhp_signal_am);
	st2.Format("%d Hz",n_iirhp_signal_freq);
	st3.Format("%d",n_iirhp_carrier_am);
	st4.Format("%d Hz",n_iirhp_carrier_freq);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-9*YGAP,"信号幅度="+st1);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-8*YGAP,"信号频率="+st2);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,"载波幅度="+st3);
	pDC->TextOut(200,50,"载波频率="+st4);//ORIGINX1+(XMAX_COORD3-30)*XGAP
	pDC->TextOut(200,300,"高通滤波后:");
	pDC->SetTextColor(RGB(0,0,0));
}

void CDSPView::OnFilterTri() 
{	
	// TODO: Add your command handler code here
	CFilterInput InpPara;
	InpPara.m_filter_carrier_am= n_filter_carrier_am;
	InpPara.m_filter_carrier_freq = n_filter_carrier_freq;
	InpPara.m_filter_signal_freq = n_filter_signal_freq;
	InpPara.m_filter_signal_am = n_filter_signal_am;
	n_mCoordMode = FILTER_TRI;

	if(InpPara.DoModal()==IDOK)
	{
		n_filter_carrier_am = InpPara.m_filter_carrier_am;
		n_filter_carrier_freq = InpPara.m_filter_carrier_freq;
		n_filter_signal_freq= InpPara.m_filter_signal_freq ;
		n_filter_signal_am= InpPara.m_filter_signal_am ;
		Invalidate(TRUE);
	}
	Invalidate(TRUE);
}

void CDSPView::OnUpdateFilterTri(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int flag = 0;
	if(n_mCoordMode == FILTER_TRI)
		flag = 1;
	pCmdUI->SetCheck(flag);	
}

void CDSPView::Filter_Tri_main(CDC *pDC)
{
	CString st1;
	CString st2;
	CString st3;
	CString st4;
	int i;
	double signal[1200]={0};
	double tri[1200]={0};
	double carrier[1200]={0};
	double w1[1200]={0};
	double yy[1200]={0};
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(200,200,0));
	CPen *PenOld = pDC->SelectObject(&PenNew);
	pDC->MoveTo(ORIGINX1, ORIGINY1);
	////////////////////////////////三角波///////////////////////////////
	int sample_fre = 2000;
	int pierod_signal = sample_fre/n_filter_signal_freq;
	int pierod_signal_mid = (int)(pierod_signal/2);
	for( i=0;i<=pierod_signal_mid;i++)
	{
		tri[i]=i*n_filter_signal_am*YGAP/pierod_signal_mid;
		tri[i+pierod_signal_mid]=tri[i];
	}
	for( i=0;i< XMAX;i++)
		{
			int j = i%pierod_signal;
			if(j<pierod_signal_mid)
				{
					tri[i]=tri[j];
				}
			else
				{
					tri[i]=tri[pierod_signal-j];
				}
		}
	for( i=0;i<200;i++)
		{
			signal[i]=tri[i]+n_filter_carrier_am*YGAP*cos(2*PI*i*n_filter_carrier_freq/sample_fre);
			pDC->LineTo(ORIGINX1+i*XGAP,(int)(ORIGINY1-signal[i]));
		}
	///高通滤波器核心程序
/*	w1[0]=signal[0];               
	yy[0]=0.0653*w1[0];
	w1[1]=signal[1]-1.199*w1[0]; 
	yy[1]=0.0653*w1[1]-0.1306*w1[0];
	for(i=2;i<=(XMAX-20)*XGAP;i++)
	{
		w1[i]=signal[i]-1.199*w1[i-1]-0.349*w1[i-2];
		yy[i]=0.0653*w1[i]-0.1306*w1[i-1]+0.0653*w1[i-2];
	}
*/
	double c=0.098531*2;
	yy[0]=c*signal[0];               
	yy[1]=c*signal[1]-3*c*signal[0]-0.486441*yy[0];
	yy[2]=c*signal[2]-3*c*signal[1]+3*c*signal[0]-0.486441*yy[1]-0.421787*yy[0];
	for(i=3;i<=(XMAX-20)*XGAP;i++)
	{
		yy[i]=c*signal[i]-3*c*signal[i-1]+3*c*signal[i-2]-c*signal[i-3]-0.486441*yy[i-1]-0.421787*yy[i-2]-0.056297*yy[i-3];
	}
////////////////////////////////////////////////

	pDC->MoveTo(ORIGINX2,ORIGINY2);
	for(i=0;i<200;i++)
	{
		pDC->LineTo(ORIGINX2+i*XGAP,(int)(ORIGINY2-yy[i]));
	} 
	pDC->SelectObject(PenOld);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetTextColor(RGB(0,0,255));
	st1.Format("%d",n_filter_signal_am);
	st2.Format("%d Hz",n_filter_signal_freq);
	st3.Format("%d",n_filter_carrier_am);
	st4.Format("%d Hz",n_filter_carrier_freq);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-9*YGAP,"三角波信号幅度="+st1);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-8*YGAP,"三角波信号频率="+st2);
	pDC->TextOut(ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,"正弦载波幅度="+st3);
	pDC->TextOut(20,ORIGINY1-6*YGAP,"正弦载波频率="+st4);
	pDC->TextOut(20,300,"经滤波器滤波后:");
	pDC->SetTextColor(RGB(0,0,0));
}

