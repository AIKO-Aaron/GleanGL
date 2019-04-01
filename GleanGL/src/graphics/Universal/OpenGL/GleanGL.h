#pragma once

#include "glcorearb.h"
#include "glext.h"
#include "../Platform.h"

#include <stdio.h>

// Function definitions
PFNGLGETSTRINGPROC glGetString;
PFNGLGETINTEGERVPROC glGetIntegerv;
PFNGLCLEARCOLORPROC glClearColor;
PFNGLCLEARPROC glClear;

#define INIT_FUNC(funcname, decl) funcname = (decl) Glean::library::getGLFunction(#funcname)

static __internalContext Glean::graphics::initGL(__internalWindow window) {
	__internalContext c = Glean::graphics::createGLContext(window);

	glGetString = (PFNGLGETSTRINGPROC)Glean::library::getGLFunction("glGetString");
	glGetIntegerv = (PFNGLGETINTEGERVPROC)Glean::library::getGLFunction("glGetIntegerv");

	INIT_FUNC(glClearColor, PFNGLCLEARCOLORPROC);
	INIT_FUNC(glClear, PFNGLCLEARPROC);

	const char *vers = (const char*) glGetString(GL_VERSION);
	printf("[GLEAN][INFO] Loaded OpenGL Version: %s\n", vers);

	return c;
}