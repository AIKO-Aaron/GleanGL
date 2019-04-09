#ifdef _WIN32

#include "../Universal/Platform.h"
#include <stdio.h>

HMODULE Glean::library::openLibrary(const char* path) {
	HMODULE module = LoadLibrary(path);
	return module;
}

void* Glean::library::getFunctionAddress(HMODULE lib, const char* name) {
	return GetProcAddress(lib, name);
}

void* Glean::library::getGLFunction(const char *name) {
	void* p = wglGetProcAddress(name);
	if ((int) p <= 0x3 || p == (void*) -1) p = Glean::library::getFunctionAddress(Glean::library::openLibrary("opengl32.dll"), name); // Not found with wgl
	return p;
}

__internalContext Glean::graphics::createGLContext(HWND window) {
	PIXELFORMATDESCRIPTOR pixelFormat;
	pixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormat.nVersion = 1;
	pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	pixelFormat.iPixelType = PFD_TYPE_RGBA;
	pixelFormat.cColorBits = 32;
	pixelFormat.cRedBits = 8;
	pixelFormat.cRedShift = 0;
	pixelFormat.cGreenBits = 8;
	pixelFormat.cGreenShift = 0;
	pixelFormat.cBlueBits = 8;
	pixelFormat.cBlueShift = 0;
	pixelFormat.cAlphaBits = 8;
	pixelFormat.cAlphaShift = 0;
	pixelFormat.cAccumBits = 0;
	pixelFormat.cAccumRedBits = 0;
	pixelFormat.cAccumGreenBits = 0;
	pixelFormat.cAccumBlueBits = 0;
	pixelFormat.cAccumAlphaBits = 0;
	pixelFormat.cDepthBits = 24;
	pixelFormat.cStencilBits = 8;
	pixelFormat.cAuxBuffers = 0; // Not supported
	pixelFormat.dwVisibleMask = 0;

	HDC handle = GetDC(window);

	int format = ChoosePixelFormat(handle, &pixelFormat);
	SetPixelFormat(handle, format, &pixelFormat);

	if (!format || !handle) {
		printf("[GLEAN][ERROR] Couldn't create Windows OpenGL Context\n");
	}

	HGLRC glRenderContext = wglCreateContext(handle);
	if (!glRenderContext) {
		printf("[GLEAN][ERROR] Couldn't create Windows OpenGL Context\n");
	}
	wglMakeCurrent(handle, glRenderContext);

	return handle;
}

void Glean::graphics::swapBuffers(HDC context) {
    if (!SwapBuffers(context)) printf("Swap buffers failed...\n");
}

#endif
