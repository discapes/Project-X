#pragma once
#include <d3d9.h>

namespace Window {


	extern HWND hwnd;

	int InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);

	int messageloop(int (*display)(float timeDelta));

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	int handleError(int code, HWND hwnd = NULL);

	int closeWindow(HWND hwnd, int code);
}