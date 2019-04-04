#pragma once

#include "../math/GleanMath.h"
#include "../events/Event.h"
#include "Shader.h"

namespace Glean {
    namespace graphics {
        
        class Camera {
        private:
            Glean::math::Vector<3> cPosition; // 0, 0, 0
            Glean::math::Vector<4> cDirection = Glean::math::createVector(0, 0, 1, 0); // 0, 0, 0, 0

        public:
            inline void move(Glean::math::Vector<3> moved) { cPosition += moved; }
            void rotate(Glean::math::Vector<3> rotations);
            void rotate(Glean::events::MouseMotionEvent *mEvent, float sensitivity = 1.0f);
            Glean::math::Matrix<4, 4> getTransformation();
            
        };
        
    }
}
