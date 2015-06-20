//
//  World.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__World__
#define __Sculpturer__World__

#include <stdio.h>
#include <vector>
#include "Object.h"
#include <functional>

using namespace std;

class World {
public:
    World();
    ~World();
    
    void init();
    void display();
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    
    void workspace();
    void add(Object *o);
    
private:
    vector<Object *> objs;
    std::array<GLclampf, 4> bg_color;
    bool init_done;
};

#endif /* defined(__Sculpturer__World__) */
