#pragma once

#include "glcorearb.h"
#include "glext.h"
#include "../Platform.h"

#include <stdio.h>

// Function definitions
PFNGLGETSTRINGPROC glGetString;
PFNGLGETINTEGERVPROC glGetIntegerv;
PFNGLGETERRORPROC glGetError;

PFNGLCLEARCOLORPROC glClearColor;
PFNGLCLEARPROC glClear;

PFNGLCREATEBUFFERSPROC glCreateBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;

#define INIT_FUNC(funcname) funcname = (typeof(funcname)) Glean::library::getGLFunction(#funcname)

__internalContext Glean::graphics::initGL(__internalWindow window) {
	__internalContext c = Glean::graphics::createGLContext(window);

    INIT_FUNC(glGetString);
    INIT_FUNC(glGetIntegerv);
    INIT_FUNC(glGetError);

    INIT_FUNC(glCreateBuffers);
    INIT_FUNC(glBindBuffer);
    
	INIT_FUNC(glClearColor);
	INIT_FUNC(glClear);
    
	const char *vers = (const char*) glGetString(GL_VERSION);
	printf("[GLEAN][INFO] Loaded OpenGL Version: %s\n", vers);

	return c;
}
