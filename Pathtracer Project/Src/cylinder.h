//
// Created by siddh on 11-10-2017.
//

#ifndef ASSIGNMENT4_CYLINDER_H
#define ASSIGNMENT4_CYLINDER_H
#include "object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cylinder : public Object {
    //Axis aligned Cylinder
private:
    double height, radius;
public:
    Cylinder(double _h, double _r, Material *m):
            Object(m), height(_h), radius(_r)    {
    }

    virtual bool intersect(Ray &r) const;

};


#endif //ASSIGNMENT4_CYLINDER_H
