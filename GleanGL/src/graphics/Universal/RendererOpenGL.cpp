#ifndef GLEAN_USE_VULKAN

#include "OpenGL/GleanGL.h"
#include "../Renderer.h"

using namespace Glean::graphics;

Renderer::Renderer(__internalWindow window) : window(window) {
	context = Glean::graphics::initGL(window);
    
    GLuint vboID;
    glCreateBuffers(1, &vboID);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void Renderer::clearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Renderer::swapBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    Glean::graphics::swapBuffers(context);
}

#endif
