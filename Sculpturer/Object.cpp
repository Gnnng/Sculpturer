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
std::array<GLfloat, 3> Object::y_axis = {0., 1., 0.};
std::array<GLfloat, 3> Object::z_axis = {0., 0., 1.};

// Class Cube

GLfloat Cube::default_size_factor = 1.0;

void Cube::display() {
//    rotate[0] += 0.3;
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    
    // 3. translate
    glTranslatef(center[0], center[1], center[2]);
    // 2. rotate
    glRotated(rotate[0], rotate[1], rotate[2], rotate[3]);
    // 1. scale
    glScaled(w, h, d);
    // color
    glColor3d(1, 0, 0);
    switch (display_mode) {
        case Object::DisplayMode::wire:
            glutWireCube(default_size_factor);
            break;
        case Object::DisplayMode::solid:
            glutSolidCube(default_size_factor);
            break;
        default:
            glutWireCube(default_size_factor);
            break;
    }
}


