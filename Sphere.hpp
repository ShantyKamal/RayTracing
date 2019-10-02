//
//  Sphere.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp
#include <glm/glm.hpp>
#include <stdio.h>
#include <string>

#include "Surface.hpp"

//class definition
class Sphere : public Surface
{
private:
    //member variables
    glm::vec3 origin = glm::vec3(0,0,0);
    float radius;
    
public:
    //methods
    //contructor
    Sphere(float x, float y, float z, float radius, float r, float g, float b);
    float get_radius();
    glm::vec3 getOrigin();
    virtual ~Sphere();
    bool intersect(PrimaryRay primary) override;
    glm::vec3 intersectionPt(PrimaryRay primary) override;

    virtual float intersectionDist(PrimaryRay primary) override;
    
};



#endif /* Sphere_hpp */
