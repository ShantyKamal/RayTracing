/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Program.h"
#include "PrimaryRay.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <limits>


Program::Program() {
        setupWindow();
}

Program::~Program() {
  
}

/*Program::trace(){
    simply creating a variable in the trace() function that keeps track of the closest distance between the ray origin and the intersection point while we iterate over the objects' triangles.
}*/

void Program::start() {
    
    
    Scene scene = populateScene(2);
    image.Initialize();
    
    //FOR EACH PIXEL
	for (unsigned int i = 0; i < image.Width(); i++) {
        for (unsigned int j = 0; j < image.Height(); j++) {
            //COMPUTE PRIMARY RAY
            PrimaryRay viewRay;
            glm::vec3 d = viewRay.directionVector(i, j, image.Width(), image.Height());
            // SHOOT PRIMARY RAY INTO SCENE AND LOOK FOR INTERSECTION
            glm::vec3 hitPt;
            glm::vec3 hitNormal;
            float nearest = INFINITY;
            Surface* visibleSurface = NULL;
       //FOR EVERY OBJECT IN SCENE
          for (unsigned int k = 0; k < scene.objects.size(); k++)
          {
               //IF RAY HITS AN OBJECT
                  if (scene.objects.at(k)->intersect(viewRay))
                  {
                      float distance = scene.objects.at(k)->intersectionDist(viewRay);
                      //CHECK IF ITS THE CLOSEST
                      if (distance < nearest)
                            {   visibleSurface = scene.objects.at(k);
                                nearest = distance;
                            }
                  }
          }
          if (visibleSurface!= NULL)     //FOUND NEAREST SURFACE
          {  //Ray shadowRay;
              //shadowRay.direction = lightPos - hitPt;
              //bool isInShadow = false;
              //for (int k = 0; k < objects.size(); ++k) {
                 // if (Intersect(objects[k], shadowRay)) {
               //       isInShadow = true;
                //      break;
                //  }
             // }
              image.SetPixel(i, j, visibleSurface->getColor());
          }
          else
              image.SetPixel(i, j, glm::vec3(1.0,1,1));
          }}
	  

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
	        image.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 500;
	int height = 500;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


Scene Program::populateScene(int num)
{
    Scene scene = Scene();
    if(num==1){
   
    //SPHERE
    scene.addObj(new Sphere(0.9, -1.925, -6.69, 0.825, 0.5, 0.5, 0.5));
    //PYRAMID
    scene.addObj(new Triangle ( -0.4, -2.75, -9.55,
                                -0.93, 0.55, -8.51,
                                0.11, -2.75, -7.98,
                               0.5, 1, 0.9));
    scene.addObj(new Triangle (0.11, -2.75, -7.98,
                                -0.93, 0.55 ,-8.51,
                                -1.46, -2.75 ,-7.47,
                               0.5, 1, 0.9));
    scene.addObj(new Triangle ( -1.46, -2.75, -7.47,
                                -0.93 ,0.55, -8.51,
                               -1.97, -2.75, -9.04,
                               0.5, 1, 0.9));
    scene.addObj(new Triangle (-1.97, -2.75, -9.04,
                                -0.93, 0.55, -8.51,
                               -0.4 ,-2.75, -9.55,
                               0.5, 1, 0.9));
    // Ceiling
   scene.addObj(new Triangle (2.75 ,2.75, -10.5,
                                2.75, 2.75 ,-5,
                                -2.75, 2.75, -5,
                              0.6, 0.7, 0.7));
   scene.addObj( new Triangle (-2.75, 2.75, -10.5,
                                2.75, 2.75, -10.5,
                               -2.75, 2.75, -5,
                               0.6, 0.7, 0.7));
    
// Green wall on right
     scene.addObj( new Triangle (2.75, 2.75, -5,
                                 2.75, 2.75, -10.5,
                                 2.75 ,-2.75, -10.5,
                                 0.6, 0.8, 0));
    
    scene.addObj(new Triangle (2.75 ,-2.75 ,-5,
                               2.75 ,2.75, -5,
                               2.75 ,-2.75, -10.5,
                               0.6, 0.8, 0));
    
// Red wall on left
    scene.addObj(new Triangle (
                                -2.75, -2.75, -5,
                                -2.75 ,-2.75, -10.5,
                                -2.75, 2.75, -10.5,
                                0.7, 0, 0));
    
    scene.addObj(new Triangle (
                                -2.75, 2.75, -5,
                                -2.75, -2.75, -5,
                                -2.75, 2.75, -10.5,
                                0.7, 0 , 0));

    // break;
    
 //Back wall
    scene.addObj(new Plane (
                            glm::vec3(0, 0, 1),
                            glm::vec3(0, 0, -10.5),
        1.0, 0, 0.0));
    
    // Floor
    scene.addObj(new Triangle (
    2.75, -2.75, -5,
    2.75 ,-2.75 ,-10.5,
    -2.75 ,-2.75 ,-10.5,
    0.6, 0.7, 0.7));
    scene.addObj(new Triangle (
    -2.75, -2.75, -5,
    2.75 , -2.75, -5,
    -2.75 , -2.75 ,-10.5,
    0.6, 0.7, 0.7));
   
    }
   
    else if (num ==2){
    
/*// Floor
    scene.addObj(new Plane (
                            glm::vec3(0, 1, 0),
                            glm::vec3(0, -1, 0),
        0.5, 0.5, 0.5 ));
    
//Back wall
    scene.addObj(new Plane (
                            glm::vec3(0, 0, 1),
                            glm::vec3(0, 0, -12),
        0.6, 0.9, 1));*/
    
// Large yellow sphere
    scene.addObj(new Sphere (
        1, -0.5, -3.5,
            0.5,
            1, 1, 0.2));
    
// Reflective grey sphere
    scene.addObj(new Sphere (
        0 ,1 ,-5,
        0.4, 0.5, 0.5, 0.5));
    
// Metallic purple sphere
    scene.addObj(new Sphere (
        -0.8, -0.75 ,-4,
        0.25, 1, 0.1, 1
        ));
    
// Green cone
    scene.addObj(new Triangle (
        0, -1, -5.8,
        0, 0.6, -5,
        0.4, -1 ,-5.693,
       0,1,0 ));
    scene.addObj(new Triangle (
        0.4, -1, -5.693,
        0, 0.6, -5,
        0.6928 ,-1, -5.4,
        0, 1,0));
   scene.addObj(new Triangle (
        0.6928 ,-1, -5.4,
        0, 0.6, -5,
        0.8, -1, -5,
            0,1,0 ));
    scene.addObj(new Triangle (
        0.8, -1, -5,
        0, 0.6 ,-5,
        0.6928, -1, -4.6,
         0,1,0 ));
    scene.addObj(new Triangle (
        0.6928, -1, -4.6,
        0 ,0.6, -5,
        0.4, -1 ,-4.307, 0,1, 0
                               ));
   scene.addObj(new Triangle (
        0.4, -1, -4.307,
        0 ,0.6 ,-5,
        0 ,-1, -4.2, 0, 1, 0));
    scene.addObj(new Triangle (
        0, -1, -4.2,
        0 ,0.6, -5,
       -0.4, -1, -4.307, 0,1,0));
    
    scene.addObj(new Triangle (
        -0.4, -1, -4.307,
        0, 0.6, -5,
        -0.6928, -1, -4.6, 0,1,0));
   scene.addObj(new Triangle (
        -0.6928, -1, -4.6,
        0, 0.6, -5,
        -0.8, -1, -5, 0,1,0));
    scene.addObj(new Triangle (
        -0.8, -1, -5,
        0, 0.6, -5,
        -0.6928, -1 ,-5.4, 0,1,0));
   scene.addObj(new Triangle (
        -0.6928, -1 ,-5.4,
        0 ,0.6 ,-5,
        -0.4, -1 ,-5.693, 0, 1,0));
    
    scene.addObj(new Triangle (
        -0.4, -1, -5.693,
        0, 0.6, -5,
      0, -1, -5.8,0,1,0));
    
// Shiny red icosahedron
    scene.addObj(new Triangle (
        -2, -1, -7,
        -1.276, -0.4472, -6.474,
        -2.276 ,-0.4472, -6.149,
            1, 0, 0));
   scene.addObj(new Triangle (
        -1.276, -0.4472, -6.474,
        -2, -1, -7,
   -1.276, -0.4472, -7.526, 1, 0, 0));
    
    scene.addObj(new Triangle (
        -2, -1, -7,
        -2.276, -0.4472, -6.149,
         -2.894, -0.4472, -7, 1, 0, 0));
   scene.addObj(new Triangle (
        -2, -1, -7,
        -2.894, -0.4472, -7,
     -2.276, -0.4472, -7.851,1, 0 , 0));
    
    scene.addObj(new Triangle (
        -2, -1, -7,
        -2.276, -0.4472, -7.851,
        -1.276, -0.4472, -7.526,1,0,0));
    scene.addObj(new Triangle (
        -1.276, -0.4472 ,-6.474,
        -1.276 ,-0.4472, -7.526,
        -1.106, 0.4472, -7,1,0,0));
    scene.addObj(new Triangle (
        -2.276, -0.4472, -6.149,
        -1.276, -0.4472, -6.474,
        -1.724, 0.4472, -6.149,1,0,0));
    scene.addObj(new Triangle (
        -2.894, -0.4472, -7,
        -2.276, -0.4472, -6.149,
          -2.724, 0.4472, -6.474, 1, 0 , 0));
   scene.addObj(new Triangle (
        -2.276, -0.4472, -7.851,
        -2.894, -0.4472, -7,
        -2.724, 0.4472, -7.526, 1, 0 ,0));
    scene.addObj(new Triangle (
        -1.276, -0.4472, -7.526,
        -2.276 ,-0.4472, -7.851,
        -1.724 ,0.4472, -7.851, 1, 0, 0));
    
    scene.addObj(new Triangle (
        -1.276, -0.4472, -6.474,
        -1.106, 0.4472 ,-7,
     -1.724, 0.4472, -6.149,1, 0, 0));
    
    scene.addObj(new Triangle (
        -2.276, -0.4472, -6.149,
        -1.724, 0.4472, -6.149,
        -2.724, 0.4472, -6.474, 1, 0, 0));
    scene.addObj(new Triangle (
        -2.894, -0.4472, -7,
        -2.724, 0.4472, -6.474,
        -2.724, 0.4472, -7.526, 1, 0, 0));
    scene.addObj(new Triangle (
        -2.276, -0.4472, -7.851,
        -2.724 ,0.4472 ,-7.526,
          -1.724, 0.4472, -7.851, 1, 0 ,0));
   scene.addObj(new Triangle (
        -1.276, -0.4472, -7.526,
        -1.724, 0.4472, -7.851,
        -1.106, 0.4472, -7, 1, 0 ,0 ));
    scene.addObj(new Triangle (
        -1.724, 0.4472, -6.149,
        -1.106, 0.4472, -7,
         -2, 1, -7, 1, 0 ,0));
    scene.addObj(new Triangle (
        -2.724, 0.4472, -6.474,
        -1.724, 0.4472, -6.149,
        -2, 1, -7, 1, 0 , 0));
    scene.addObj(new Triangle (
        -2.724, 0.4472, -7.526,
        -2.724 ,0.4472, -6.474,
         -2, 1, -7,1, 0, 0));
    scene.addObj(new Triangle (
        -1.724, 0.4472, -7.851,
        -2.724, 0.4472, -7.526,
        -2 ,1 ,-7,1,0,0));
    scene.addObj(new Triangle (
        -1.106, 0.4472 ,-7,
        -1.724 ,0.4472 ,-7.851,
         -2, 1 ,-7, 1, 0 , 0));
    }
//case 3:
 //   break;
    return scene;
}

