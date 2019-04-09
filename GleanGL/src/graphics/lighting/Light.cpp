#include "Light.h"

using namespace Glean::graphics;

Glean::graphics::Light::Light(Glean::math::Vector<4> pos, Glean::math::Vector<3> col, float brightness) {
    source.x = pos[0];
    source.y = pos[1];
    source.z = pos[2];
    source.w = pos[3];

    source.r = col[0];
    source.g = col[1];
    source.b = col[2];

    source.x = brightness;
    
    source.a1 = 1; // constant
    source.a2 = 0.01f;
    source.a3 = 0.0001f;
}

