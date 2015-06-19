//
//  Object.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Object__
#define __Sculpturer__Object__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h> 
#include <OpenGL/gl.h>

#include <array>


class Object {
public:
    Object();
    virtual ~Object() = 0;
    virtual void display() = 0;
    
// Global variables
    static std::array<GLfloat, 3> x_axis, y_axis, z_axis;
    static enum class DisplayMode {
        wire,
        solid
    };
protected:
    GLfloat cx, cy, cz;                         // center (x,y,z)
    std::array<GLfloat, 3> nx, ny, nz;          // three axies vector
    
    DisplayMode display_mode;

};

class Cube :public Object{
public:
    Cube();
    virtual ~Cube();
    virtual void display();

    static GLfloat default_size_factor;
private:
    GLfloat w, h, d;                            // width, height, depth

};



#endif /* defined(__Sculpturer__Object__) */
