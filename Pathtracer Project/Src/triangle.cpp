//
// Created by siddh on 11-10-2017.
//

#include "triangle.h"
#include <glm/glm.hpp>

bool Triangle::intersect(Ray &r) const {

    using glm::vec3;
    vec3 e = r.getOrigin().to_vec3();
    vec3 d = r.getDirection().to_vec3();
    vec3 a = A.to_vec3(), b = B.to_vec3(), c = C.to_vec3();
    glm::mat3 A(a - b, a - c, d),
              B(a - e, a - c, d),
              C(a - b, a - e, d),
              D(a - b, a - c, a - e);

    double detA = glm::determinant(A);
    double beta = glm::determinant(B)/detA;
    double gamma = glm::determinant(C)/detA;
    double t = glm::determinant(D)/detA;

    if(beta > 0 && gamma > 0 && beta + gamma < 1)   {
        if(r.setParameter(t, this)) {
            r.setNormal(normal);
            return true;
        }
    }

    return false;
}

Vector3D Triangle::getTexCoord(Vector3D pos)	const   {
    return pos;
}