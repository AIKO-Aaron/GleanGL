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

static Glean::math::Vector<4> cpos = Glean::math::createVector(0, 0, 1, 1);
static Glean::math::Vector<2> cangles = Glean::math::createVector(PI, 0);
static GLuint texID;
static GLuint *vertexBuffers = new GLuint[2];

void handleEvent(Glean::events::Event *e) {
    if(e->type == Glean::events::KEYDOWN) {
        Glean::events::KeyEvent *kEvent = e->asKeyEvent();
		if (kEvent->isPlatformCtrlDown() && kEvent->key == Glean::events::kQ) exit(0);
        //printf("[SANDBOX][DEBUG] Pressed Key: %c\n", Glean::events::getCharFromKey(kEvent->key));
        // if(kEvent->key == Glean::events::kW) c.move(Glean::math::createVector(0, 0, 0.01));
	}
	else if (e->type == Glean::events::MOUSEMOTION) {
		Glean::events::MouseMotionEvent *mEvent = e->asMouseMotionEvent();
        c.rotate(mEvent);
        cangles += Glean::math::createVector((float) mEvent->dx / 100.0f, (float) mEvent->dy / 100.0f);
        if(cangles[1] < -PI / 2.0f) cangles[1] = -PI / 2.0f + 0.00001f;
        if(cangles[1] > PI / 2.0f) cangles[1] = PI / 2.0f - 0.00001f;

		//printf("[SANDBOX][DEBUG] Mouse position on screen: %d|%d\n", mEvent->xPos, mEvent->yPos);
	}
}

void render(Glean::graphics::Renderer *renderer) {
    /**renderer->clearColor(0, 0, 0, 1);

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
    }*/

    renderer->clearColor(0, 0, 0, 1);
    
    unsigned char *img = testRay(cpos, cangles);
    //cangles[1] += PI / 1000.0f;
    //cangles[0] -= PI / 1000.0f;
    
    float dx = 0;
    float dy = 0;
    float dz = 0;
    
    if(window->isKeyPressed(Glean::events::kA)) dx += 0.1f;
    if(window->isKeyPressed(Glean::events::kD)) dx -= 0.1f;
    if(window->isKeyPressed(Glean::events::kS)) dz += 0.1f;
    if(window->isKeyPressed(Glean::events::kW)) dz -= 0.1f;
    if(window->isKeyPressed(Glean::events::kSHIFT)) dy -= 0.1f;
    if(window->isKeyPressed(Glean::events::kSPACE)) dy += 0.1f;
    
    Glean::math::Vector<4> moveVec = Glean::math::createVector(dx * cos(cangles[0]) + dz * sin(cangles[0]), dy, -dx * sin(cangles[0]) + dz * cos(cangles[0]), 0);
    cpos -= moveVec;
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 960, 540, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img);

    shader->bind();
    shader->uniformi("tex", 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[1]);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    renderer->swapBuffers();

    GLuint err;
    if((err = glGetError()) != GL_NO_ERROR) {
        printf("[SANDBODX][ERROR] GL-Error has occured: %d\n", err);
        exit(0);
    }
}

int main(int argc, char **args) {    
	window = new Window("Hello World", 960, 540);
    window->captureMouse();
    window->addEventHandler(handleEvent);
    window->addRenderFunction(render);
    
    //mesh = generateSphere(Glean::math::createVector(0, 0, 3), 1, 100); //new Glean::graphics::Mesh(verticies);
	mesh = generateSphere(Glean::math::createVector(0, 0, -3), 1, 100); //new Glean::graphics::Mesh(verticies);

    //shader = Glean::graphics::loadShaderRecursive("assets/shader.vert", "assets/shader.frag");
    shader = Glean::graphics::loadShaderRecursive("assets/image.vert", "assets/image.frag");
    
    glGenBuffers(2, vertexBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 4, new float[5 * 4] {
          -1,  1, 0, 0, 0,
           1,  1, 0.1, 1, 0,
           1, -1, 0, 1, 1,
          -1, -1, 0, 0, 1
    }, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, new unsigned int[6] {0, 1, 2, 2, 3, 0}, GL_STATIC_DRAW);

    // testCL();
    
	initCL();
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	window->start();
    
#ifdef _WIN32
	std::cin.get();
#endif
    return 0;
}
