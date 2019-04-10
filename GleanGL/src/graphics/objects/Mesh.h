#pragma once

#include <vector>
#include "../../math/GleanMath.h"
#include "../native/Universal/OpenGL/GleanGL.h"

namespace Glean {
    namespace graphics {
        
#pragma pack(push, 1)
        typedef struct {
            float x, y, z;
            float nx, ny, nz;
            float u, v;
        } vertexData;
#pragma pack(pop)
        
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
