//
//  Plane.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "Plane.hpp"
#include <iostream>

glm::vec3 Plane::getNormal() { return this->normal; }
glm::vec3 Plane::getNativePt() { return this->nativePoint; }

float Plane::intersectionDist(PrimaryRay primary)
{
    glm::vec3 d = primary.direction;
    glm::vec3 n = this->getNormal();
    glm::vec3 q = this->getNativePt();
    
    float t = (glm::dot(q, n)) / (glm::dot(d, n));
    //if (t>0)
        return t;
    //else
    //    return INFINITY;
   
}

bool Plane::intersect(PrimaryRay primary)
{
    //viewRay direction vector:
    glm::vec3 d = primary.direction;
    glm::vec3 n = (this->getNormal());
    
    glm::vec3 q = this->getNativePt();
    q = glm::normalize(q);
    float denom = glm::dot( d , n);
    if(std::fabs(denom)<=0.0) return false;
    //b/c plane is parallel or disjoint to camera ray, no intersection
    else {return true;
        float t = (glm::dot(q, n)) / denom;
        if (t<=0) return false;
        else
            return true;
}
}

glm::vec3 Plane::intersectionPt(PrimaryRay primary)
{
    glm::vec3 d = primary.direction;
    glm::vec3 n = this->getNormal();
    glm::vec3 q = this->getNativePt();
    
    float t = (glm::dot(q, n)) / (glm::dot(d, n));
    //hitPoint = t*[d]
   
    return glm::vec3(d.x*t, d.y*t, d.z*t);
}


Plane::Plane(glm::vec3 n, glm::vec3 q, float r, float g, float b)
{
    this->normal = n;
    this->nativePoint = q;
    this->setColor(r, g, b);
}
Plane::Plane(glm::vec3 p, glm::vec3 q, glm::vec3 r)
{
    glm::vec3 pq = q - p;
    glm::vec3 pr = r - p;
    glm::vec3 normal = glm::cross(pq, pr);
    //normalize the normal
    this->normal = glm::normalize(normal);
    this->nativePoint = p;
}



Plane::~Plane() {}
