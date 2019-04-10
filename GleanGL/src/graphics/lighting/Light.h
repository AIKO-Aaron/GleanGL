#pragma once

#include "../../math/GleanMath.h"

namespace Glean {
    namespace graphics {
        
#pragma pack(push, 1)
        typedef struct {
            float x, y, z, w; // Position
            float r, g, b; // Color
            float brightness; // Brightness
            float a1, a2, a3; // Attenuation
            float _a; // unused
        } lightSource;
#pragma pack(pop)
        
        class Light {
        private:
            lightSource source;
            
        public:
            Light(Glean::math::Vector<4> position, Glean::math::Vector<3> color, float brightness);
            Light(Glean::math::Vector<4> position, Glean::math::Vector<3> color, float brightness, Glean::math::Vector<3> attenuation);
        
            inline lightSource getLightSource() { return source; }
        };
        
    }
}
