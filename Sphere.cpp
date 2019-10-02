//
//  Sphere.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "Surface.hpp"
#include "Sphere.hpp"
#include <glm/gtc/matrix_transform.hpp>

float Sphere::intersectionDist(PrimaryRay primary)
{
    glm::vec3 d = primary.direction;
    glm::vec3 sOrigin = this->origin;
    float rSqrd = (this->radius)*(this->radius);
    float a = glm::dot(d, d);
    float b = glm::dot(glm::vec3(d.x*2, d.y*2, d.z*2), sOrigin);
    float c = glm::dot(-sOrigin, -sOrigin) - rSqrd;
    //using quadratic formula find t
    float t1 = ((-b) + sqrtf((b*b)-(4*a*c))) / (2*a);
    float t2 = ((-b) - sqrtf((b*b)-(4*a*c))) / (2*a);
    float t = fmax(t1, t2);
    return t; 
}


glm::vec3 Sphere::intersectionPt(PrimaryRay primary)
{
    glm::vec3 d = primary.direction;
    glm::vec3 sOrigin = this->origin;
    sOrigin = glm::normalize(sOrigin);
    float rSqrd = (this->radius)*(this->radius);
    float a = glm::dot(d, d);
    float b = glm::dot(glm::vec3(d.x*2, d.y*2, d.z*2), sOrigin);
    float c = glm::dot(-sOrigin, -sOrigin) - rSqrd;
    //using quadratic formula find t
    float discriminant = ((b*b) - (4*a*c));
    float numeratorP = ((-b) + sqrtf(discriminant));
    float numeratorN = ((-b) - sqrtf(discriminant));
    float t1 = numeratorP / (2*a);
    float t2 = numeratorN / (2*a);
    float t;
    if ( (t1>0) && (t2>0))
         t = fmin(t1, t2);
    else
        t = fmax(t1, t2);
    //hitPoint = t*[d]
    return glm::vec3(d.x*t, d.y*t, d.z*t);
}



bool Sphere::intersect(PrimaryRay primary)
{
    glm::vec3 d = primary.direction;
    glm::vec3 sOrigin = this->origin;
    sOrigin = glm::normalize(sOrigin);
    float rSqrd = (this->radius)*(this->radius);
    float a = glm::dot(d, d);
    float b = glm::dot(glm::vec3(d.x*2, d.y*2, d.z*2), sOrigin);
    float c = (glm::dot(-sOrigin, -sOrigin)) - rSqrd;
    float discriminant = ((b*b) - (4*a*c));
    //if discriminant is negative return false
    if( discriminant < 0)
        return false;
    //check if a positive t-value is possible
    else
         {
             float numeratorP = ((-b) + sqrtf(discriminant));
             float numeratorN = ((-b) - sqrtf(discriminant));
             if ( ((numeratorP/(2*a)) < 0)  && ((numeratorN/(2*a)) < 0) )
                 return true;
             else
                 return false;
         }
}


Sphere::Sphere(float x, float y, float z, float radius, float r, float g, float b)
{

    this->origin = glm::vec3(x,y,z);
    this->radius = radius;
    this->setColor(r, g, b);
}
float Sphere::get_radius()
{
    return this->radius;
}


glm::vec3 Sphere::getOrigin()
{
    return this->origin; 
}



Sphere::~Sphere() {}
