#ifdef _WIN32

#include "../Window.h"

#include <Windows.h>

#include <Windows.h>
#include <stdio.h>

#define WINDOWCLASS_NAME "aiko_glean_window"

using namespace Glean::graphics;

static LRESULT CALLBACK WindowProcedure(HWND window, UINT uMessage, WPARAM wParam, LPARAM lParam) {

	if (uMessage == WM_CLOSE) {
		DestroyWindow(window); // Close the window
		return 0;
	}
	else if (uMessage == WM_DESTROY) {
		PostQuitMessage(0); // Actually quit the application when destroyed
		return 0;
	}

	return DefWindowProc(window, uMessage, wParam, lParam);
}

static void registerWindowClass(HINSTANCE currentProgramInstance) {
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // Redraw the window if the size of it is changed
	windowClass.lpfnWndProc = WindowProcedure; // The handler for window events
	windowClass.cbClsExtra = 0; // Extra bytes to alloc for a window
	windowClass.cbWndExtra = 0; // Extra bytes after the window
	windowClass.hInstance = currentProgramInstance;
	windowClass.hIcon = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = WINDOWCLASS_NAME;
	windowClass.hIconSm = nullptr;
	windowClass.hbrBackground = nullptr; // (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClassEx(&windowClass)) {
		printf("[GLEAN][ERROR] Error registering window class\n");
		return;
	}
}

Window::Window(const char *title, int width, int height) {
	HINSTANCE currentProgramInstance = GetModuleHandle(0); // Get the current program's instance

	if (!GetClassInfoEx(currentProgramInstance, WINDOWCLASS_NAME, nullptr)) registerWindowClass(currentProgramInstance);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	window = CreateWindow(WINDOWCLASS_NAME, title, WS_OVERLAPPEDWINDOW, (screenWidth - width) / 2, (screenHeight - height) / 2, width, height, nullptr, nullptr, currentProgramInstance, nullptr);
	if (!window) {
		printf("[GLEAN][ERROR] Error creating window!\n");
		return;
	}

	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);

	// Done, so call init
	init();
}

Window::Window(const char *title, int width, int height, int x, int y) {
	HINSTANCE currentProgramInstance = GetModuleHandle(0); // Get the current program's instance

	if (!GetClassInfoEx(currentProgramInstance, WINDOWCLASS_NAME, nullptr)) registerWindowClass(currentProgramInstance);

	window = CreateWindow(WINDOWCLASS_NAME, title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, currentProgramInstance, nullptr);
	if (!window) {
		printf("[GLEAN][ERROR] Error creating window!\n");
		return;
	}

	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);

	// Done, so call init
	init();
}

bool Window::fetchEvents() {
	MSG msg;
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE | PM_NOYIELD)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		switch (msg.message) {
		case WM_KEYDOWN:
			//msg.wParam --> Virtual key code
			//msg.lParam --> Weird flags
			break;
		case WM_QUIT:
			return false; // Window was closed... So no more events
		default:
			//printf("[GLEAN][WARN] Unhandled Event for Windows window: %.08X\n", msg.message);
			break;
		}
	}

	return true;
}

void Window::start() { loop(); }

#endif