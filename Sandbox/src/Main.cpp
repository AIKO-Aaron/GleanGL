#include <iostream>

#include "graphics/Window.h"
#include "graphics/Shader.h"

using namespace Glean::graphics;

void handleEvent(Glean::events::Event *e) {
    if(e->type == Glean::events::KEYDOWN) {
        Glean::events::KeyEvent *kEvent = e->asKeyEvent();
        if(kEvent->isPlatformCtrlDown() && kEvent->key == Glean::events::kQ) exit(0);
        printf("[SANDBOX][DEBUG] Pressed Key: %c\n", Glean::events::getCharFromKey(kEvent->key));
	}
	else if (e->type == Glean::events::MOUSEMOTION) {
		Glean::events::MouseMotionEvent *mEvent = e->asMouseMotionEvent();
		printf("[SANDBOX][DEBUG] Mouse position on screen: %d|%d\n", mEvent->xPos, mEvent->yPos);
	}
}

void render(Glean::graphics::Renderer *renderer) {
    renderer->clearColor(0, 0, 0, 1);
    renderer->swapBuffers();
}

int main(int argc, char **args) {    
	Window *window = new Window("Hello World", 960, 540);
    window->addEventHandler(handleEvent);
    window->addRenderFunction(render);

	Glean::graphics::Shader *shader = new Glean::graphics::Shader("#version 330 core\nvoid main() {\n\n}\n", "#version 330 core\nvoid main() {\n\n}\n");

	window->start();

	std::cin.get();
}
