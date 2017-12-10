// DllHook1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windowsx.h>

#define EXPORT  __declspec(dllexport) //khi bên dịch chương trình sẽ export ra tệp tin .DLL và .Lib

HHOOK hHook = NULL;
HINSTANCE hinstLib;
bool isHook = true;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_LBUTTONDOWN)
		{
			if (isHook){
				return -1;
			}
		}

		if (wParam == WM_RBUTTONDOWN && GetAsyncKeyState(VK_CONTROL) < 0)
		{
			isHook = !isHook;
		}
		
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

EXPORT void _doInstallHook(HWND hWnd)
{
	if (hHook != NULL) return;

	hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseHookProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Hook đã được cài đặt", L"Thành công", 0);
	else MessageBox(hWnd, L"Hook chưa được cài đặt", L"Thất bại", 0);
}

EXPORT void _doRemoveHook(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Hook đã được gỡ bỏ", L"Thông báo", MB_OK);
}
