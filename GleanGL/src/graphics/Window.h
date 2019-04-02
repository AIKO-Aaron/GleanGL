#pragma once

#include "Universal/Platform.h"
#include "Renderer.h"
#include <stdio.h>

#include "../events/Event.h"

#include <thread>
#include <chrono>
#include <vector>

namespace Glean {
	namespace graphics {

        typedef void (*renderFunc)(Renderer *renderer);
        typedef void (*eventDispatchFunc)(Glean::events::Event *event);

		class Window {
		private:
			__internalWindow window;

            void loop();
			void init();
			bool fetchEvents();
            
            std::vector<renderFunc> renderFunctions;
            std::vector<eventDispatchFunc> eventHandlers;

			Renderer* renderer;
		public:
			Window(const char *title, int width, int height);
			Window(const char *title, int width, int height, int x, int y);
			void start();
            
            inline void dispatchEvent(Glean::events::Event *e) { for(eventDispatchFunc f : eventHandlers) f(e); }
            
            inline void addRenderFunction(renderFunc rf) { renderFunctions.push_back(rf); }
            inline void addEventHandler(eventDispatchFunc ef) { eventHandlers.push_back(ef); }
		};

	}
}
