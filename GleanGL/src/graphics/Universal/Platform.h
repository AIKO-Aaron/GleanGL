#pragma once

// #define GLEAN_USE_VULKAN // If enabled we should use vulkan

#ifdef __APPLE__

#elif defined(_WIN32)

#include <Windows.h>
typedef HWND __internalWindow;
typedef HMODULE __internalLibrary;
typedef HDC __internalContext;

#include "../Windows/Win_Events.h"

#else

#endif

namespace Glean {
	namespace library {

		extern __internalLibrary openLibrary(const char *path);
		extern void* getFunctionAddress(__internalLibrary lib, const char *name);
		extern void* getGLFunction(const char *name);

	}

	namespace graphics {

		extern __internalContext initGL(__internalWindow window);
		extern __internalContext createGLContext(__internalWindow window);

	}
}