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
    enum class SC_MOUSE : int {
        button_l, // 0
        button_m, // not captured
        button_r,
        swipe_d,
        swipe_u,
        swipe_r,
        swipe_l
    };

    std::array<GLint, 2>        window_min_size;
    std::vector<Object *>       objs;
    std::array<GLclampf, 4>     bg_color;
    std::array<GLdouble, 4>     pers;
    std::array<GLint, 2>        view_port_size;
    std::array<GLdouble, 3>     eye;
    std::array<GLdouble, 3>     look_c;
    std::array<GLdouble, 3>     look_dir;
    GLdouble                    reshape_factor;
    GLdouble                    eye_move_step;
    std::array<GLdouble, 3>     eye_move;
    GLdouble                    rotate_x, rotate_y, rotate_z;
    bool init_done;

    World();
    ~World();
    
    void displayObject();
    void displayHUD();
    void lookUpdate();
    void setDefaultValue();
    bool ensureMinWindow(int width, int height);
    void init();
    void display();
    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    GLdouble toDegree(GLdouble rad) { return rad / (3.14159265358/180); }
    GLdouble toRadian(GLdouble deg) { return deg * 3.14159265358 / 180; }
    void workspace();
    void add(Object *o) { objs.push_back(o); }
};

#endif /* defined(__Sculpturer__World__) */
