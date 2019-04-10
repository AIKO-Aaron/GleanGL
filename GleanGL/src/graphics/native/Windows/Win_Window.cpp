#ifdef _WIN32

#include "../../Window.h"
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

Glean::graphics::Window::Window(const char *title, int width, int height) {
	HINSTANCE currentProgramInstance = GetModuleHandle(0); // Get the current program's instance

	if (!GetClassInfoEx(currentProgramInstance, WINDOWCLASS_NAME, nullptr)) registerWindowClass(currentProgramInstance);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	window = CreateWindow(WINDOWCLASS_NAME, title, WS_OVERLAPPEDWINDOW, (screenWidth - width) / 2, (screenHeight - height) / 2, width, height, nullptr, nullptr, currentProgramInstance, nullptr);
	if (!window) {
		printf("[GLEAN][ERROR] Error creating window!\n");
		return;
	}

	POINT mouseLoc;
	GetCursorPos(&mouseLoc);
	Glean::events::mouseX = mouseLoc.x;
	Glean::events::mouseY = mouseLoc.y;

	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);

	// Done, so call init
	init();
}

Glean::graphics::Window::Window(const char *title, int width, int height, int x, int y) {
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

bool Glean::graphics::Window::fetchEvents() {
	MSG msg;
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE | PM_NOYIELD)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

        if(msg.message == WM_QUIT) return false;

        if(msg.message == WM_KEYDOWN) keysPressed[Glean::events::SCANCODE_TO_KEY[msg.wParam] % IMPLEMENTED_KEYS] = true;
        if(msg.message == WM_KEYUP) keysPressed[Glean::events::SCANCODE_TO_KEY[msg.wParam] % IMPLEMENTED_KEYS] = false;

        Glean::events::Event *e = Glean::events::translateEvent(msg);
        if (e) dispatchEvent(e);
	}

	if (mouseCaptured) { // What a pain
		RECT rect;
		GetWindowRect(window, &rect);
		POINT p;
		p.x = (rect.left + rect.right) / 2;
		p.y = (rect.top + rect.bottom) / 2;
		ScreenToClient(window, &p);
		Glean::events::mouseX = p.x;
		Glean::events::mouseY = p.y;
		SetPhysicalCursorPos((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
	}

	return true;
}

void Glean::graphics::Window::start() { loop(); }

void Glean::graphics::Window::close() { DestroyWindow(window); }

void Glean::graphics::Window::captureMouse() { 
	RECT rect;
	GetWindowRect(window, &rect);
	ClipCursor(&rect);
	ShowCursor(FALSE);
	mouseCaptured = true;
}

void Glean::graphics::Window::uncaptureMouse() { 
	ClipCursor(NULL);
	ShowCursor(TRUE);
	mouseCaptured = false;
}

#endif
