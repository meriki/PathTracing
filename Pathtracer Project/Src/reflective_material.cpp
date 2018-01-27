//
// Created by sid on 29/11/17.
//

#include "reflective_material.h"
#include <random>

using namespace std;
static std::default_random_engine randgen;
static std::uniform_real_distribution<float> uniform_dist(0, 1);


Ray ReflectiveMaterial::getNextRay(Ray &incident) {
    float eps = 1e-5;
    Vector3D dir = incident.getDirection() -
                   2.0 * dotProduct(incident.getNormal(), incident.getDirection()) * incident.getNormal();
    dir += roughness*(Vector3D(uniform_dist(randgen),uniform_dist(randgen),uniform_dist(randgen)) - Vector3D(0.5));
    dir.normalize();
    Ray reflected = Ray(incident.getPosition() + eps*dir, dir, incident.getLevel()+1);

    return reflected;
}