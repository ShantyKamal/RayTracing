//
//  Plane.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "Surface.hpp"
#include <string>

class Plane : public Surface
{
private:
    //member variables
    glm::vec3 normal = glm::vec3(0,0,0);
    glm::vec3 nativePoint = glm::vec3(0,0,0);
   
    
public:
 
    //methods
    //contructor with normal vector and a point on the plane
    Plane(glm::vec3 n, glm::vec3 q, float r, float g, float b);
    //constructor with three points on the plane
    Plane(glm::vec3 p, glm::vec3 q, glm::vec3 r);

    glm::vec3 getNormal();
    glm::vec3 getNativePt();
    bool intersect(PrimaryRay primary) override;
    glm::vec3 intersectionPt(PrimaryRay primary) override;
    virtual float intersectionDist(PrimaryRay primary) override;
    
    
     virtual ~Plane();
    
};


#endif /* Plane_hpp */
