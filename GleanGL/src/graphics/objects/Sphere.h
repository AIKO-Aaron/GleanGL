#pragma once

#include "Mesh.h"

namespace Glean {
    namespace graphics {
        
        extern Mesh *generateSphere(Glean::math::Vector<3> center, float radius, float numSteps = 30);
        
    }
}
