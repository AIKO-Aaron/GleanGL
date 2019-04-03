#include "Shader.h"

using namespace Glean::graphics;

Shader::Shader(const char *vertSrc, const char *fragSrc) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("OpenGL error: %d\n", err);
	}
	GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertID, 1, &vertSrc, NULL);
	glShaderSource(fragID, 1, &fragSrc, NULL);

	glCompileShader(vertID);
	glCompileShader(fragID);

	GLint errCode;
	glGetShaderiv(vertID, GL_COMPILE_STATUS, &errCode);
	if (errCode != GL_TRUE) {
		glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &errCode);
		char *errBuf = (char*) malloc(errCode + 1);
		glGetShaderInfoLog(vertID, errCode, &errCode, errBuf);
		printf("[GLEAN][ERROR] Couldn't compile vertex shader: \n%s\n", errBuf);
		return;
	}
	glGetShaderiv(fragID, GL_COMPILE_STATUS, &errCode);
	if (errCode != GL_TRUE) {
		glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &errCode);
		char *errBuf = (char*)malloc(errCode + 1);
		glGetShaderInfoLog(fragID, errCode, &errCode, errBuf);
		printf("[GLEAN][ERROR] Couldn't compile fragment shader: \n%s\n", errBuf);
		return;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertID);
	glAttachShader(shaderID, fragID);
	glLinkProgram(shaderID);
	glDeleteShader(vertID);
	glDeleteShader(fragID);
}

Shader* Glean::graphics::loadShaderRecursive(const char *vertPath, const char *fragPath, int depth) {
    return new Shader(Glean::util::readWithProcessing(vertPath, depth).data, Glean::util::readWithProcessing(fragPath, depth).data);
}
