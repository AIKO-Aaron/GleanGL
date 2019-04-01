#include "Window.h"

using namespace Glean::graphics;

void Window::init() {
	renderer = new Renderer(window);
}

void Window::loop() {
	auto clock = std::chrono::high_resolution_clock();
	while (fetchEvents()) {
		auto start = clock.now();
		
		// TODO: render, update, ...
		//printf("Render/Update loop\n");

		renderer->clearColor(1, 0, 1, 1);
		renderer->swapBuffers();

		auto end = clock.now();
		std::this_thread::sleep_for(std::chrono::nanoseconds(10000000 / 60) - (end - start));
	}
}
