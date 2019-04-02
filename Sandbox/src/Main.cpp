#include <iostream>

#include "graphics/Window.h"

using namespace Glean::graphics;

void handleEvent(Glean::events::Event *e) {
    if(e->type == Glean::events::KEYDOWN) {
        Glean::events::KeyEvent *kEvent = e->asKeyEvent();
        if(kEvent->isPlatformCtrlDown() && kEvent->key == Glean::events::kQ) exit(0);
        printf("Pressed Key: %c\n", Glean::events::getCharFromKey(kEvent->key));
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
	window->start();

	std::cin.get();
}
