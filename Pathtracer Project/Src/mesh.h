#ifndef CGPROJECT_MESH_H
#define CGPROJECT_MESH_H

#include "object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <bits/stdc++.h>

#include "object.h"
#include "ray.h"
#include "vector3D.h"
#include "color.h"
#include "material.h"
#include "triangle.h"

class Mesh : public Object
{
private:
    std::vector< unsigned int > vertexIndices, normalIndices;
    std::vector <Object*> triangles;
    int n_triangles;
    Material *material;

    double maxX, minX, maxY, minY, maxZ, minZ;

public:
    Mesh(Material *m):
            Object(m) {

        maxX = 10000;
        minX = -10000;
        maxZ = 10000;
        minZ = -10000;
        maxY = 10000;
        minY = -10000;

        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        FILE *file = fopen("../Resources/teapot.obj", "r");
        if (file == NULL) {
            printf("Impossible to open the file !\n");

        }

        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);

        std::vector<unsigned int> vertexIndices, normalIndices;


        while (res != EOF) {

            // read the first word of the line
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);

            }
            else if (strcmp(lineHeader, "f") == 0) {
                unsigned int vertexIndex[3],normalIndex[3];
//            int matches = fscanf(file, "%d//%d  %d//%d  %d//%d", &vertexIndex[0], &normalIndex[0],&vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

                if (matches == 3) {
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);

                } else {
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                }
            }
            res = fscanf(file, "%s", lineHeader);
        }


        int i, j = 0;

        for (i = 0; i < vertexIndices.size(); i=i+3) {
            Vector3D a = Vector3D(temp_vertices[vertexIndices[i] - 1].x, temp_vertices[vertexIndices[i] - 1].y,
                                  temp_vertices[vertexIndices[i] - 1].z);
            Vector3D b = Vector3D(temp_vertices[vertexIndices[i + 1] - 1].x, temp_vertices[vertexIndices[i + 1] - 1].y,
                                  temp_vertices[vertexIndices[i + 1] - 1].z);
            Vector3D c = Vector3D(temp_vertices[vertexIndices[i + 2] - 1].x, temp_vertices[vertexIndices[i + 2] - 1].y,
                                  temp_vertices[vertexIndices[i + 2] - 1].z);
            Object *temp = new Triangle(a/50.0, b/50.0, c/50.0, m);

            maxX = std::max(maxX, (a/50.0).X());
            maxX = std::max(maxX, (b/50.0).X());
            maxX = std::max(maxX, (c/50.0).X());
            minX = std::min(minX, (a/50.0).X());
            minX = std::min(minX, (b/50.0).X());
            minX = std::min(minX, (c/50.0).X());

            maxY = std::max(maxY, (a/50.0).Y());
            maxY = std::max(maxY, (b/50.0).Y());
            maxY = std::max(maxY, (c/50.0).Y());
            minY = std::min(minY, (a/50.0).Y());
            minY = std::min(minY, (b/50.0).Y());
            minY = std::min(minY, (c/50.0).Y());

            maxZ = std::max(maxZ, (a/50.0).Z());
            maxZ = std::max(maxZ, (b/50.0).Z());
            maxZ = std::max(maxZ, (c/50.0).Z());
            minZ = std::min(minZ, (a/50.0).Z());
            minZ = std::min(minZ, (b/50.0).Z());
            minZ = std::min(minZ, (c/50.0).Z());
            triangles.push_back(temp);
        }

        n_triangles= vertexIndices.size()/3;

    }





    virtual bool intersect(Ray &r) const;
    Vector3D getTexCoord(Vector3D pos)	const;
};


#endif //CGPROJECT_MESH_H
