//
//  Surface.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-23.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef Surface_hpp
#define Surface_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <string>
#include "PrimaryRay.hpp"

class Surface{
protected:
    glm::vec3 color = glm::vec3(1,1,1);
    std::string material; 
    
public:

    Surface();
    virtual ~Surface();
    void setColor(float r, float g, float b);
    glm::vec3 getColor();
    //glm::vec3 normalize(glm::vec3 vector);
    //abstract methods?
    virtual bool intersect(PrimaryRay primary);
    virtual glm::vec3 intersectionPt(PrimaryRay primary);
    virtual float intersectionDist(PrimaryRay primary);
   // glm::vec3 cameraToWindow(float x,  float y, float z);
};

#endif /* Surface_hpp */
