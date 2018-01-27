//
// Created by siddh on 2/11/17.
//

#include "transformedsurface.h"

Vector3D trans_normal(Vector3D norm, glm::mat4 m)
{
    glm::vec4 an = glm::transpose(m) * glm::vec4(norm.to_vec3(), 0);
    Vector3D normal(an.x, an.y, an.z);
    normal.normalize();
    return normal;
}
bool TransformedSurface::intersect(Ray &r) const {
    glm::vec4 to = inv * glm::vec4(r.getOrigin().to_vec3(), 1.0);
    glm::vec4 td = inv * glm::vec4(r.getDirection().to_vec3(), 0);

    Ray tr = Ray(Vector3D(to.x, to.y, to.z), Vector3D(0,0,0));
    tr.setDirection(Vector3D(td.x, td.y, td.z)); //No normalization

    model->intersect(tr);
    r.setNormal(trans_normal(tr.getNormal(), inv));
    r.setParameter(tr.getParameter(), tr.intersected());
}
