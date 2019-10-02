//
//  Scene.hpp
//  Boilerplate
//
//  Created by Shanty 1 on 2018-11-23.
//  Copyright © 2018 University of Calgary. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Surface.hpp"
#include "Plane.hpp"
#include <memory>

class Scene {
public:
   // std::vector<Surface *> objects;
    std::vector<Surface *> objects;
   

    Scene();
    virtual ~Scene();
    
    void addObj(Surface* obj);
};

#endif /* Scene_hpp */
