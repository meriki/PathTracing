//
// Created by siddh on 11-10-2017.
//

#ifndef ASSIGNMENT4_TRIANGLE_H
#define ASSIGNMENT4_TRIANGLE_H

#include "../Src/object.h"
#include "../Src/ray.h"
#include "../Src/vector3D.h"
#include "../Src/color.h"

class Triangle: public Object {
private:
    Vector3D A, B, C, normal;

public:
    Triangle(const Vector3D vert1, const Vector3D vert2, const Vector3D vert3, Material * m):
            Object(m){
        A = vert1;
        B = vert2;
        C = vert3;

        normal = -crossProduct(B-A, C-A);
        normal.normalize();
    }

    virtual  bool intersect(Ray &r) const;
    virtual Vector3D getTexCoord(Vector3D pos)	const;
};


#endif //ASSIGNMENT4_TRIANGLE_H
