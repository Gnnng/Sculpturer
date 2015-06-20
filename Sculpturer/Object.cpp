//
//  Object.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include "Object.h"

using namespace std;

std::array<GLfloat, 3> Object::x_axis = {1., 0., 0.};
std::array<GLfloat, 3> Object::y_axis = {1., 0., 0.};
std::array<GLfloat, 3> Object::z_axis = {1., 0., 0.};

Object::Object() {
    cx = cy = cz = 0;
    nx = x_axis;
    ny = y_axis;
    nz = z_axis;
    display_mode = DisplayMode::solid;
}

void Object::display() {
    
}

Object::~Object() {
    
}
// Class Cube

GLfloat Cube::default_size_factor = 1.0;

Cube::Cube() {
    w = h = d = 1;
}

Cube::~Cube() {
    
}

void Cube::display() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // 3. translate
    glTranslatef(cx, cy, cz);
    // 2. rotate
    glRotatef(0, 0, 0, 0);
    // 1. scale
    glScalef(w, h, d);

    switch (display_mode) {
        case Object::DisplayMode::wire:
            glutWireCube(1.0);
            break;
        case Object::DisplayMode::solid:
            glutSolidCube(1.0);
            break;
        default:
            glutWireCube(1.0);
            break;
    }
    glPopMatrix();
}


