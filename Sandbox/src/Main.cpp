#include <iostream>

#include "graphics/Window.h"
#include "graphics/Shader.h"

using namespace Glean::graphics;

static Glean::graphics::Shader *shader;
static GLuint vboID, vioID;

void handleEvent(Glean::events::Event *e) {
    if(e->type == Glean::events::KEYDOWN) {
        Glean::events::KeyEvent *kEvent = e->asKeyEvent();
        if(kEvent->isPlatformCtrlDown() && kEvent->key == Glean::events::kQ) exit(0);
        //printf("[SANDBOX][DEBUG] Pressed Key: %c\n", Glean::events::getCharFromKey(kEvent->key));
	}
	else if (e->type == Glean::events::MOUSEMOTION) {
		Glean::events::MouseMotionEvent *mEvent = e->asMouseMotionEvent();
		//printf("[SANDBOX][DEBUG] Mouse position on screen: %d|%d\n", mEvent->xPos, mEvent->yPos);
	}
}

void render(Glean::graphics::Renderer *renderer) {
    renderer->clearColor(0, 0, 0, 1);

    shader->bind();
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    
    GLuint err;
    if((err = glGetError()) != GL_NO_ERROR) printf("Error happened...: %d\n", err);
    
    renderer->swapBuffers();
}

int main(int argc, char **args) {    
	Window *window = new Window("Hello World", 960, 540);
    window->addEventHandler(handleEvent);
    window->addRenderFunction(render);
    
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, new float[4 * 6] {
        -0.5f, -0.5f, 0, 1, 1, 1,
         0.5f, -0.5f, 1, 1, 1, 1,
         0.5f,  0.5f, -1, 1, 1, 1,
        -0.5f,  0.5f, -1, 1, 1, 1
    }, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vioID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char) * 6, new unsigned char[6] { 0, 1, 2, 2, 3, 0 }, GL_STATIC_DRAW);
    
    shader = Glean::graphics::loadShaderRecursive("assets/shader.vert", "assets/shader.frag");

	window->start();

	std::cin.get();
}
