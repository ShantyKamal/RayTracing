//
//  Scene.cpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-23.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#include "Scene.hpp"
#include "Triangle.hpp"
Scene::Scene()
{

}

void Scene::addObj(Surface* objectAddy){
    this->objects.push_back(objectAddy);}

Scene::~Scene() {}
