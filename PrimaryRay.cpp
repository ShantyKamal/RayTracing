//
//  ray.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "PrimaryRay.hpp"
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>

PrimaryRay::PrimaryRay(){}

void PrimaryRay::setFOV(float fov)    {this->fov = fov;}

PrimaryRay::~PrimaryRay() {}


//given x and y in image coordinates, compute view ray from camera origin to pixel centre
glm::vec3 PrimaryRay::directionVector(float i, float j, float w, float h)
{
    float x, y ,z;
    float focalLength = (h*0.5)/tan(this->fov *0.5);
    z = - focalLength;
    
    if (j>(h*0.5))
        y = ((-h*0.5)+0.5+j);
    else if(j<(h*0.5))
        y = ((-h*0.5)+0.5+j);
    else
        y = 0;
    
    if (i>(w*0.5))
        x = ((-w*0.5) + 0.5 + i);
    else if (i < (w*0.5))
        x = ((-w*0.5) + 0.5 + i);
    else
        x = 0;

    //normalize the direction vector now
    this->direction = glm::normalize(glm::vec3(x,y,z));
   
    return this->direction;
}


