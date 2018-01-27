#include "world.h"
#include "material.h"
#include "sphere.h"
#include <glm/glm.hpp>
#include <utility>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;
static std::default_random_engine randgen;
static std::uniform_real_distribution<float> uniform_dist(0, 1);

glm::mat3x3 normalCoordTransformation(const Vector3D &normal)	{
	Vector3D X, Y, Z;
	Y = normal;
	if(fabs(Y.X()) > fabs(Y.Y()))
		X = Vector3D(Y.Z(), 0, -Y.X());
	else
		X = Vector3D(0, Y.Z(), -Y.Y());
	X.normalize();
	Z = crossProduct(X, Y);

	return glm::mat3x3(X.to_vec3(), Y.to_vec3(), Z.to_vec3());
}

Vector3D sampleHemisphereDirection()	{
	float cosPhi = uniform_dist(randgen);
	float sinPhi = sqrt(1-cosPhi*cosPhi);
	float theta = 2*M_PI*uniform_dist(randgen);

	Vector3D dir;
	dir.X(sinPhi*cos(theta));
	dir.Y(cosPhi);
	dir.Z(sinPhi*sin(theta));

	return dir;
}

Ray Material::getNextRay(Ray &incident) {
	float eps = 1e-5;

	glm::mat3x3 trans = normalCoordTransformation(incident.getNormal());
	glm::vec3 dir = glm::normalize(trans * sampleHemisphereDirection().to_vec3());
	Ray reflected = Ray(incident.getPosition() + eps * dir, dir, incident.getLevel() + 1);

	return reflected;
}