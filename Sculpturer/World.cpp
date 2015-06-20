//
//  World.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include "World.h"
#include <cstdlib>

World::World() {
    
    // color reference: http://zhongguose.com/#tiehui
    bg_color = {55.0/255, 68.0/255, 75.0/255, 1};
    
    init_done = false;
}

World::~World() {
    
}

void World::init() {
    glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    init_done = true;
}

void World::display() {
    if (not init_done)
        init();
    glClear(GL_COLOR_BUFFER_BIT);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_BUFFER_BIT);
    
    for(auto &&obj: objs) {
        obj->display();
    }

    glFlush();
    glutSwapBuffers();
}

void World::reshape(int width, int height) {

}

void World::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 's':
            for(auto &&obj: objs) {
                obj->display_mode = Object::DisplayMode::solid;
            }
            break;
        case 'w':
            for(auto &&obj: objs) {
                obj->display_mode = Object::DisplayMode::wire;
            }
            break;
        default:
            break;
    }
}

void World::workspace() {
    auto cube1 = new Cube();
    cube1->w = 0.5;
    add(cube1);
}

void World::add(Object *o) {
    objs.push_back(o);
}
