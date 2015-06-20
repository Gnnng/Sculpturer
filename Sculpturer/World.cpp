//
//  World.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include "World.h"

World::World() {

    bg_color = {0, 0, 0, 1};
}

World::~World() {
    
}

void World::init() {
    glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    glColor3f(0, 0, 0);
}

void World::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_BUFFER_BIT);
    
//    glColor3f(1, 0, 0);
//    glBegin(GL_TRIANGLES);
//    glVertex2f(0, 0);
//    glVertex2f(0, 0.5);
//    glVertex2f(0.5, 0);
//    glEnd();
    
    for(auto &&obj: objs) {
        obj->display();
    }

    glFlush();
    glutSwapBuffers();
}

void World::reshape(int width, int height) {

}

void World::keyboard(unsigned char key, int x, int y) {
    
}

void World::workspace() {
    auto cube1 = new Cube();
    cube1->w = 0.5;
    add(cube1);
}

void World::add(Object *o) {
    objs.push_back(o);
}
