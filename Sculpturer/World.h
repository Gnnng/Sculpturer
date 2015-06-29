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

class World {
public:
    std::array<GLint, 2>        window_min_size;
    std::vector<Object *>       objs;
    std::array<GLclampf, 4>     bg_color;
    std::array<GLdouble, 4>     pers;
    std::array<GLint, 2>        view_port_size;
    std::array<GLdouble, 3>     eye;
    std::array<GLdouble, 3>     look_c;
    GLdouble                    reshape_factor;
    bool init_done;

    World();
    ~World();
    
    void setDefaultValue();
    bool ensureMinWindow(int width, int height);
    void init();
    void display();
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    
    void workspace();
    void add(Object *o);
};

#endif /* defined(__Sculpturer__World__) */
