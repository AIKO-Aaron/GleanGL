#pragma once

#include "Universal/Platform.h"
#include "Renderer.h"
#include <stdio.h>

#include <thread>
#include <chrono>

namespace Glean {
	namespace graphics {

		class Window {
		private:
			__internalWindow window;

			void init();
			bool fetchEvents();

			Renderer* renderer;
            void loop();
		public:            
			Window(const char *title, int width, int height);
			Window(const char *title, int width, int height, int x, int y);
			void start();
		};

	}
}
