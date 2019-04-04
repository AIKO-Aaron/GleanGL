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
PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM2FPROC glUniform2f = nullptr;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;
PFNGLUNIFORM4FPROC glUniform4f = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM2IPROC glUniform2i = nullptr;
PFNGLUNIFORM3IPROC glUniform3i = nullptr;
PFNGLUNIFORM4IPROC glUniform4i = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLENABLEPROC glEnable = nullptr;

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
	INIT_FUNC(glDrawElements);
	INIT_FUNC(glBufferData);
	INIT_FUNC(glEnableVertexAttribArray);
	INIT_FUNC(glVertexAttribPointer);
	INIT_FUNC(glGenVertexArrays);
	INIT_FUNC(glBindVertexArray);
	INIT_FUNC(glDrawArrays);
	INIT_FUNC(glUniform1f);
	INIT_FUNC(glUniform2f);
	INIT_FUNC(glUniform3f);
	INIT_FUNC(glUniform4f);
	INIT_FUNC(glUniform1i);
	INIT_FUNC(glUniform2i);
	INIT_FUNC(glUniform3i);
	INIT_FUNC(glUniform4i);
	INIT_FUNC(glUniform4fv);
	INIT_FUNC(glUniformMatrix4fv);
	INIT_FUNC(glGetUniformLocation);
	INIT_FUNC(glEnable);
}