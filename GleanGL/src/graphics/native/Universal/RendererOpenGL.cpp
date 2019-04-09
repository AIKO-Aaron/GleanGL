#include "OpenGL/GleanGL.h"
#include "../../Renderer.h"

using namespace Glean::graphics;

Glean::graphics::Renderer::Renderer(__internalWindow window) : window(window) {
	context = Glean::graphics::initGL(window);
    
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    
    shader = loadShaderRecursive("assets/shader.vert", "assets/shader.frag");
}

void Glean::graphics::Renderer::clearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Glean::graphics::Renderer::swapBuffers() {
    Glean::graphics::swapBuffers(context);
}

void Glean::graphics::Renderer::render() {
    shader->bind();
    for(Light *l : lights) l->getLightSource();
    for(Mesh *m : objects) m->render();
    
}
