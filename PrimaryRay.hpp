//
//  ray.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include <glm/glm.hpp>


class PrimaryRay
{
public:
//member variables
    glm::vec3 origin = glm::vec3(0,0,0);
    glm::vec3 direction = glm::vec3(0,0,0);
    float fov = (55*M_PI) / 180.0;
//methods 
    //contructor
    PrimaryRay();
    virtual ~PrimaryRay();
    
   void setFOV(float fov);
    glm::vec3 directionVector(float i, float j, float w, float h);

};

#endif /* ray_hpp */
