#include <iostream>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/objects/Mesh.h"
#include "graphics/objects/Sphere.h"
#include "math/GleanMath.h"
#include "graphics/Camera.h"
#include "graphics/native/Universal/OpenCL/GleanCL.h"

using namespace Glean::graphics;

static Glean::graphics::Window *window;
static Glean::graphics::Shader *shader;
static float angle = 0;
static Camera c;
static Glean::graphics::Mesh *mesh;
static float currentTime = 0;

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
    shader->uniform("time", currentTime += 0.01f);
    
    mesh->render();
    
    GLuint err;
    if((err = glGetError()) != GL_NO_ERROR) {
        printf("[SANDBODX][ERROR] GL-Error has occured: %d\n", err);
        exit(0);
    }
    
    renderer->swapBuffers();
}

int main(int argc, char **args) {    
	window = new Window("Hello World", 960, 540);
    window->captureMouse();
    window->addEventHandler(handleEvent);
    window->addRenderFunction(render);
    
    mesh = generateSphere(Glean::math::createVector(0, 0, 3), 1, 100); //new Glean::graphics::Mesh(verticies);
     
    shader = Glean::graphics::loadShaderRecursive("assets/shader.vert", "assets/shader.frag");
    
    testCL();
    
	window->start();
    
#ifdef _WIN32
	std::cin.get();
#endif
    return 0;
}
