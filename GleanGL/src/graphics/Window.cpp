#include "Window.h"

using namespace Glean::graphics;

void Window::init() {
	renderer = new Renderer(window);
    for(int i = 0; i < IMPLEMENTED_KEYS; i++) keysPressed[i] = false;
}

void Window::loop() {
	auto clock = std::chrono::high_resolution_clock();
    auto lastTime = clock.now();
    int fps = 0;
	while (fetchEvents()) {
		auto start = clock.now();
		
		// TODO: render, update, ...
		//printf("Render/Update loop\n");

        for(renderFunc f : renderFunctions) f(renderer);
        ++fps;
        
        auto n = clock.now();
        if(n - lastTime >= std::chrono::seconds(1)) {
            lastTime = n;
            printf("[GLEAN][INFO] FPS: %d\n", fps);
            fps = 0;
        }
        
		auto end = clock.now();
		std::this_thread::sleep_for(std::chrono::nanoseconds(10000000 / 60) - (end - start));
	}
}
