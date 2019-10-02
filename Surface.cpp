//
//  Surface.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-23.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "Surface.hpp"

Surface::Surface(){}



void Surface::setColor(float r, float g, float b)
{
    this->color = glm::vec3(r, g, b);
}

glm::vec3 Surface::getColor()
{
    return this->color;
}


float Surface::intersectionDist(PrimaryRay primary) {return 0;}
bool Surface::intersect(PrimaryRay primary){ return false;}
glm::vec3 Surface::intersectionPt(PrimaryRay primary){return glm::vec3(0,0,0);}

Surface::~Surface() {}
