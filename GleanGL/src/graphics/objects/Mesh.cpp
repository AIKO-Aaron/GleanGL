#include "Mesh.h"

using namespace Glean::graphics;



Glean::graphics::Mesh::Mesh(std::vector<Glean::math::Vector<3>> verticies) {
    vertexData *data = new vertexData[verticies.size()];
    GLuint *indicies = new GLuint[verticies.size()];
    
    numVerticies = (GLuint) verticies.size();
    
    for(int i = 0; i < verticies.size() / 3; i++) {
        Glean::math::Vector<3> p1 = verticies[3 * i + 0] - verticies[3 * i + 1];
        Glean::math::Vector<3> p2 = verticies[3 * i + 0] - verticies[3 * i + 2];
        Glean::math::Vector<3> normal = Glean::math::cross(p1, p2);
        
        for(int j = 0; j < 3; j++) {
            data[3 * i + j].x = verticies[3 * i + j][0];
            data[3 * i + j].y = verticies[3 * i + j][1];
            data[3 * i + j].z = verticies[3 * i + j][2];
            
            data[3 * i + j].nx = normal[0];
            data[3 * i + j].ny = normal[1];
            data[3 * i + j].nz = normal[2];
                        
            indicies[3 * i + j] = 3 * i + j;
        }
    }
    glGenBuffers(2, vertexBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * verticies.size(), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * verticies.size(), indicies, GL_STATIC_DRAW);

    delete[] data;
    delete[] indicies;
}

void Glean::graphics::Mesh::render() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*) (sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*) (sizeof(float) * 6));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[1]);
    
    glDrawElements(GL_TRIANGLES, numVerticies, GL_UNSIGNED_INT, 0);

    /*glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);*/

}
