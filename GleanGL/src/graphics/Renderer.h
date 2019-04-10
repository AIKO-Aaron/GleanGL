#pragma once

#include "Shader.h"
#include "lighting/Light.h"
#include "objects/Mesh.h"

#define MAX_LIGHTS 5

namespace Glean {
	namespace graphics {

		class Renderer {
		private:
			__internalWindow window;
			__internalContext context; // GL / Vulkan context

            unsigned int vaoID = 0;
            Glean::graphics::Shader *shader = nullptr;
            
            std::vector<Glean::graphics::Light*> lights;
            std::vector<Glean::graphics::Mesh*> objects;
            
            lightSource *sources = new lightSource[MAX_LIGHTS];

		public:
			Renderer(__internalWindow window);

			void clearColor(float r, float g, float b, float a);
			void swapBuffers();
            
            inline void addLight(Glean::graphics::Light *light) { lights.push_back(light); }
            inline void addObject(Glean::graphics::Mesh *mesh) { objects.push_back(mesh); }
            
            void render();
		};

	}
}
