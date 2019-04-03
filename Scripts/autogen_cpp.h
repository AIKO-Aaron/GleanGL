PFNGLGETSTRINGPROC glGetString = nullptr;
PFNGLGETINTEGERVPROC glGetIntegerv = nullptr;
PFNGLGETERRORPROC glGetError = nullptr;
PFNGLCLEARCOLORPROC glClearColor = nullptr;
PFNGLCLEARPROC glClear = nullptr;
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
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

static void initGLean() {
	INIT_FUNC(glGetString);
	INIT_FUNC(glGetIntegerv);
	INIT_FUNC(glGetError);
	INIT_FUNC(glClearColor);
	INIT_FUNC(glClear);
	INIT_FUNC(glGenBuffers);
	INIT_FUNC(glBindBuffer);
	INIT_FUNC(glCreateProgram);
	INIT_FUNC(glCreateShader);
	INIT_FUNC(glShaderSource);
	INIT_FUNC(glCompileShader);
	INIT_FUNC(glGetShaderiv);
	INIT_FUNC(glGetShaderInfoLog);
	INIT_FUNC(glAttachShader);
	INIT_FUNC(glLinkProgram);
	INIT_FUNC(glUseProgram);
	INIT_FUNC(glDeleteShader);
}