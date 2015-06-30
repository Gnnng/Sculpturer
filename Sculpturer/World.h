//
//  World.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__World__
#define __Sculpturer__World__

#include <vector>
#include <functional>

#include "Utils.h"
#include "Camera.h"
#include "Object.h"
#include "Window.h"

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
    
    std::vector<Object *>       objs;
    std::array<GLclampf, 4>     bg_color;
    Camera                      camera;
    Window                      window;
    GLint                       update_time;
    bool init_done;

    World();
    ~World();
    
    void displayObject();
    void displayHUD();
    void init();
    void display();
    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    void update();
    static void auto_update(int id);
    
    void workspace();
    void add(Object *o) { objs.push_back(o); }
    void drawGrid(GLfloat size, GLfloat step);
};

#endif /* defined(__Sculpturer__World__) */
