#include <windows.h>
#include <tchar.h>
#include "Resource.h"
#include "DSP.h"

TCHAR szTitle[] = "Digital Signal Processing"; // The title bar text

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		SendMessage(hwnd,WM_SETICON,TRUE,(LONG)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MAINFRAME)));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnDraw(hwnd);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COORD_GRID:
			OnCoordGrid(hwnd);
			return 0;
		case ID_COORD_DOT:
			OnCoordDot(hwnd);
			return 0;
		case ID_SIN_INPUTPARA:
			inputPara(hwnd);
			return 0;
		case ID_TRI_DFT:
			DftParaInput(hwnd);
			return 0;
		case ID_DIT_FFT:
			DifFFTInput(hwnd);
			return 0;
		case ID_IIR_LP:
			IIRLPInput(hwnd);
			return 0;
		case ID_IIR_AP:
			IIRAPInput(hwnd);
			return 0;
		case ID_IIR_HP:
			IIRHPInput(hwnd);
			return 0;
		case ID_FILTER_TRI:
			filterTri(hwnd);
			return 0;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int APIENTRY _tWinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR     lpCmdLine,
				int       nCmdShow)
{
	MSG msg;
	WNDCLASS wc;

	wc.style         = CS_VREDRAW|CS_HREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINFRAME);
	wc.lpszClassName = MAKEINTRESOURCE(IDR_MAINFRAME);

	if (FALSE == RegisterClass(&wc)) return FALSE;

	// create the browser
	if (NULL == CreateWindow(
		MAKEINTRESOURCE(IDR_MAINFRAME),
		szTitle,
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL)) return FALSE;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
