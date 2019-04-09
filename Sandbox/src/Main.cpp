#include <iostream>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "math/GleanMath.h"
#include "graphics/Camera.h"

using namespace Glean::graphics;

static Glean::graphics::Window *window;
static Glean::graphics::Shader *shader;
static GLuint vboID, vioID;
static float angle = 0;
static Camera c;

void handleEvent(Glean::events::Event *e) {
    if(e->type == Glean::events::KEYDOWN) {
        Glean::events::KeyEvent *kEvent = e->asKeyEvent();
        if(kEvent->isPlatformCtrlDown() && kEvent->key == Glean::events::kQ) exit(0);
        //printf("[SANDBOX][DEBUG] Pressed Key: %c\n", Glean::events::getCharFromKey(kEvent->key));
        // if(kEvent->key == Glean::events::kW) c.move(Glean::math::createVector(0, 0, 0.01));
	}
	else if (e->type == Glean::events::MOUSEMOTION) {
		Glean::events::MouseMotionEvent *mEvent = e->asMouseMotionEvent();
        c.rotate(mEvent);
		//printf("[SANDBOX][DEBUG] Mouse position on screen: %d|%d\n", mEvent->xPos, mEvent->yPos);
	}
}

void render(Glean::graphics::Renderer *renderer) {
    renderer->clearColor(0, 0, 0, 1);

    angle += 0.01f;
    
    float dx = 0;
    float dy = 0;
    float dz = 0;
    
    if(window->isKeyPressed(Glean::events::kA)) dx -= 0.1f;
    if(window->isKeyPressed(Glean::events::kD)) dx += 0.1f;
    if(window->isKeyPressed(Glean::events::kS)) dz -= 0.1f;
    if(window->isKeyPressed(Glean::events::kW)) dz += 0.1f;
    if(window->isKeyPressed(Glean::events::kSHIFT)) dy -= 0.1f;
    if(window->isKeyPressed(Glean::events::kSPACE)) dy += 0.1f;

    Glean::math::Vector<4> moveVec = Glean::math::createVector(dx, 0, dz, 0);
    Glean::math::Vector<4> m = c.getTransformation().inverse() * moveVec;
    m[1] = -dy;
    c.move(m);
    
    shader->bind();
    shader->uniform("angle", angle);
    shader->uniform("camera", c.getTransformation());
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioID);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, 0);
    
    GLuint err;
    if((err = glGetError()) != GL_NO_ERROR) {
        printf("Error happened: %d\n", err);
        exit(0);
    }
    
    renderer->swapBuffers();
}

int main(int argc, char **args) {    
	window = new Window("Hello World", 960, 540);
    window->captureMouse();
    window->addEventHandler(handleEvent);
    window->addRenderFunction(render);
    
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 * 6, new float[12 * 6] {
        -0.5f, -0.5f, 1, 1, 0, 1,
         0.5f, -0.5f, 1, 1, 1, 1,
         0.5f,  0.5f, 1, 1, 1, 1,
        -0.5f,  0.5f, 1, 1, 1, 1,
        
        1, 0, 1, 0, 0, 1,
        2, 0, 1, 0, 0, 1,
        2, 0, 2, 0, 0, 1,
        1, 0, 2, 0, 0, 1,
        
        -1, 2, -1, 1, 0, 1,
         1, 2, -1, 1, 0, 1,
         1, 2,  1, 1, 0, 1,
        -1, 2,  1, 1, 0, 1,
    }, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vioID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char) * 18, new unsigned char[18] { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8 }, GL_STATIC_DRAW);
    
    shader = Glean::graphics::loadShaderRecursive("assets/shader.vert", "assets/shader.frag");
    
	window->start();

#ifdef _WIN32
	std::cin.get();
#endif
    return 0;
}
