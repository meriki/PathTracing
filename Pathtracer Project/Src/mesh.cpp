//
// Created by meraki on 29/11/17.
//

#include "mesh.h"
#include <glm/glm.hpp>
#include "triangle.h"
#include <typeinfo>

bool Mesh::intersect(Ray &r) const {
    int i;
    bool isect = false;

    for(i=0;i<n_triangles;i++){
        isect |= triangles[i]->intersect(r);
    }
    return isect;
}
Vector3D Mesh::getTexCoord(Vector3D pos)	const   {
    return pos;
}