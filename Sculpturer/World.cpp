//
//  World.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "utils.h"
#include "World.h"

void World::setDefaultValue() {
/*
 This function init those value those rarely changed in development. Those
 changed a lot are explicitly listed in constructor function
 */
    window_min_size = {800, 600};
}

World::World() {
    setDefaultValue();
    
    // color reference: http://zhongguose.com/#tiehui
    bg_color = {55.0/255, 68.0/255, 75.0/255, 1};
    
    init_done = false;
    
    // view_port parameters
    view_port_size = window_min_size;
    
    DBVAR(view_port_size[0]);
    DBVAR(view_port_size[1]);
    
    auto ratio = (GLfloat) view_port_size[0] / view_port_size[1];
    pers = {45.0, ratio, 0.1, 100};
    
    // look at parameters
    eye = {0, 0, 6};
    look_c = {0, 0, -10};
    
    reshape_factor = 1.0;
}


World::~World() {
    
}

void World::init() {
    if (not init_done)
        glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    init_done = true;
}

void World::display() {
    init();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(eye[0], eye[1], eye[2], look_c[0], look_c[1], look_c[2], 0, 1, 0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_BUFFER_BIT);

    for(auto obj: objs) {
        obj->display();
    }
    
    glFlush();
    glutSwapBuffers();
}

bool World::ensureMinWindow(int width, int height) {
    if (width < window_min_size[0]) {
        glutReshapeWindow(window_min_size[0], height);
        return true;
    }
    if( height < window_min_size[1]) {
        glutReshapeWindow(width, window_min_size[1]);
        return true;
    }
    return false;
}

void World::reshape(int width, int height) {
    init();
    ensureMinWindow(width, height);
    DBMSG("window size updated: " << width << "x" << height);

    view_port_size = {width, height};
    pers[1] = (GLfloat) width / height;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#warning only perspectvie yet, should support ortho mode also
    gluPerspective(pers[0], pers[1], pers[2], pers[3]);

    glMatrixMode(GL_MODELVIEW);
}

void World::keyboard(unsigned char key, int x, int y) {
    init();
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
        case 'q':
            eye[2] += 0.1;
            DBVAR(eye[2]);
            break;
        case 'e':
            eye[2] -= 0.1;
            DBVAR(eye[2]);
            break;
        case 'j':
            reshape_factor -= 0.1;
            DBVAR(reshape_factor);
            break;
        case 'k':
            reshape_factor += 0.1;
            DBVAR(reshape_factor);
            break;
        default:
            break;
    }
}

void World::workspace() {
    init();
    auto cube1 = new Cube();
//    cube1->w = cube1->h = 0.2;
    add(cube1);
}

void World::add(Object *o) {
    objs.push_back(o);
}
