#pragma once

#include "glcorearb.h"
#include "glext.h"
#include "../Platform.h"

#include <stdio.h>

#ifdef __APPLE__
#  define INIT_FUNC(funcname) funcname = (typeof(funcname)) Glean::library::getGLFunction(#funcname)
#else
#  define INIT_FUNC(funcname) funcname = (decltype(funcname)) Glean::library::getGLFunction(#funcname)
#endif

extern PFNGLGETSTRINGPROC glGetString;
extern PFNGLGETINTEGERVPROC glGetIntegerv;
extern PFNGLGETERRORPROC glGetError;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLCLEARPROC glClear;
extern PFNGLCREATEBUFFERSPROC glCreateBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;

static __internalContext Glean::graphics::initGL(__internalWindow window) {
	__internalContext c = Glean::graphics::createGLContext(window);

    INIT_FUNC(glGetString);
    INIT_FUNC(glGetIntegerv);
    INIT_FUNC(glGetError);

    INIT_FUNC(glCreateBuffers);
    INIT_FUNC(glBindBuffer);
    
	INIT_FUNC(glClearColor);
	INIT_FUNC(glClear);

	INIT_FUNC(glCreateProgram);
	INIT_FUNC(glCreateShader);
	INIT_FUNC(glShaderSource);
	INIT_FUNC(glGetShaderInfoLog);
	INIT_FUNC(glCompileShader);
	INIT_FUNC(glGetShaderiv);
	INIT_FUNC(glAttachShader);
	INIT_FUNC(glLinkProgram);
	INIT_FUNC(glUseProgram);
	INIT_FUNC(glDeleteShader);
    
	printf("%p\n", glGetError);

	const char *vers = (const char*) glGetString(GL_VERSION);
	printf("[GLEAN][INFO] Loaded OpenGL Version: %s\n", vers);

	return c;
}