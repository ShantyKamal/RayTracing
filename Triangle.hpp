//
//  Triangle.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#include "Surface.hpp"
#include <string>
class Triangle : public Surface
{
private:
    //member variables
    glm::vec3 normal = glm::vec3(0,0,0);
    std::vector<glm::vec3> verts;
    
    
public:
    //methods
    //constructor
    Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3,
             float r, float g, float b);
    
    glm::vec3 getNormal();
    glm::vec3 getVertex(int num);
    bool intersect(PrimaryRay primary) override;
    glm::vec3 intersectionPt(PrimaryRay primary) override;
    virtual float intersectionDist(PrimaryRay primary) override;
    
    
    virtual ~Triangle();
    
};

#endif /* Triangle_hpp */
