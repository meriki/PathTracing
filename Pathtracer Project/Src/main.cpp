//Attribution: RayTracer code from Assignment 4 provided by our TA


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>




#include "camera.h"
#include "renderengine.h"
#include "world.h"
#include "material.h"
#include "object.h"
#include "sphere.h"
#include "reflective_material.h"
#include "utility.hpp"
#include "triangle.h"
#include "cylinder.h"
#include "transformedsurface.h"
#include "texture.h"
#include "mesh.h"
//Globals
GLFWwindow * mainWindow = nullptr;
GLuint program;
GLuint quadVao,quadVbo;
int screen_width = 1280/4, screen_height = 720/4;
float quadVertices[] = {-1, -1,
                        1, -1,
                        1, 1,
                        -1, -1,
                        1, 1,
                        -1, 1};
GLuint texImage;
GLint uniform_texImage;

Camera *camera;
RenderEngine *engine;

int init_resources()
{

    auto vert(fileToCharArr("./Resources/vshader.vert"));
    auto frag(fileToCharArr("./Resources/fshader.frag"));



	//Create program
    program = makeProgram(compileShader(shDf(GL_VERTEX_SHADER,&vert[0],vert.size())),compileShader(shDf(GL_FRAGMENT_SHADER,&frag[0],frag.size())),true);



	//Initialize raytracer objects
	Vector3D camera_position(0, -5, 2.5);
	Vector3D camera_target(0, 0, 1); //Looking down -Z axis
	Vector3D camera_up(0, 1, 0);
	float camera_fovy =  45;
	camera = new Camera(camera_position, camera_target, camera_up, camera_fovy, screen_width, screen_height);
	//Create a world
	World *world = new World;
	//world->setAmbient(Color(1));
	//world->setBackground(Color(0.55, 0.49, 0.5));
    world->setBackground(Color(0));
    Material *def = new Material(Color(1));

    Material *m1 = new Material(Color(0.85, 0.4, 0.4));

    Material *m2 = new Material( Color(0.4, 0.4, 0.85));
    Material *m3 = new Material( Color(0.4, 0.85, 0.4));

    Material *l = new Material(Color(1),Color(2.2));
    Material *mr = new ReflectiveMaterial(0.1);

    Texture *t = new Texture("../Resources/chess.png");
    Material *tx = new Material(Color(), Color(), t);

    //Scene description adapted from small-pt
    Sphere *s1 = new Sphere(Vector3D(0,0,-1000), 997, def);
    Sphere *s2 = new Sphere(Vector3D(-1004,0,0), 1000, m1);
    Sphere *s3 = new Sphere(Vector3D(1004,0,0), 1000, m2);
    Sphere *s4 = new Sphere(Vector3D(0,1006,0), 1000, def);
    Sphere *s5 = new Sphere(Vector3D(0,0,110), 100, l);
    //Sphere *s6 = new Sphere(Vector3D(-0.5,-0.5,1), 1, tx);
    //Sphere *s7 = new Sphere(Vector3D(1,1,1), 1, mr);
    Object *teapot = new Mesh(m3);
    world->addObject(s1);
    world->addObject(s2);
    world->addObject(s3);
    world->addObject(s4);
    world->addObject(s5);
    //world->addObject(s6);
    //world->addObject(s7);
    world->addObject(teapot);
	engine = new RenderEngine(world, camera);
    //engine->activate_saa(); //Jittering sampling - makes rendering slower

    glGenVertexArrays(1, &quadVao);


    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glBindVertexArray(quadVao);
    glBindBuffer(GL_ARRAY_BUFFER,quadVbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);



    //Initialise texture
	glGenTextures(1, &texImage);
	glBindTexture(GL_TEXTURE_2D, texImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, camera->getBitmap());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	uniform_texImage = glGetUniformLocation(program, "texImage");
	if(uniform_texImage == -1)
	{
		fprintf(stderr, "Could not bind uniform: texImage\n");
		return 0;
	}
	return 1;
}



int main() {
    using namespace std;



    mainWindow = setupGlfw(screen_width,screen_height,"Lumina 2");


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize OpenGL context" << endl;
        exit(-1);
    }



	if (1 != init_resources()) {
        exit(-1);
	}

    double last = 0,accumulator = 0;
    glfwSetTime(last);
    double delta = 0.0f;
    glfwSwapInterval(1);

    bool done = false;
    while (!glfwWindowShouldClose(mainWindow)) {


        double curr = glfwGetTime();
        delta = curr-last;
        last = curr;
        glfwPollEvents();



        if(glfwGetKey(mainWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(mainWindow, GLFW_TRUE);
        }

        if(done)
            continue;
        if(engine->renderLoop())
        {
            done = true;
            cout << "Rendering complete" << endl;
        }

        //Update texture on GPU
        glBindTexture(GL_TEXTURE_2D, texImage);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screen_width, screen_height, GL_RGB, GL_FLOAT, camera->getBitmap());



        glClearColor(0.0, 0.0, 0.0, 0.0);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texImage);
        glUniform1i(uniform_texImage, 0);


        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);

    }


    glDeleteVertexArrays(1,&quadVao);
    glDeleteBuffers(1,&quadVbo);

    glDeleteProgram(program);
    glDeleteTextures(1, &texImage);
	return EXIT_SUCCESS;
}
