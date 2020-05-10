#include <Windows.h>
#include "Window.h"
#include "Direct3DX9.h"
#include "Settings.h"
#include <ctime>
#include "imgui/imgui_impl_win32.h"
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#include "Menu.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	{
		int result = Window::InitializeWindow(hInstance, nShowCmd, Settings::Window::width, Settings::Window::height, true);
		if (result != 0) {
			return Window::handleError(result);
		}
	}
	{
		int result = DirectX::setupScene();
		if (result != 0) {
			return Window::handleError(result);
		}
	}
	Window::messageloop(DirectX::renderScene);
	DirectX::cleanUp;
	return 0;
}

namespace Window {

	LPCSTR WndClassName = "Project X Class";
	HWND hwnd = NULL;

	int messageloop(int (*display)(float timeDelta)) {
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		static float lastTime = (double)clock() / (double)CLOCKS_PER_SEC;

		while (true) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);

			} else {

				//Set the time
				float currTime = (double)clock() / (double)CLOCKS_PER_SEC;

				//Set the speed until the next frame
				float timeDelta = (currTime - lastTime) * 0.001f;

				display(timeDelta);    //Display the goods

				//Last time equal to current time
				lastTime = currTime;

			}

		}
		return (int)msg.wParam;
	}

	int InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
	{
		WNDCLASSEX wc;    //Create a new extended windows class
		wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
		wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
		wc.lpfnWndProc = WndProc;    //Default windows procedure function
		wc.cbClsExtra = NULL;    //Extra bytes after our wc structure
		wc.cbWndExtra = NULL;    //Extra bytes after our windows instance
		wc.hInstance = hInstance;    //Instance to current application
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);    //Title bar Icon
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);    //Window bg color
		wc.lpszMenuName = NULL;    //Name of the menu attached to our window
		wc.lpszClassName = WndClassName;    //Name of our windows class
		wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar

		if (!RegisterClassEx(&wc))
			return 1;

		if (Settings::Window::isFullScreen) {
			hwnd = CreateWindowEx(    //Create our Extended Window
				NULL,    //Extended style
				WndClassName,    //Name of our windows class
				"Project X Title",    //Name in the title bar of our window
				WS_EX_TOPMOST | WS_POPUP,    //style of our window
				0, 0,    //Top left corner of window
				width,    //Width of our window
				height,    //Height of our window
				NULL,    //Handle to parent window
				NULL,    //Handle to a Menu
				hInstance,    //Specifies instance of current program
				NULL    //used for an MDI client window
			);
		} else {
			hwnd = CreateWindowEx(    //Create our Extended Window
				NULL,    //Extended style
				WndClassName,    //Name of our windows class
				"Project X Title",    //Name in the title bar of our window
				WS_OVERLAPPEDWINDOW,    //style of our window
				CW_USEDEFAULT, CW_USEDEFAULT,    //Top left corner of window
				width,    //Width of our window
				height,    //Height of our window
				NULL,    //Handle to parent window
				NULL,    //Handle to a Menu
				hInstance,    //Specifies instance of current program
				NULL    //used for an MDI client window
			);
		}


		if (!hwnd)
			return 2;

		ShowWindow(hwnd, ShowWnd);
		UpdateWindow(hwnd);

		int result = DirectX::initializeD3D(hwnd);
		if (result != 0) {
			handleError(result, hwnd);
			return result;
		}
		return 0;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_KEYDOWN:
			if (wParam == Settings::Keys::exitKey) {
				closeWindow(hwnd, 0);
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		if (Menu::isOpen) {
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
			// so clicks dont register to CSGO
			if ((!GetAsyncKeyState(VK_XBUTTON2)) && (msg == WM_LBUTTONDOWN
				|| msg == WM_LBUTTONUP
				|| msg == WM_LBUTTONDBLCLK

				|| msg == WM_MBUTTONDOWN
				|| msg == WM_MBUTTONUP
				|| msg == WM_MBUTTONDBLCLK

				|| msg == WM_RBUTTONDOWN
				|| msg == WM_RBUTTONUP
				|| msg == WM_RBUTTONDBLCLK

				|| msg == WM_XBUTTONDOWN
				|| msg == WM_XBUTTONUP
				|| msg == WM_XBUTTONDBLCLK
				|| ((msg == WM_MOUSEMOVE) && (wParam != 0)))
				) return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	int handleError(int code, HWND hwnd) {
		switch (code) {
		case 1:
			MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
			break;
		case 2:
			MessageBox(NULL, "Error creating window", "Error", MB_OK | MB_ICONERROR);
			break;
		case 3:
			MessageBox(NULL, "Error initializing D3D9", "Error", MB_OK | MB_ICONERROR);
			break;
		case 4:
			MessageBox(NULL, "CreateDevice() - FAILED", "Error", MB_OK | MB_ICONERROR);
			break;
		}

		if (hwnd) {
			closeWindow(hwnd, code);
			return code;
		}
		PostQuitMessage(code);
		return code;
	}

	int closeWindow(HWND hwnd, int code) {
		PostQuitMessage(code);
		DestroyWindow(hwnd);
		return code;
	}

}