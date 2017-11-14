#include "stdafx.h"

LPCWSTR className = L"MyCustomControl";
LPCWSTR helloWorld = L"Hello World, I'm a Win32 custom control";

DWORD IDC_CONTROL = 8;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) 
{
	switch (ul_reason_for_call) 
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				TextOut(
					hdc,
					10, 10,
					helloWorld,
					wcslen(helloWorld));

				EndPaint(hWnd, &ps);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

extern "C" __declspec(dllexport) ATOM __stdcall Initialize() 
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}

extern "C" __declspec(dllexport) HWND __stdcall CreateControl(HWND parent) 
{
	return CreateWindowExW(
		0,
		className,
		L"",
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		parent,
		(HMENU)IDC_CONTROL,
		NULL,
		0);
}