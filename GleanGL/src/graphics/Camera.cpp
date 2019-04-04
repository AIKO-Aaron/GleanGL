#include "Camera.h"

using namespace Glean::graphics;

void Glean::graphics::Camera::rotate(Glean::math::Vector<3> rotations) {
    cDirection = Glean::math::rotate_z(rotations[2]) * Glean::math::rotate_y(rotations[1]) * Glean::math::rotate_x(rotations[0]) * cDirection;
}

void Glean::graphics::Camera::rotate(Glean::events::MouseMotionEvent *mEvent, float sensitivity) {
    rotate(Glean::math::createVector(-(float) mEvent->dy * sensitivity / 100.0f, -(float) mEvent->dx * sensitivity / 100.0f, 0));
}

Glean::math::Matrix<4, 4> Glean::graphics::Camera::getTransformation() {
    Glean::math::Matrix<4, 4> m = Glean::math::identity<4>();
    
    // v1 = right
    // v2 = up
    // v3 = front
    
    // x1, x2, x3, tx
    // y1, y2, y2, zy
    // z1, z2, z3, tz
    //  0,  0,  0, 1
    
    Glean::math::Vector<3> up = Glean::math::createVector(0, 1, 0); // Up is always just 0,1,0
    Glean::math::Vector<3> front = Glean::math::Vector<3>(&cDirection[0]);
    Glean::math::Vector<3> right = Glean::math::cross(up, front);
    
    m(0, 0) = right[0];
    m(1, 0) = right[1];
    m(2, 0) = right[2];
    
    m(0, 1) = up[0];
    m(1, 1) = up[1];
    m(2, 1) = up[2];
    
    m(0, 2) = cDirection[0];
    m(1, 2) = cDirection[1];
    m(2, 2) = cDirection[2];
    
    /**Glean::math::Matrix<4, 4> translation = Glean::math::identity<4>();
    translation(0, 3) = cPosition[0];
    translation(1, 3) = cPosition[1];
    translation(2, 3) = cPosition[2];*/
    
    m(0, 3) = cPosition[0] * m(0, 0) + cPosition[1] * m(0, 1) + cPosition[2] * m(0, 2);
    m(1, 3) = cPosition[0] * m(1, 0) + cPosition[1] * m(1, 1) + cPosition[2] * m(1, 2);
    m(2, 3) = cPosition[0] * m(2, 0) + cPosition[1] * m(2, 1) + cPosition[2] * m(2, 2);
    
    // x1, x2, x3, 0
    // y1, y2, y2, 0
    // z1, z2, z3, 0
    //  0,  0,  0, 1
    
    // 1, 0, 0, tx
    // 0, 1, 0, zy
    // 0, 0, 1, tz
    // 0, 0, 0, 1
    
    // x1, x2, x3, x1*tx+x2*ty+x3*tz
    //
    //
    //
    
    return m;
}
