#include "GleanGL.h"

PFNGLGETSTRINGPROC glGetString = nullptr;
PFNGLGETINTEGERVPROC glGetIntegerv = nullptr;
PFNGLGETERRORPROC glGetError = nullptr;
PFNGLCLEARCOLORPROC glClearColor = nullptr;
PFNGLCLEARPROC glClear = nullptr;
PFNGLCREATEBUFFERSPROC glCreateBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;