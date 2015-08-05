#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include "Resource.h"
#include "DSP.h"

#define ORIGINX 20
#define ORIGINY 300
#define ORIGINX1 20
#define ORIGINY1 160
#define ORIGINX2 20
#define ORIGINY2 380
#define ORIGINX3 20
#define ORIGINY3 150
#define ORIGINX4 20
#define ORIGINY4 300
#define ORIGINX5 720
#define ORIGINY5 440
#define ORIGINX6 20
#define ORIGINY6 470
#define XMAX 320
#define XMAX_COORD3 160
#define XMAX_COORD4 160
#define XMAX_COORD5 160
#define XMAX_COORD6 160
#define XGAP 4
#define YGAP 20
#define YGAP_C6 10
#define MARKLENGTH 4
#define YP_AMOUT 12
#define YN_AMOUT 15
#define Y_COUNTER 5
#define Y_COUNTER_COORD5 20

extern int m_Period;
extern int m_Amplitude;
extern int m_SampleFreq;
extern int m_dft_point;
extern int m_tri_amplitude;
extern int m_tri_count;
extern int m_tri_pierod;
extern int n_ditfft_level;
extern int n_ditfft_amplitude;
extern int n_ditfft_count;
extern int n_ditfft_pierod;
extern int n_iirhp_carrier_freq;
extern int n_iirhp_carrier_am;
extern int n_iirhp_signal_freq;
extern int n_iirhp_signal_am;
extern int n_iirap_carrier_freq;
extern int n_iirap_carrier_am;
extern int n_iirap_signal_freq;
extern int n_iirap_signal_am;
extern int n_iirlp_carrier_freq;
extern int n_iirlp_carrier_am;
extern int n_iirlp_signal_freq;
extern int n_iirlp_signal_am;
extern int n_filter_carrier_am;
extern int n_filter_carrier_freq;
extern int n_filter_signal_am;
extern int n_filter_signal_freq;
enum CoordMode n_mCoordMode=COORD_DOT;

static void DrawGridCoord(HDC hdc)
{
	TCHAR str[32];
	int XUNIT = 0;
	int YUNIT = 0;
	MoveToEx(hdc,ORIGINX,ORIGINY,NULL);//设置原点

	for(XUNIT = 0;XUNIT < XMAX; XUNIT++)
		{
			if(XUNIT%10)//绘制非整数刻度
			{
				LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY);
				LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH);
				MoveToEx(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,NULL);
			}
			else//绘制整数刻度和纵向网格线
			{
				LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY);
				LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY-YP_AMOUT*YGAP);
				LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY+YN_AMOUT*YGAP);
				//if(XUNIT%2==0)
				{
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,str,_tcslen(str));
				}
				//COUNT+=1;
				MoveToEx(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,NULL);
			}
		}
		LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY);//绘制X轴箭头
		LineTo(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY+5);
		MoveToEx(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,NULL);
		LineTo(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY-5);
		_stprintf(str,_T("X(t/s)"));
		TextOut(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX,ORIGINY,NULL);//绘制Y轴刻度和横向网格线
		for(YUNIT=-YN_AMOUT;YUNIT<=YP_AMOUT;YUNIT++)
		{
			LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);
			LineTo(hdc,ORIGINX+XMAX*XGAP,ORIGINY-YUNIT*YGAP);
			MoveToEx(hdc,ORIGINX,ORIGINY-YUNIT*YGAP,NULL);
		}
		LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);//绘制Y轴箭头
		LineTo(hdc,ORIGINX-5,ORIGINY-YUNIT*YGAP+5);
		LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);
		LineTo(hdc,ORIGINX+5,ORIGINY-YUNIT*YGAP+5);
		_stprintf(str,_T("Y"));
		TextOut(hdc,ORIGINX-18,ORIGINY-YUNIT*YGAP-8,str,_tcslen(str));
		for(YUNIT=-15;YUNIT<15;YUNIT+=5)
		{
			_stprintf(str,_T("%d"),YUNIT);
			TextOut(hdc,ORIGINX-20,ORIGINY-YUNIT*YGAP-10,str,_tcslen(str));
		}//y轴刻度
}

static void DrawDotCoord(HDC hdc)
{
	TCHAR str[32];
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
	MoveToEx(hdc,ORIGINX,ORIGINY,NULL);
	LineTo(hdc,ORIGINX+XMAX*XGAP,ORIGINY);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY);
			LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY-MARKLENGTH*2);
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,str,_tcslen(str));
				}
			MoveToEx(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,NULL);
		}
		LineTo(hdc,ORIGINX+XUNIT*XGAP,ORIGINY);//X轴箭头
		LineTo(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY+5);
		MoveToEx(hdc,ORIGINX+XUNIT*XGAP,ORIGINY,NULL);
		LineTo(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY-5);
		_stprintf(str,_T("X(t/s)"));
		TextOut(hdc,ORIGINX+XUNIT*XGAP-5,ORIGINY+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX,ORIGINY,NULL);//Y轴
		for(YUNIT=-YN_AMOUT;YUNIT<=YP_AMOUT;YUNIT++)
		{
			LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);
			LineTo(hdc,ORIGINX+MARKLENGTH,ORIGINY-YUNIT*YGAP);
			MoveToEx(hdc,ORIGINX,ORIGINY-YUNIT*YGAP,NULL);  
		}
		LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);//Y轴箭头
		LineTo(hdc,ORIGINX-5,ORIGINY-YUNIT*YGAP+5);
		LineTo(hdc,ORIGINX,ORIGINY-YUNIT*YGAP);
		LineTo(hdc,ORIGINX+5,ORIGINY-YUNIT*YGAP+5);
		_stprintf(str,_T("Y"));
		TextOut(hdc,ORIGINX-18,ORIGINY-YUNIT*YGAP-8,str,_tcslen(str));
		for(YUNIT=-15;YUNIT<15;YUNIT+=5)
		{
			_stprintf(str,_T("%d"),YUNIT);
			TextOut(hdc,ORIGINX-20,ORIGINY-YUNIT*YGAP-10,str,_tcslen(str));
		}//y轴刻度

		//SelectObject(hdc,GetStockObject(BLACK_BRUSH));//绘制坐标内点状
		for(X_STAR=ORIGINX;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY-YGAP*YP_AMOUT);Y_STAR<=(ORIGINY+YGAP*YN_AMOUT);Y_STAR+=XGAP)
					{
						SetPixel(hdc,X_STAR,Y_STAR,RGB(0,125,125));
					}
			}

}

static void DrawDotCoord2(HDC hdc)
{
	TCHAR str[32];
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);
		LineTo(hdc,ORIGINX2+XMAX*XGAP,ORIGINY2);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2);
			//LineTo(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2-MARKLENGTH);

			if(XUNIT%10==0)
				{
					LineTo(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2-MARKLENGTH*2);
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2,str,_tcslen(str));
				}
			MoveToEx(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2,NULL);	
			
		}
		LineTo(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2);//X轴箭头
		LineTo(hdc,ORIGINX2+XUNIT*XGAP-5,ORIGINY2+5);
		MoveToEx(hdc,ORIGINX2+XUNIT*XGAP,ORIGINY2,NULL);
		LineTo(hdc,ORIGINX2+XUNIT*XGAP-5,ORIGINY2-5);
		_stprintf(str,_T("X(t/s)"));
		TextOut(hdc,ORIGINX2+XUNIT*XGAP-5,ORIGINY2+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			LineTo(hdc,ORIGINX2,ORIGINY2-YUNIT*YGAP);
			LineTo(hdc,ORIGINX2+MARKLENGTH,ORIGINY2-YUNIT*YGAP);
			MoveToEx(hdc,ORIGINX2,ORIGINY2-YUNIT*YGAP,NULL);  
		}
		LineTo(hdc,ORIGINX2,ORIGINY2-YUNIT*YGAP);//Y轴箭头
		LineTo(hdc,ORIGINX2-5,ORIGINY2-YUNIT*YGAP+5);
		LineTo(hdc,ORIGINX2,ORIGINY2-YUNIT*YGAP);
		LineTo(hdc,ORIGINX2+5,ORIGINY2-YUNIT*YGAP+5);
		_stprintf(str,_T("Y"));
		TextOut(hdc,ORIGINX2-18,ORIGINY2-YUNIT*YGAP-8,str,_tcslen(str));
		for(YUNIT=-4;YUNIT<5;YUNIT++)
		{
			//if(YUNIT%5==0)
				{
					_stprintf(str,_T("%d"),YUNIT);
					TextOut(hdc,ORIGINX2-20,ORIGINY2-YUNIT*YGAP-10,str,_tcslen(str));
				}
		}//y轴刻度

		//SelectObject(hdc,GetStockObject(BLACK_BRUSH));//绘制坐标内点状
		for(X_STAR=ORIGINX2;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY2-YGAP*Y_COUNTER);Y_STAR<=(ORIGINY2+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						SetPixel(hdc,X_STAR,Y_STAR,RGB(0,125,125));
					}
			}

}

static void DrawDotCoord1(HDC hdc)
{
	TCHAR str[32];
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);
		LineTo(hdc,ORIGINX1+XMAX*XGAP,ORIGINY1);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1);
			//LineTo(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1-MARKLENGTH);

			if(XUNIT%10==0)
				{
					LineTo(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1-MARKLENGTH*2);
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1,str,_tcslen(str));
				}
			MoveToEx(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1,NULL);	
			
		}
		LineTo(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1);//X轴箭头
		LineTo(hdc,ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5);
		MoveToEx(hdc,ORIGINX1+XUNIT*XGAP,ORIGINY1,NULL);
		LineTo(hdc,ORIGINX1+XUNIT*XGAP-5,ORIGINY1-5);
		_stprintf(str,_T("X(t/s)"));
		TextOut(hdc,ORIGINX1+XUNIT*XGAP-5,ORIGINY1+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			LineTo(hdc,ORIGINX1,ORIGINY1-YUNIT*YGAP);
			LineTo(hdc,ORIGINX1+MARKLENGTH,ORIGINY1-YUNIT*YGAP);
			MoveToEx(hdc,ORIGINX1,ORIGINY1-YUNIT*YGAP,NULL);  
		}
		LineTo(hdc,ORIGINX1,ORIGINY1-YUNIT*YGAP);//Y轴箭头
		LineTo(hdc,ORIGINX1-5,ORIGINY1-YUNIT*YGAP+5);
		LineTo(hdc,ORIGINX1,ORIGINY1-YUNIT*YGAP);
		LineTo(hdc,ORIGINX1+5,ORIGINY1-YUNIT*YGAP+5);
		_stprintf(str,_T("Y"));
		TextOut(hdc,ORIGINX1-18,ORIGINY1-YUNIT*YGAP-8,str,_tcslen(str));
		for(YUNIT=-4;YUNIT<5;YUNIT++)
		{
			//if(YUNIT%5==0)
				{
					_stprintf(str,_T("%d"),YUNIT);
					TextOut(hdc,ORIGINX1-20,ORIGINY1-YUNIT*YGAP-10,str,_tcslen(str));
				}
		}//y轴刻度

		//SelectObject(hdc,GetStockObject(BLACK_BRUSH));//绘制坐标内点状
		for(X_STAR=ORIGINX1;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY1-YGAP*Y_COUNTER);Y_STAR<=(ORIGINY1+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						SetPixel(hdc,X_STAR,Y_STAR,RGB(0,125,125));
					}
			}

}

static void IIR_DrawCoord(HDC hdc, int originalX, int originalY)
{
	TCHAR str[32];
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		MoveToEx(hdc,originalX,originalY,NULL);
		LineTo(hdc,originalX+XMAX*XGAP,originalY);
		for(XUNIT = 0;XUNIT < XMAX; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,originalX+XUNIT*XGAP,originalY);

			if(XUNIT*5%100==0)
				{
					LineTo(hdc,originalX+XUNIT*XGAP,originalY-MARKLENGTH*2);
					if(n_mCoordMode==FILTER_TRI)
						{
							_stprintf(str,_T("%d"),XUNIT/2);
						}
					else
						{
							_stprintf(str,_T("%d"),XUNIT*XGAP);
						}
					TextOut(hdc,originalX+XUNIT*XGAP,originalY,str,_tcslen(str));
				}
			MoveToEx(hdc,originalX+XUNIT*XGAP,originalY,NULL);
		}
		LineTo(hdc,originalX+XUNIT*XGAP,originalY);//X轴箭头
		LineTo(hdc,originalX+XUNIT*XGAP-5,originalY+5);
		MoveToEx(hdc,originalX+XUNIT*XGAP,originalY,NULL);
		LineTo(hdc,originalX+XUNIT*XGAP-5,originalY-5);
		_stprintf(str,_T("X(t/ms)"));
		TextOut(hdc,originalX+XUNIT*XGAP-5,originalY+5,str,_tcslen(str));

		MoveToEx(hdc,originalX,originalY,NULL);//Y轴
		for(YUNIT=-Y_COUNTER;YUNIT<Y_COUNTER;YUNIT++)
		{
			LineTo(hdc,originalX,originalY-YUNIT*YGAP);
			LineTo(hdc,originalX+MARKLENGTH,originalY-YUNIT*YGAP);
			MoveToEx(hdc,originalX,originalY-YUNIT*YGAP,NULL);
		}
		LineTo(hdc,originalX,originalY-YUNIT*YGAP);//Y轴箭头
		LineTo(hdc,originalX-5,originalY-YUNIT*YGAP+5);
		LineTo(hdc,originalX,originalY-YUNIT*YGAP);
		LineTo(hdc,originalX+5,originalY-YUNIT*YGAP+5);
		_stprintf(str,_T("Y"));
		TextOut(hdc,originalX-18,originalY-YUNIT*YGAP-8,str,_tcslen(str));
		for(YUNIT=-4;YUNIT<5;YUNIT++)
		{
			//if(YUNIT%5==0)
				{
					_stprintf(str,_T("%d"),YUNIT);
					TextOut(hdc,originalX-20,originalY-YUNIT*YGAP-10,str,_tcslen(str));
				}
		}//y轴刻度

		//SelectObject(hdc,GetStockObject(BLACK_BRUSH));//绘制坐标内点状
		for(X_STAR=originalX;X_STAR<=(XMAX+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(originalY-YGAP*Y_COUNTER);Y_STAR<=(originalY+YGAP*Y_COUNTER);Y_STAR+=XGAP)
					{
						SetPixel(hdc,X_STAR,Y_STAR,RGB(0,125,125));
					}
			}

}

static void DrawSinsignal(HDC hdc)
{
	TCHAR str[32];
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(0,255,0));
	SelectObject(hdc,hPen);
	SetTextAlign(hdc,TA_LEFT);
	SetTextColor(hdc,RGB(0,0,255));
	_stprintf(str,_T("输入SIN正弦函数:"));
	TextOut(hdc,ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-8*YGAP,str,_tcslen(str));
	_stprintf(str,_T("周期=%d"),m_Period);
	TextOut(hdc,ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("幅度=%d"),m_Amplitude);
	TextOut(hdc,ORIGINX1+(XMAX-20)*XGAP,ORIGINY1-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("抽样频率=%d"),m_SampleFreq);
	TextOut(hdc,ORIGINX2+(XMAX-20)*XGAP,ORIGINY2-6*YGAP,str,_tcslen(str));

	MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);//画连续SIN信号
	{
	double i;
	for(i = 0;i< 200; i+=0.01)//XMAX
		{
			double j = sin(PI/(m_Period/2)*i)*m_Amplitude;
			SetPixel(hdc,(int)(ORIGINX1+i*XGAP),(int)(j*YGAP+ORIGINY1),RGB(255,0,0));
		}
	}
	MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);//画抽样后的信号

	{
	double m;
	for(m = 0;m< 200;m+=m_SampleFreq)//XMAX
		{
			double n = sin(PI/(m_Period/2)*m)*m_Amplitude;
			MoveToEx(hdc,(int)(ORIGINX2+m*XGAP),(int)(ORIGINY2),NULL);
			LineTo(hdc,(int)(ORIGINX2+m*XGAP),(int)(ORIGINY2+n*YGAP));
			Ellipse(hdc,(int)(ORIGINX2+m*XGAP-2),(int)(ORIGINY2+n*YGAP+2),(int)(ORIGINX2+m*XGAP+2),(int)(ORIGINY2+n*YGAP-2));
			
		}
	}
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
}

static void DrawTriByPierodCount(HDC hdc,int count,int pierod,int amplitude)
{
	TCHAR str[32];
	int signal_xstart = ORIGINX3 ;
	int signal_ystart = ORIGINY3;
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(0,0,255));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX3,ORIGINY3,NULL);
	{
	int m;
	for(m =1;m<=2*count;m++)
		{
			if(signal_xstart<=XMAX_COORD3*XGAP)
			{
				signal_xstart=signal_xstart+(pierod*XGAP/2);
				if(m%2)
				{
					signal_ystart = ORIGINY3 - amplitude*YGAP;
					LineTo(hdc,signal_xstart,signal_ystart);
					MoveToEx(hdc,signal_xstart,signal_ystart,NULL);
				}
				else
				{
					signal_ystart = ORIGINY3;
					LineTo(hdc,signal_xstart,signal_ystart);
					MoveToEx(hdc,signal_xstart,signal_ystart,NULL);	
				}
			}
		}
	}
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	SetTextAlign(hdc,TA_LEFT);
	SetTextColor(hdc,RGB(55,55,55));
	_stprintf(str,_T("三角波周期=%d"),pierod);
	TextOut(hdc,ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("幅度=%d"),amplitude);
	TextOut(hdc,ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("周期个数=%d"),count);
	TextOut(hdc,ORIGINX3+(XMAX_COORD3-30)*XGAP,ORIGINY3-5*YGAP,str,_tcslen(str));
	SetTextColor(hdc,RGB(0,0,0));
}

static void DrawDotCoord3(HDC hdc)
{
	TCHAR str[32];
	//int X_STAR;
	//int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
	MoveToEx(hdc,ORIGINX3,ORIGINY3,NULL);
	LineTo(hdc,ORIGINX3+XMAX_COORD3*XGAP,ORIGINY3);
	for(XUNIT = 0;XUNIT < XMAX_COORD3; XUNIT++)//绘制X轴和X轴刻度
	{
		LineTo(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3);
		LineTo(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3-MARKLENGTH);

		if(XUNIT%10==0)
			{
				LineTo(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3-MARKLENGTH*2);
				MoveToEx(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3,NULL);
				LineTo(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3+MARKLENGTH*2);
				_stprintf(str,_T("%d"),XUNIT);
				TextOut(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3,str,_tcslen(str));
			}
		MoveToEx(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3,NULL);
		
	}
	LineTo(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3);//X轴箭头
	LineTo(hdc,ORIGINX3+XUNIT*XGAP-5,ORIGINY3+5);
	MoveToEx(hdc,ORIGINX3+XUNIT*XGAP,ORIGINY3,NULL);
	LineTo(hdc,ORIGINX3+XUNIT*XGAP-5,ORIGINY3-5);	
	_stprintf(str,_T("T(s)"));
	TextOut(hdc,ORIGINX3+XUNIT*XGAP-5,ORIGINY3+5,str,_tcslen(str));

	MoveToEx(hdc,ORIGINX3,ORIGINY3,NULL);//Y轴
	for(YUNIT=0;YUNIT<Y_COUNTER;YUNIT++)
	{
		LineTo(hdc,ORIGINX3,ORIGINY3-YUNIT*YGAP);
		LineTo(hdc,ORIGINX3+MARKLENGTH,ORIGINY3-YUNIT*YGAP);
		MoveToEx(hdc,ORIGINX3,ORIGINY3-YUNIT*YGAP,NULL);  
	}
	LineTo(hdc,ORIGINX3,ORIGINY3-YUNIT*YGAP);//Y轴箭头
	LineTo(hdc,ORIGINX3-5,ORIGINY3-YUNIT*YGAP+5);
	LineTo(hdc,ORIGINX3,ORIGINY3-YUNIT*YGAP);
	LineTo(hdc,ORIGINX3+5,ORIGINY3-YUNIT*YGAP+5);
	_stprintf(str,_T("幅度"));
	TextOut(hdc,ORIGINX3-18,ORIGINY3-(YUNIT+1)*YGAP,str,_tcslen(str));
	for(YUNIT=0;YUNIT<5;YUNIT++)
	{	
			{
				_stprintf(str,_T("%d"),YUNIT);
				TextOut(hdc,ORIGINX3-20,ORIGINY3-YUNIT*YGAP-10,str,_tcslen(str));
			}
	}//y轴刻度

}

static void DrawTriSignal(HDC hdc,int point,int pierod,int amplitude)
{//pierod=160;
	TCHAR str[32];
	int signal_xstart;
	int signal_ystart;
	int middle_value = 0;
	int dsitance_value = 0;
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(0,255,0));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX4,ORIGINY4,NULL);
	for(signal_xstart =0;signal_xstart<point;signal_xstart+=1)
		{
			if(signal_xstart<pierod)
			{
				middle_value = pierod/2;
				dsitance_value = abs(signal_xstart-middle_value);
				signal_ystart = amplitude*YGAP*(middle_value-dsitance_value)/middle_value;
				LineTo(hdc,ORIGINX4+signal_xstart*XGAP,ORIGINY4-signal_ystart);
				Ellipse(hdc,ORIGINX4+signal_xstart*XGAP-2,ORIGINY4-signal_ystart+2,ORIGINX4+signal_xstart*XGAP+2,ORIGINY4-signal_ystart-2);
				MoveToEx(hdc,ORIGINX4+(signal_xstart+1)*XGAP,ORIGINY4,NULL);	
			}
			else
			{
				signal_ystart = 0;
				Ellipse(hdc,ORIGINX4+signal_xstart*XGAP-2,ORIGINY4-signal_ystart+2,ORIGINX4+signal_xstart*XGAP+2,ORIGINY4-signal_ystart-2);
			}
		}
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	SetTextAlign(hdc,TA_LEFT);
	SetTextColor(hdc,RGB(0,0,255));
	_stprintf(str,_T("幅频特性"));
	TextOut(hdc,ORIGINX4+(XMAX_COORD4-30)*XGAP,ORIGINY4-4*YGAP,str,_tcslen(str));
	_stprintf(str,_T("DFT取点数=%d"),point);
	TextOut(hdc,1000,ORIGINY4-4*YGAP,str,_tcslen(str));
	SetTextColor(hdc,RGB(0,0,0));
}

static void DrawDotCoord4(HDC hdc)
{
	TCHAR str[32];
	//int X_STAR;
	//int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
	MoveToEx(hdc,ORIGINX4,ORIGINY4,NULL);
	LineTo(hdc,ORIGINX4+XMAX_COORD4*XGAP,ORIGINY4);
	for(XUNIT = 0;XUNIT < XMAX_COORD4; XUNIT++)//绘制X轴和X轴刻度
	{
		LineTo(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4);
		LineTo(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4-MARKLENGTH);

		if(XUNIT%10==0)
			{
				LineTo(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4-MARKLENGTH*2);
				MoveToEx(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4,NULL);
				LineTo(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4+MARKLENGTH*2);
				_stprintf(str,_T("%d"),XUNIT);
				TextOut(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4,str,_tcslen(str));
			}
		MoveToEx(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4,NULL);
	}
	LineTo(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4);//X轴箭头
	LineTo(hdc,ORIGINX4+XUNIT*XGAP-5,ORIGINY4+5);
	MoveToEx(hdc,ORIGINX4+XUNIT*XGAP,ORIGINY4,NULL);
	LineTo(hdc,ORIGINX4+XUNIT*XGAP-5,ORIGINY4-5);
	_stprintf(str,_T("N"));
	TextOut(hdc,ORIGINX4+XUNIT*XGAP-5,ORIGINY4+5,str,_tcslen(str));

	MoveToEx(hdc,ORIGINX4,ORIGINY4,NULL);//Y轴
	for(YUNIT=0;YUNIT<Y_COUNTER;YUNIT++)
	{
		LineTo(hdc,ORIGINX4,ORIGINY4-YUNIT*YGAP);
		LineTo(hdc,ORIGINX4+MARKLENGTH,ORIGINY4-YUNIT*YGAP);
		MoveToEx(hdc,ORIGINX4,ORIGINY4-YUNIT*YGAP,NULL);  
	}
	LineTo(hdc,ORIGINX4,ORIGINY4-YUNIT*YGAP);//Y轴箭头
	LineTo(hdc,ORIGINX4-5,ORIGINY4-YUNIT*YGAP+5);
	LineTo(hdc,ORIGINX4,ORIGINY4-YUNIT*YGAP);
	LineTo(hdc,ORIGINX4+5,ORIGINY4-YUNIT*YGAP+5);
	_stprintf(str,_T("幅度"));
	TextOut(hdc,ORIGINX4-18,ORIGINY4-(YUNIT+1)*YGAP,str,_tcslen(str));
	for(YUNIT=0;YUNIT<5;YUNIT++)
	{	
			{
				_stprintf(str,_T("%d"),YUNIT);
				TextOut(hdc,ORIGINX4-20,ORIGINY4-YUNIT*YGAP-10,str,_tcslen(str));
			}
	}//y轴刻度	
}

static void DrawDftAM(HDC hdc)
{
	HPEN hPen;
	int i,N,M,K;
	double array_sample[320]={0};
	double array_Re[320]={0};
	double array_Im[320]={0};
	double array_AmValue[320]={0};
	double phase_value[320]={0};

	double Basic_value = 2*PI/m_dft_point;
	double middle_value = 0;
	double dsitance_value = 0;
	for(i = 0;i<m_dft_point;i++)
		{
			if(i < m_tri_pierod)
				{
					middle_value =(double)m_tri_pierod/2;
					dsitance_value = fabs(i-middle_value);
					array_sample[i] = m_tri_amplitude*(middle_value-dsitance_value)/middle_value;
				}
			else{
					array_sample[i] = 0;
				}
		}
	for(N = 0;N < m_dft_point;N++)
		{
			double Re_value = 0;
			double Im_value = 0;
			for(M = 0 ;M < m_dft_point; M++ )
				{
					Re_value+=(float)(array_sample[M]*cos(Basic_value*M*N));
					Im_value+=(float)(-(array_sample[M])*sin(Basic_value*M*N));
				}
			array_AmValue[N] = pow(Re_value*Re_value+Im_value*Im_value,0.5);
			phase_value[N] = atan(-Im_value/Re_value)*180/PI;
		}
	hPen = CreatePen(PS_SOLID,1,RGB(255,0,0));
	SelectObject(hdc,hPen);
	for(K = 0;K < m_dft_point;K++)
		{
			MoveToEx(hdc,ORIGINX5+K*XGAP,ORIGINY5,NULL);
			LineTo(hdc,ORIGINX5+K*XGAP,(int)(ORIGINY5-array_AmValue[K]*YGAP)); 
			Ellipse(hdc,ORIGINX5+K*XGAP-2,(int)(ORIGINY5-array_AmValue[K]*YGAP-2),
						ORIGINX5+K*XGAP+2,(int)(ORIGINY5-array_AmValue[K]*YGAP+2));
		}
	for(M = 0;M < m_dft_point;M++)
		{
			MoveToEx(hdc,ORIGINX6+M*XGAP,ORIGINY6,NULL); 
			LineTo(hdc,ORIGINX6+M*XGAP,(int)(ORIGINY6-phase_value[M])); 
			Ellipse(hdc,ORIGINX6+M*XGAP-2,(int)(ORIGINY6-phase_value[M]-2),
						ORIGINX6+M*XGAP+2,(int)(ORIGINY6-phase_value[M]+2));
		}
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
}

static void DrawDotCoord5(HDC hdc)
{
	TCHAR str[32];
	int XUNIT = 0;
	int YUNIT = 0;
		MoveToEx(hdc,ORIGINX5,ORIGINY5,NULL);
		for(XUNIT = 0;XUNIT < XMAX_COORD5; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5);
			LineTo(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5-MARKLENGTH);
			if(XUNIT%10==0)
				{
					LineTo(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5-MARKLENGTH*2);
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5,str,_tcslen(str));
				}
			MoveToEx(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5,NULL);
		}
		LineTo(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5);//X轴箭头
		LineTo(hdc,ORIGINX5+XUNIT*XGAP-5,ORIGINY5+5);
		MoveToEx(hdc,ORIGINX5+XUNIT*XGAP,ORIGINY5,NULL);
		LineTo(hdc,ORIGINX5+XUNIT*XGAP-5,ORIGINY5-5);
		_stprintf(str,_T("N"));
		TextOut(hdc,ORIGINX5+XUNIT*XGAP-5,ORIGINY5+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX5,ORIGINY5,NULL);//Y轴
		for(YUNIT=0;YUNIT<Y_COUNTER_COORD5;YUNIT++)
		{
			LineTo(hdc,ORIGINX5,ORIGINY5-YUNIT*YGAP);
			LineTo(hdc,ORIGINX5+MARKLENGTH,ORIGINY5-YUNIT*YGAP);
			MoveToEx(hdc,ORIGINX5,ORIGINY5-YUNIT*YGAP,NULL);
		}
		LineTo(hdc,ORIGINX5,ORIGINY5-YUNIT*YGAP);//Y轴箭头
		LineTo(hdc,ORIGINX5-5,ORIGINY5-YUNIT*YGAP+5);
		LineTo(hdc,ORIGINX5,ORIGINY5-YUNIT*YGAP);
		LineTo(hdc,ORIGINX5+5,ORIGINY5-YUNIT*YGAP+5);
		_stprintf(str,_T("|X(n)|"));
		TextOut(hdc,ORIGINX5-18,ORIGINY5-(YUNIT+1)*YGAP,str,_tcslen(str));
		for(YUNIT=0;YUNIT<Y_COUNTER_COORD5;YUNIT++)
		{
			_stprintf(str,_T("%d"),YUNIT);
			TextOut(hdc,ORIGINX5-20,ORIGINY5-YUNIT*YGAP-10,str,_tcslen(str));
		}//y轴刻度

		SetTextAlign(hdc,TA_LEFT);
		SetTextColor(hdc,RGB(55,55,55));
		_stprintf(str,_T("%d"),m_dft_point);
		_stprintf(str,_T("幅度特性"));
		TextOut(hdc,ORIGINX5+(XMAX_COORD5-20)*XGAP,ORIGINY5-Y_COUNTER_COORD5*YGAP,str,_tcslen(str));
		SetTextColor(hdc,RGB(0,0,0));

}

static void DrawDotCoord6(HDC hdc)
{
	TCHAR str[32];
	int X_STAR;
	int Y_STAR;
	int XUNIT = 0;
	int YUNIT = 0;
		MoveToEx(hdc,ORIGINX6,ORIGINY6,NULL);
		LineTo(hdc,ORIGINX6+XMAX_COORD6*XGAP,ORIGINY6);
		for(XUNIT = 0;XUNIT < XMAX_COORD6; XUNIT++)//绘制X轴和X轴刻度
		{
			LineTo(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6);
			LineTo(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6-MARKLENGTH);
				
			if(XUNIT%10==0)
				{
					LineTo(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6-MARKLENGTH*2);
					_stprintf(str,_T("%d"),XUNIT);
					TextOut(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6,str,_tcslen(str));
				}
			MoveToEx(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6,NULL);
		}
		LineTo(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6);//X轴箭头
		LineTo(hdc,ORIGINX6+XUNIT*XGAP-5,ORIGINY6+5);
		MoveToEx(hdc,ORIGINX6+XUNIT*XGAP,ORIGINY6,NULL);
		LineTo(hdc,ORIGINX6+XUNIT*XGAP-5,ORIGINY6-5);	
		_stprintf(str,_T("N"));
		TextOut(hdc,ORIGINX6+XUNIT*XGAP-5,ORIGINY6+5,str,_tcslen(str));

		MoveToEx(hdc,ORIGINX6,ORIGINY6,NULL);//Y轴
		for(YUNIT=-9;YUNIT<=9;YUNIT++)
		{
			LineTo(hdc,ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);
			LineTo(hdc,ORIGINX6+MARKLENGTH,ORIGINY6-YUNIT*YGAP_C6);
			MoveToEx(hdc,ORIGINX6,ORIGINY6-YUNIT*10,NULL);
		}
		LineTo(hdc,ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);//Y轴箭头
		LineTo(hdc,ORIGINX6-5,ORIGINY6-YUNIT*YGAP_C6+5);
		LineTo(hdc,ORIGINX6,ORIGINY6-YUNIT*YGAP_C6);
		LineTo(hdc,ORIGINX6+5,ORIGINY6-YUNIT*YGAP_C6+5);
		_stprintf(str,_T("arg[X[n]]"));
		TextOut(hdc,ORIGINX6-18,ORIGINY6-(YUNIT+2)*YGAP_C6,str,_tcslen(str));
		for(YUNIT=-9;YUNIT<=9;YUNIT++)
		{
			if(YUNIT%2)
				{
					_stprintf(str,_T("%d"),YUNIT*10);
					TextOut(hdc,ORIGINX6-20,ORIGINY6-YUNIT*10,str,_tcslen(str));
				}
		}//y轴刻度
		for(X_STAR=ORIGINX6;X_STAR<=(160+4)*XGAP;X_STAR+=XGAP)
			{
				for(Y_STAR=(ORIGINY6-YGAP_C6*9);Y_STAR<=(ORIGINY6+YGAP_C6*9);Y_STAR+=XGAP)
					{
						SetPixel(hdc,X_STAR,Y_STAR,RGB(0,125,125));
					}
			}
		SetTextAlign(hdc,TA_LEFT);
		SetTextColor(hdc,RGB(55,55,55));
		_stprintf(str,_T("相位特性"));
		TextOut(hdc,ORIGINX6+(XMAX_COORD6-20)*XGAP,ORIGINY6-5*YGAP,str,_tcslen(str));
		SetTextColor(hdc,RGB(0,0,0));

}

static void IIRLP_main(HDC hdc)
{
	TCHAR str[32];
	int i;
	double signal[1200]={0},signal_pass[1200]={0},
		ww1[1200]={0},wy1[1200]={0},
		ww2[1200]={0},wy2[1200]={0},
		ww3[1200]={0},wy3[1200]={0};
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(255,0,0));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);
	for(i=0;i<(XMAX-20)*XGAP;i++)
		{
			signal[i]=n_iirlp_signal_am*sin(2*PI*n_iirlp_signal_freq*i*0.001)+n_iirlp_carrier_am*sin(2*PI*n_iirlp_carrier_freq*i*0.001);
			LineTo(hdc,ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
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
		
		MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);
		for (i=0;i<=(XMAX-20)*XGAP;i++)
		{
			LineTo(hdc,ORIGINX2+i,ORIGINY2-(int)(signal_pass[i]*YGAP));
		}

		DeleteObject(hPen);
		SelectObject(hdc,GetStockObject(BLACK_PEN));
		SetTextAlign(hdc,TA_LEFT);
		SetTextColor(hdc,RGB(0,0,255));
		_stprintf(str,_T("信号幅度=%d"),n_iirlp_signal_am);
		TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,str,_tcslen(str));
		_stprintf(str,_T("信号频率=%d Hz"),n_iirlp_signal_freq);
		TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,str,_tcslen(str));
		_stprintf(str,_T("载波幅度=%d"),n_iirlp_carrier_am);
		TextOut(hdc,ORIGINX1,ORIGINY1-7*YGAP,str,_tcslen(str));
		_stprintf(str,_T("载波频率=%d Hz"),n_iirlp_carrier_freq);
		TextOut(hdc,ORIGINX1,ORIGINY1-6*YGAP,str,_tcslen(str));
		_stprintf(str,_T("低通滤波后:"));
		TextOut(hdc,ORIGINX2,ORIGINY2-6*YGAP,str,_tcslen(str));
		SetTextColor(hdc,RGB(0,0,0));
}

static void IIRAP_main(HDC hdc)
{
	TCHAR str[32];
	int i;
	double signal[1200]={0},signal_pass[1200]={0};
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(255,0,0));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);
	for(i=0;i<(XMAX-20)*XGAP;i++)
		{
			signal[i]=n_iirap_signal_am*sin(2*PI*n_iirap_signal_freq*i*0.001)+n_iirap_carrier_am*sin(2*PI*n_iirap_carrier_freq*i*0.001);
			LineTo(hdc,ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
		}
	MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);
	for (i=0;i<=(XMAX-20)*XGAP;i++)
		{
			signal_pass[i]=signal[i];
			LineTo(hdc,ORIGINX2+i,ORIGINY2-(int)(signal_pass[i]*YGAP));
		}

		DeleteObject(hPen);
		SelectObject(hdc,GetStockObject(BLACK_PEN));
		SetTextAlign(hdc,TA_LEFT);
		SetTextColor(hdc,RGB(0,0,255));
		_stprintf(str,_T("信号幅度=%d"),n_iirap_signal_am);
		TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,str,_tcslen(str));
		_stprintf(str,_T("信号频率=%d Hz"),n_iirap_signal_freq);
		TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,str,_tcslen(str));
		_stprintf(str,_T("载波幅度=%d"),n_iirap_carrier_am);
		TextOut(hdc,ORIGINX1,ORIGINY1-7*YGAP,str,_tcslen(str));
		_stprintf(str,_T("载波频率=%d Hz"),n_iirap_carrier_freq);
		TextOut(hdc,ORIGINX1,ORIGINY1-6*YGAP,str,_tcslen(str));
		_stprintf(str,_T("全通滤波后:"));
		TextOut(hdc,ORIGINX2,ORIGINY2-6*YGAP,str,_tcslen(str));
		SetTextColor(hdc,RGB(0,0,0));
}

static void IIRHP_main(HDC hdc)
{
	TCHAR str[32];
	int i;
	double signal[1200]={0};
	double w1[1200]={0};
	double yy[1200]={0};
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX1,ORIGINY1,NULL);
	for(i=0;i<(200)*XGAP;i++)
		{
			signal[i]=n_iirhp_signal_am*sin(2*PI*n_iirhp_signal_freq*i*0.001)+n_iirhp_carrier_am*sin(2*PI*n_iirhp_carrier_freq*i*0.001);
			LineTo(hdc,ORIGINX1+i,(int)(ORIGINY1-signal[i]*YGAP));
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

	MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);
	for(i=1;i<=(200)*XGAP;i++)//XMAX
	{
		LineTo(hdc,ORIGINX2+i,(int)(ORIGINY2-yy[i]*YGAP));
	}
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	SetTextAlign(hdc,TA_LEFT);
	SetTextColor(hdc,RGB(0,0,255));
	_stprintf(str,_T("信号幅度=%d"),n_iirhp_signal_am);
	TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("信号频率=%d Hz"),n_iirhp_signal_freq);
	TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("载波幅度=%d"),n_iirhp_carrier_am);
	TextOut(hdc,ORIGINX1,ORIGINY1-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("载波频率=%d Hz"),n_iirhp_carrier_freq);
	TextOut(hdc,ORIGINX1,ORIGINY1-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("高通滤波后:"));
	TextOut(hdc,ORIGINX2,ORIGINY2-6*YGAP,str,_tcslen(str));
	SetTextColor(hdc,RGB(0,0,0));
}

static void Filter_Tri_main(HDC hdc)
{
	TCHAR str[32];
	int i;
	double signal[1200]={0};
	double tri[1200]={0};
	double carrier[1200]={0};
	double w1[1200]={0};
	double yy[1200]={0};
	HPEN hPen;
	hPen = CreatePen(PS_SOLID,1,RGB(200,200,0));
	SelectObject(hdc,hPen);
	MoveToEx(hdc,ORIGINX1, ORIGINY1,NULL);
	////////////////////////////////三角波///////////////////////////////
	{
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
			LineTo(hdc,ORIGINX1+i*XGAP,(int)(ORIGINY1-signal[i]));
		}
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
	{
	double c=0.098531*2;
	yy[0]=c*signal[0];               
	yy[1]=c*signal[1]-3*c*signal[0]-0.486441*yy[0];
	yy[2]=c*signal[2]-3*c*signal[1]+3*c*signal[0]-0.486441*yy[1]-0.421787*yy[0];
	for(i=3;i<=(XMAX-20)*XGAP;i++)
	{
		yy[i]=c*signal[i]-3*c*signal[i-1]+3*c*signal[i-2]-c*signal[i-3]-0.486441*yy[i-1]-0.421787*yy[i-2]-0.056297*yy[i-3];
	}
	}
////////////////////////////////////////////////

	MoveToEx(hdc,ORIGINX2,ORIGINY2,NULL);
	for(i=0;i<200;i++)
	{
		LineTo(hdc,ORIGINX2+i*XGAP,(int)(ORIGINY2-yy[i]));
	} 
	DeleteObject(hPen);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	SetTextAlign(hdc,TA_LEFT);
	SetTextColor(hdc,RGB(0,0,255));
	_stprintf(str,_T("三角波信号幅度=%d"),n_filter_signal_am);
	TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("三角波信号频率=%d Hz"),n_filter_signal_freq);
	TextOut(hdc,ORIGINX1+(XMAX_COORD3-30)*XGAP,ORIGINY1-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("正弦载波幅度=%d"),n_filter_carrier_am);
	TextOut(hdc,ORIGINX1,ORIGINY1-7*YGAP,str,_tcslen(str));
	_stprintf(str,_T("正弦载波频率=%d Hz"),n_filter_carrier_freq);
	TextOut(hdc,ORIGINX1,ORIGINY1-6*YGAP,str,_tcslen(str));
	_stprintf(str,_T("经滤波器滤波后:"));
	TextOut(hdc,ORIGINX2,ORIGINY2-5*YGAP,str,_tcslen(str));
	SetTextColor(hdc,RGB(0,0,0));
}

void OnCoordGrid(HWND hwnd)
{
	n_mCoordMode=COORD_GRID;
	InvalidateRgn(hwnd,NULL,TRUE);
}

void OnCoordDot(HWND hwnd)
{
	n_mCoordMode=COORD_DOT;
	InvalidateRgn(hwnd,NULL,TRUE);
}

void OnDraw(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC         hdc;
	hdc = BeginPaint(hwnd, &ps);
	switch(n_mCoordMode)
	{
	case COORD_GRID://绘制网格坐标
		//DrawDotCoord(hdc);
		//MoveToEx(hdc,ORIGINX,ORIGINY,NULL);//设置原点
		DrawGridCoord(hdc);
		break;
	case COORD_DOT://绘制点状坐标
		DrawDotCoord(hdc);
		break;
	case SINSIGNAL_INPUT:
		DrawDotCoord1(hdc);
		DrawDotCoord2(hdc);
		DrawSinsignal(hdc);
		break;
	case DFT_TRI:
		DrawDotCoord3(hdc);
		DrawTriByPierodCount(hdc,m_tri_count,m_tri_pierod,m_tri_amplitude);	
		DrawDotCoord4(hdc);
		DrawTriSignal(hdc,m_dft_point,m_tri_pierod,m_tri_amplitude);
		DrawDotCoord5(hdc);
		DrawDotCoord6(hdc);
		DrawDftAM(hdc);
		break;
	case DIT_FFT:
		{
		int point = (int)pow(2,n_ditfft_level);
		DrawDotCoord3(hdc);
		DrawTriByPierodCount(hdc,n_ditfft_count,n_ditfft_pierod,n_ditfft_amplitude);
		DrawDotCoord4(hdc);
		DrawTriSignal(hdc,point,n_ditfft_pierod,n_ditfft_amplitude);
		DrawDotCoord5(hdc);
		DrawDotCoord6(hdc);
		m_tri_count=n_ditfft_count;
		m_tri_pierod=n_ditfft_pierod;
		m_tri_amplitude=n_ditfft_amplitude;
		m_dft_point=point;
		DrawDftAM(hdc);
		break;
		}
	case IIR_LP:
		IIR_DrawCoord(hdc,ORIGINX1, ORIGINY1);
		IIR_DrawCoord(hdc,ORIGINX2, ORIGINY2);
		IIRLP_main(hdc);
		break;
	case IIR_AP:
		IIR_DrawCoord(hdc,ORIGINX1, ORIGINY1);
		IIR_DrawCoord(hdc,ORIGINX2, ORIGINY2);
		IIRAP_main(hdc);
		break;
	case IIR_HP:
		IIR_DrawCoord(hdc,ORIGINX1, ORIGINY1);
		IIR_DrawCoord(hdc,ORIGINX2, ORIGINY2);
		IIRHP_main(hdc);
		break;
	case FILTER_TRI:
		IIR_DrawCoord(hdc,ORIGINX1, ORIGINY1);
		IIR_DrawCoord(hdc,ORIGINX2, ORIGINY2);
		Filter_Tri_main(hdc);
		break;
	}
	EndPaint(hwnd, &ps);
}