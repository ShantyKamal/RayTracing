//
//  Triangle.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-20.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "Triangle.hpp"
#include "Plane.hpp"

float Triangle::intersectionDist(PrimaryRay primary)
{
     Plane triPlane = Plane(this->getVertex(0), this->getVertex(1), this->getVertex(2));
    float t = triPlane.intersectionDist(primary);
    return t; 
}

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3,
                   float r, float g, float blue)
{
    glm::vec3 a = glm::vec3(x1, y1, z1);
    glm::vec3 b = glm::vec3(x2, y2, z2);
    glm::vec3 c = glm::vec3(x3, y3, z3);
    //takes in 3 vertices of a triangle 
    this->verts.push_back(a); this->verts.push_back(b);
    this->verts.push_back(c);
    
    //normal of plane the triangle lies on 
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;                                   //normalize before use or?
    glm::vec3 normal = glm::cross(ab, ac);
    //normalize the normal
    this->normal = glm::normalize(normal);
    this->setColor(r, g, blue);
}


bool Triangle::intersect(PrimaryRay primary)
{
    //1st check if point intersects the plane on which the triangle lies on
    Plane triPlane = Plane(this->getVertex(0), this->getVertex(1), this->getVertex(2));
    if (!(triPlane.intersect(primary)))
        return false;
    
    else 
    {
        //find P = intersection point on plane
        glm::vec3 p = triPlane.intersectionPt(primary);
        //check if P lies inside triangle
        glm::vec3 n = this->getNormal();
        //vertices of triangle
        glm::vec3 a = this->getVertex(0);
        glm::vec3 b = this->getVertex(1);
        glm::vec3 c = this->getVertex(2);
        //sides of triangle
        glm::vec3 ab = b - a;
        glm::vec3 bc = c - b;
        glm::vec3 ca = a - c;
        //vectors from triangle vertices to point P
        glm::vec3 aP = p - a;
        glm::vec3 bP = p - b;
        glm::vec3 cP = p - c;
        //dot product of an angle > 90 will be negative
        return (  (glm::dot(n, glm::cross(ab, aP)) >0 )
                &&(glm::dot(n, glm::cross(bc, bP)) >0 )
                &&(glm::dot(n, glm::cross(ca, cP)) >0 )  );
    }
}

glm::vec3 Triangle::intersectionPt(PrimaryRay primary)
{
    Plane triPlane = Plane(this->getVertex(0), this->getVertex(1), this->getVertex(2));
    //Plane triPlane = Plane(this->getNormal(), this->getVertex(0));
    glm::vec3 p = triPlane.intersectionPt(primary);
    return p;
}





glm::vec3 Triangle::getNormal() {return this->normal;}

glm::vec3 Triangle::getVertex(int num) { return this->verts[num]; }

Triangle::~Triangle(){}
