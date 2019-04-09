#include "Camera.h"

using namespace Glean::graphics;

void Glean::graphics::Camera::rotate(Glean::math::Vector<3> rotations) {
    cAngles += rotations;
    
    if(cAngles[0] <= -PI / 2.0f) cAngles[0] = -PI / 2.0f;
    if(cAngles[0] >= PI / 2.0f) cAngles[0] = PI / 2.0f;
}

void Glean::graphics::Camera::rotate(Glean::events::MouseMotionEvent *mEvent, float sensitivity) {
    rotate(Glean::math::createVector((float) mEvent->dy * sensitivity / 100.0f, -(float) mEvent->dx * sensitivity / 100.0f, 0));
}

Glean::math::Matrix<4, 4> Glean::graphics::Camera::getTransformation() {
    Glean::math::Matrix<4, 4> m = Glean::math::identity<4>();
    
    Glean::math::Vector<4> frontVert = Glean::math::createVector(0, 0, 1, 0); // Just a direction... normalized
    frontVert = Glean::math::rotate_x(cAngles[0]) * frontVert;
    frontVert = Glean::math::rotate_y(cAngles[1]) * frontVert;
    frontVert = Glean::math::rotate_z(cAngles[2]) * frontVert;
    // frontVert.print();
    frontVert.normalize();
    
    Glean::math::Vector<3> up = Glean::math::createVector(0, 1, 0); // Up is always just 0,1,0
    Glean::math::Vector<3> front = Glean::math::Vector<3>(&frontVert[0]).normalize();
    Glean::math::Vector<3> right = Glean::math::cross(up, front); // Always unit if up & front are too
    Glean::math::Vector<3> actualUp = Glean::math::cross(right, front);
    
    right.normalize();
    actualUp.normalize();
    
    m(0, 0) = right[0];
    m(0, 1) = right[1];
    m(0, 2) = right[2];
    
    m(1, 0) = actualUp[0];
    m(1, 1) = actualUp[1];
    m(1, 2) = actualUp[2];
    
    m(2, 0) = -frontVert[0];
    m(2, 1) = -frontVert[1];
    m(2, 2) = -frontVert[2];
    
    Glean::math::Matrix<4, 4> translation1 = Glean::math::identity<4>();
    translation1(0, 3) = -cPosition[0];
    translation1(1, 3) = -cPosition[1];
    translation1(2, 3) = -cPosition[2];

    m = m * translation1;
    
    return m;
}
