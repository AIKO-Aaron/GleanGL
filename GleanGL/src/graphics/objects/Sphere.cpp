#include "Sphere.h"

Glean::graphics::Mesh *Glean::graphics::generateSphere(Glean::math::Vector<3> center, float radius, float numSteps) {
    std::vector<Glean::math::Vector<3>> verticies;
    
    float epsilon_big = 2.0f * PI / numSteps;
    float epsilon_small = PI / numSteps;
    
    for(int i = 1; i <= numSteps; i++) {
        for(int j = 1; j <= numSteps; j++) {
            float phi = epsilon_small * j;
            float theta = epsilon_big * i;
            
            float lphi = epsilon_small * (j - 1);
            float ltheta = epsilon_big * (i - 1);

            Glean::math::Vector<3> p1 = Glean::math::createVector(sin( theta) * sin( phi), cos( theta), sin( theta) * cos( phi)) * radius + center;
            Glean::math::Vector<3> p2 = Glean::math::createVector(sin(ltheta) * sin( phi), cos(ltheta), sin(ltheta) * cos( phi)) * radius + center;
            Glean::math::Vector<3> p3 = Glean::math::createVector(sin(ltheta) * sin(lphi), cos(ltheta), sin(ltheta) * cos(lphi)) * radius + center;
            Glean::math::Vector<3> p4 = Glean::math::createVector(sin( theta) * sin(lphi), cos( theta), sin( theta) * cos(lphi)) * radius + center;

            if(i <= numSteps / 2) {
                verticies.push_back(p1);
                verticies.push_back(p2);
                verticies.push_back(p3);
                
                verticies.push_back(p3);
                verticies.push_back(p4);
                verticies.push_back(p1);
            } else {
                verticies.push_back(p3);
                verticies.push_back(p2);
                verticies.push_back(p1);
                
                verticies.push_back(p1);
                verticies.push_back(p4);
                verticies.push_back(p3);
            }
            
        }
    }
    
    Glean::graphics::Mesh *mesh = new Glean::graphics::Mesh(verticies);
    return mesh;
}
