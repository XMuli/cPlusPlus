#include "stdafx.h"
#include "math.h"
#include <Windows.h>

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//函数命名
DWORD WINAPI ThreadProcOne(LPVOID lpParameter);
DWORD WINAPI ThreadProcTwo(LPVOID lpParameter);
DWORD WINAPI ThreadProcThree(LPVOID lpParameter);
DWORD WINAPI ThreadProcFour(LPVOID lpParameter);
DWORD WINAPI ThreadProcFive(LPVOID lpParameter);


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	// TODO: Place code here.
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("WndClassName");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&wc))
	{
		//call error
		return -1;
	}
	HWND hWnd = CreateWindow("WndClassName", "yuanyi", WS_OVERLAPPEDWINDOW, 100, 100, 1000, 640, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		//call error
		return -1;
	}
	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);
	MSG uMsg;
	while (GetMessage(&uMsg, NULL, 0, 0))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}

	return uMsg.wParam;
}


LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rt = { 0 };
		GetClientRect(hWnd, &rt);

		MoveToEx(hdc, rt.left, (rt.top + rt.bottom) / 2, NULL);
		LineTo(hdc, rt.right, (rt.top + rt.bottom) / 2);

		MoveToEx(hdc, (rt.left + rt.right) / 2, rt.top, NULL);
		LineTo(hdc, (rt.left + rt.right) / 2, rt.bottom);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		DWORD lpParameter[5] = { 0 };

		//同时创建5个线程
		CloseHandle(CreateThread(NULL, 0, ThreadProcOne, (LPVOID)hWnd, 0, &lpParameter[0]));
		CloseHandle(CreateThread(NULL, 0, ThreadProcTwo, (LPVOID)hWnd, 0, &lpParameter[1]));
		CloseHandle(CreateThread(NULL, 0, ThreadProcThree, (LPVOID)hWnd, 0, &lpParameter[2]));
		CloseHandle(CreateThread(NULL, 0, ThreadProcFour, (LPVOID)hWnd, 0, &lpParameter[3]));
		CloseHandle(CreateThread(NULL, 0, ThreadProcFive, (LPVOID)hWnd, 0, &lpParameter[4]));
	}
	break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

//画横线
DWORD WINAPI ThreadProcOne(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;
	HDC hdc;
	hdc = GetDC(hWnd);
	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);

	int nX1 = rt.left + 80;
	int nY1 = (rt.top + rt.bottom) / 4;
	int nX2 = (rt.left + rt.right) / 2 - 80;
	int nY2 = nY1;
	int nWind = nX2 - nX1;
	for (int k = 0; k < 16; k++)
	{
		int j = 5;
		for (int t = 0; t <= nWind; t++)
		{
			SetPixel(hdc, nX1 + t, nY1, RGB(124, 252, 0));
			Sleep(0.9);
		}

		nX1 += 2 * j;
		nY1 += 2 + j;
	}

	ReleaseDC(hWnd, hdc);

	return 0;
}


//画竖线
DWORD WINAPI ThreadProcTwo(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;
	HDC hdc;
	hdc = GetDC(hWnd);
	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);
	int nX1 = (rt.left + rt.right) * 3 / 4;
	int nY1 = rt.top + 80;
	int nX2 = nX1;
	int nY2 = (rt.top + rt.bottom) / 2 - 80;
	int nWide = nY2 - nY1;
	for (int k = 0; k < 16; k++)
	{
		int j = 5;

		for (int t = 0; t <= nWide; t++)
		{
			SetPixel(hdc, nX1, nY1 + t, RGB(255, 140, 0));
			Sleep(0.9);
		}

		nX1 += j;
		nY1 += j;

	}



	ReleaseDC(hWnd, hdc);

	return 0;
}


//画矩形
DWORD WINAPI ThreadProcThree(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;
	HDC hdc;
	hdc = GetDC(hWnd);
	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);
	int nX_L = rt.left + 80;
	int nX_R = (rt.left + rt.right) / 2 - 80;
	int nY_T = (rt.top + rt.bottom) / 2 + 80;
	int nY_B = rt.bottom - 80;

	for (int k = 0; k < 16; k++)
	{
		int j = 5;
		int t = 0;
		for (int t = 0; t <= (nX_R - nX_L); t++)
		{
			SetPixel(hdc, nX_L + t, nY_T, RGB(238, 112, 214));
			Sleep(0.9);
		}

		for (t = 0; t <= (nY_B - nY_T); t++)
		{
			SetPixel(hdc, nX_R, nY_T + t, RGB(255, 192, 203));
			Sleep(0.9);
		}

		for (t = 0; t <= (nX_R - nX_L); t++)
		{
			SetPixel(hdc, nX_R - t, nY_B, RGB(255, 0, 255));
			Sleep(0.9);
		}

		for (t = 0; t <= (nY_B - nY_T); t++)
		{
			SetPixel(hdc, nX_L, nY_B - t, RGB(75, 0, 130));
			Sleep(0.9);
		}
		nX_L += j;
		nY_T += j;
		nX_R += j;
		nY_B += j;

	}

	ReleaseDC(hWnd, hdc);

	return 0;
}


//画等边三角形
DWORD WINAPI ThreadProcFour(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;
	HDC hdc;
	hdc = GetDC(hWnd);
	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);
	int nWideFree = 120;
	double nX1 = (rt.left + rt.right) / 2 + nWideFree;
	double nX2 = rt.right - nWideFree;
	double nWide = nX2 - nX1;
	double nY_B = rt.bottom - 40;
	double nY_T = nY_B - (sqrt(3)) / 2 * nWide;
	for (int k = 0; k < 16; k++)
	{
		int j = 5;
		int t = 0;
		for (double t = 0; t <= (nWide / 2); t++)
		{
			SetPixel(hdc, (int)(nX1 + t), (int)(nY_B - (sqrt(3))*t), RGB(65, 105, 225));    //sqrt(3)   -->double   精度
			Sleep(0.9);
		}

		for (t = 0; t <= (nWide / 2); t++)
		{
			SetPixel(hdc, (int)((nX1 + nX2) / 2 + t), (int)(nY_T + (sqrt(3))*t), RGB(0, 191, 255));
			Sleep(0.9);
		}

		for (t = 0; t <= nWide; t++)
		{
			SetPixel(hdc, (int)(nX2 - t), (int)nY_B, RGB(0, 206, 209));
			Sleep(0.9);
		}
		int T = 0;

		nX1 += j; nY_B += j;
		T = (nX1 + nX2) / 2;
		t += j; nY_T += j;
		nX2 += j; nY_B += j;

	}

	ReleaseDC(hWnd, hdc);

	return 0;
}



//画圆
DWORD WINAPI ThreadProcFive(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;
	HDC hdc;
	hdc = GetDC(hWnd);
	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);

	int nR = 200;
	int nX = (rt.left + rt.right) / 2;
	int nY = (rt.top + rt.bottom) / 2;
	int nX_L = nX - nR;
	int nX_R = nX + nR;
	int nY_T = nY - nR;
	int nY_B = nY + nR;

	for (int k = 0; k < 16; k++)
	{
		int j = 5;
		int t = 0;
		for (int t = 0; t <= nR; t++)
		{

			SetPixel(hdc, nX - t, nY - sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			SetPixel(hdc, nX + t, nY + sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			SetPixel(hdc, nX + t, nY - sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			SetPixel(hdc, nX - t, nY + sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			Sleep(0.9);
		}



		for (t = 0; t <= nR; t++)
		{
			SetPixel(hdc, nX_L + t, nY_T + sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			SetPixel(hdc, nX_R - t, nY_B - sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			Sleep(0.9);
		}

		for (t = 0; t <= nR; t++)
		{

			SetPixel(hdc, nX_L + t, nY_B - sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			SetPixel(hdc, nX_R - t, nY_T + sqrt((pow(nR, 2) - pow(t, 2))), RGB(255, 0, 0));
			Sleep(0.9);
		}

		nX += j;
		nY += j;
		nX_L += j;
		nY_T += j;
		nX_R += j;
		nY_B += j;

	}



	ReleaseDC(hWnd, hdc);

	return 0;
}