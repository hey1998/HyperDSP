#ifndef DSP_H
#define DSP_H

#define PI 3.1415926

typedef struct tagComplex
{
	 float Re;//复数实部
	 float Im;//复数虚部
}Complex;

enum CoordMode
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
};

void OnDraw(HWND);
void OnCoordGrid(HWND);
void OnCoordDot(HWND);
void inputPara(HWND);
void DftParaInput(HWND);
void DifFFTInput(HWND);
void IIRLPInput(HWND);
void IIRAPInput(HWND);
void IIRHPInput(HWND);
void filterTri(HWND);

#endif