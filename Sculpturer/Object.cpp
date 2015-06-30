//
//  Object.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include "Utils.h"
#include "Object.h"

using namespace std;

// Class Object

std::array<GLfloat, 3> Object::x_axis = {1., 0., 0.};
std::array<GLfloat, 3> Object::y_axis = {0., 1., 0.};
std::array<GLfloat, 3> Object::z_axis = {0., 0., 1.};

void Object::drawAxis(float size)
{
    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    //    glDisable(GL_LIGHTING);
    glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
                                //      the light position when you draw GL_LINES
                                //      and GL_POINTS. remember the matrix.
    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);
    
    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);
    
    // restore default settings
    glPopMatrix();
    //    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}

// Class Cube

GLfloat Object::default_size_factor = 1.0;

void Cube::display() {
//    autoRotate();
//    rotate[0] += 0.3;
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
    glPushMatrix();
    // 3. translate
    glTranslatef(center[0], center[1], center[2]);
    
    glTranslated(moving[0], moving[1], moving[2]);
    // 2. rotate
    glRotated(rotate[0], 1, 0, 0);
    glRotated(rotate[1], 0, 1, 0);
    glRotated(rotate[2], 0, 0, 1);
    // 1. scale
    glScaled(w, h, d);
    // color
    glColor3ubv(color.data());
    switch (display_mode) {
        case Object::DisplayMode::wire:
            drawSystemObject((SystemObjectType)obj_type);
//            glutWireCube(default_size_factor);
            break;
        case Object::DisplayMode::solid:
            drawSystemObject((SystemObjectType)obj_type);
//            glutSolidCube(default_size_factor);
            break;
        default:
            glutWireCube(default_size_factor);
            break;
    }

    glScaled(1/w, 1/h, 1/d);
    drawAxis(1);
    glPopMatrix();
}


