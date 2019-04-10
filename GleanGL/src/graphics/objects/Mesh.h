#pragma once

#include <vector>
#include "../../math/GleanMath.h"
#include "../native/Universal/OpenGL/GleanGL.h"

namespace Glean {
    namespace graphics {
        
#pragma push(push, 1)
        typedef struct {
            float x, y, z;
            float nx, ny, nz;
            float u, v;
        } vertexData;
#pragma pop
        
        class Mesh {
        private:
            GLuint *vertexBuffers = new GLuint[2];
            GLuint numVerticies;
            
        public:
            Mesh(std::vector<Glean::math::Vector<3>> verticies);
            void render();
        };
        
    }
}
