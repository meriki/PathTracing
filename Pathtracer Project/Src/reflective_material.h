//
// Created by sid on 29/11/17.
//
#include "material.h"
#ifndef CGPROJECT_REFLECTIVE_MATERIAL_H
#define CGPROJECT_REFLECTIVE_MATERIAL_H


class ReflectiveMaterial: public Material {
public:
    ReflectiveMaterial(float r): Material(Color(1)), roughness(r)    {}
    Ray getNextRay(Ray& incident);
private:
    float roughness;
};


#endif //CGPROJECT_REFLECTIVE_MATERIAL_H
