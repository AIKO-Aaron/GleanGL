#include <iostream>

#include "graphics/Window.h"

using namespace Glean::graphics;

int main(int argc, char **args) {
	Window *window = new Window("Hello World", 960, 540);
	window->start();

	std::cin.get();
}
