#include <windows.h>
#include <tchar.h>
#include "Resource.h"
#include "DSP.h"

#define MinMaxInt(a,b,c,d,e,f) \
do{ \
if(b<c||b>d){ \
MessageBox(a,_T("请填入一个在"#c"和"#d"之间的整数。"),NULL,MB_OK|MB_ICONEXCLAMATION); \
f=FALSE; \
}else{ \
e=b; \
}}while(0)

int m_Period = 80;
int m_SampleFreq = 1;
int m_Amplitude = 5;

int m_dft_point = 128;
int m_tri_amplitude = 4;
int m_tri_count = 3;
int m_tri_pierod = 10;

int n_ditfft_level = 7;
int n_ditfft_amplitude = 4;
int n_ditfft_count = 3;
int n_ditfft_pierod = 10;
	
int n_iirhp_carrier_freq = 200;
int n_iirhp_carrier_am = 1;
int n_iirhp_signal_freq = 10;
int n_iirhp_signal_am = 1;

int n_iirap_carrier_freq = 200;
int n_iirap_carrier_am = 1;
int n_iirap_signal_freq =10;
int n_iirap_signal_am = 1;

int n_iirlp_carrier_freq = 200;
int n_iirlp_carrier_am = 1;
int n_iirlp_signal_freq = 10;
int n_iirlp_signal_am = 1;

int n_filter_carrier_freq = 50;
int n_filter_carrier_am = 2;
int n_filter_signal_freq = 500;
int n_filter_signal_am = 2;

extern enum CoordMode n_mCoordMode;

INT_PTR CALLBACK inputParaProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_PERIOD,m_Period,TRUE);
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_AMPLITUDE,m_Amplitude,TRUE);
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_SAMPFREQ,m_SampleFreq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_PERIOD,NULL,TRUE),
				4,320,m_Period,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_AMPLITUDE,NULL,TRUE),
				1,5,m_Amplitude,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_SAMPFREQ,NULL,TRUE),
				1,159,m_SampleFreq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=SINSIGNAL_INPUT;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}

INT_PTR CALLBACK DftParaProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_DFT_POINT,m_dft_point,TRUE);
		SetDlgItemInt(hwndDlg,IDC_TRI_AMPLITUDE,m_tri_amplitude,TRUE);
		SetDlgItemInt(hwndDlg,IDC_TRI_PIEROD,m_tri_pierod,TRUE);
		SetDlgItemInt(hwndDlg,IDC_TRI_COUNT,m_tri_count,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_DFT_POINT,NULL,TRUE),
				1,160,m_dft_point,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_TRI_AMPLITUDE,NULL,TRUE),
				1,5,m_tri_amplitude,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_TRI_PIEROD,NULL,TRUE),
				1,160,m_tri_pierod,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_TRI_COUNT,NULL,TRUE),
				1,5,m_tri_count,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=DFT_TRI;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		}
	}
	return FALSE;
}

INT_PTR CALLBACK DifFFTProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_DITFFT_POINT,n_ditfft_level,TRUE);
		SetDlgItemInt(hwndDlg,IDC_DITFFT_AMPLITUDE,n_ditfft_amplitude,TRUE);
		SetDlgItemInt(hwndDlg,IDC_DITFFT_PIEROD,n_ditfft_pierod,TRUE);
		SetDlgItemInt(hwndDlg,IDC_DITFFT_COUNT,n_ditfft_count,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_DITFFT_POINT,NULL,TRUE),
				1,7,n_ditfft_level,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_DITFFT_AMPLITUDE,NULL,TRUE),
				1,5,n_ditfft_amplitude,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_DITFFT_PIEROD,NULL,TRUE),
				1,160,n_ditfft_pierod,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_DITFFT_COUNT,NULL,TRUE),
				1,5,n_ditfft_count,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=DIT_FFT;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		}
	}
	return FALSE;
}

INT_PTR CALLBACK IIRLPProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_IIRLP_SIGNAL_AM,n_iirlp_signal_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRLP_SIGNAL_FREQ,n_iirlp_signal_freq,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRLP_CARRIER_AM,n_iirlp_carrier_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRLP_CARRIER_FREQ,n_iirlp_carrier_freq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRLP_SIGNAL_AM,NULL,TRUE),
				0,5,n_iirlp_signal_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRLP_SIGNAL_FREQ,NULL,TRUE),
				1,499,n_iirlp_signal_freq,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRLP_CARRIER_AM,NULL,TRUE),
				0,5,n_iirlp_carrier_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRLP_CARRIER_FREQ,NULL,TRUE),
				1,499,n_iirlp_carrier_freq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=IIR_LP;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}

INT_PTR CALLBACK IIRAPProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_IIRAP_SIGNAL_AM,n_iirap_signal_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRAP_SIGNAL_FREQ,n_iirap_signal_freq,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRAP_CARRIER_AM,n_iirap_carrier_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRAP_CARRIER_FREQ,n_iirap_carrier_freq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRAP_SIGNAL_AM,NULL,TRUE),
				0,5,n_iirap_signal_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRAP_SIGNAL_FREQ,NULL,TRUE),
				1,499,n_iirap_signal_freq,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRAP_CARRIER_AM,NULL,TRUE),
				0,5,n_iirap_carrier_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRAP_CARRIER_FREQ,NULL,TRUE),
				1,499,n_iirap_carrier_freq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=IIR_AP;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}

INT_PTR CALLBACK IIRHPProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_IIRHP_SIGNAL_AM,n_iirhp_signal_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRHP_SIGNAL_FREQ,n_iirhp_signal_freq,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRHP_CARRIER_AM,n_iirhp_carrier_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_IIRHP_CARRIER_FREQ,n_iirhp_carrier_freq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRHP_SIGNAL_AM,NULL,TRUE),
				0,5,n_iirhp_signal_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRHP_SIGNAL_FREQ,NULL,TRUE),
				1,499,n_iirhp_signal_freq,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRHP_CARRIER_AM,NULL,TRUE),
				0,5,n_iirhp_carrier_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_IIRHP_CARRIER_FREQ,NULL,TRUE),
				1,499,n_iirhp_carrier_freq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=IIR_HP;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}

INT_PTR CALLBACK filterTriProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_FILTER_SIGNAL_AM,n_filter_signal_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_FILTER_SIGNAL_FREQ,n_filter_signal_freq,TRUE);
		SetDlgItemInt(hwndDlg,IDC_FILTER_CARRIER_AM,n_filter_carrier_am,TRUE);
		SetDlgItemInt(hwndDlg,IDC_FILTER_CARRIER_FREQ,n_filter_carrier_freq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_FILTER_SIGNAL_AM,NULL,TRUE),
				0,5,n_filter_signal_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_FILTER_SIGNAL_FREQ,NULL,TRUE),
				1,500,n_filter_signal_freq,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_FILTER_CARRIER_AM,NULL,TRUE),
				0,5,n_filter_carrier_am,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_FILTER_CARRIER_FREQ,NULL,TRUE),
				0,1000,n_filter_carrier_freq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=FILTER_TRI;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}

void inputPara(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,inputParaProc);
}

void DftParaInput(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,DftParaProc);
}

void DifFFTInput(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG3),hwnd,DifFFTProc);
}

void IIRLPInput(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG4),hwnd,IIRLPProc);
}

void IIRAPInput(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG5),hwnd,IIRAPProc);
}

void IIRHPInput(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG6),hwnd,IIRHPProc);
}

void filterTri(HWND hwnd)
{
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG7),hwnd,filterTriProc);
}