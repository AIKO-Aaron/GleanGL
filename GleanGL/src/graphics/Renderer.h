#pragma once

namespace Glean {
	namespace graphics {

		class Renderer {
		private:
			__internalWindow window;
			__internalContext context; // GL / Vulkan context

            unsigned int vaoID;
            
		public:
			Renderer(__internalWindow window);

			void clearColor(float r, float g, float b, float a);
			void swapBuffers();            
		};

	}
}
