//
//  Object.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Object__
#define __Sculpturer__Object__

#include "Utils.h"


class Object {
public:
    static std::array<GLfloat, 3> x_axis, y_axis, z_axis;
    std::array<GLubyte, 3>  color;
    enum class DisplayMode : int {
        wire,
        solid
    };
    std::array<GLfloat, 3> center;              // center (x,y,z)
    std::array<GLfloat, 3> nx, ny, nz;          // three axies vector
    GLdouble w, h, d;                           // x_factor, y_factor, z_factror
    std::array<GLdouble, 4> rotate;
    DisplayMode display_mode;
    bool select_flag;
    
    Object() :
    center({0, 0, 0}),
    nx(x_axis), ny(y_axis), nz(z_axis),
    w(1), h(1), d(1),
    display_mode(DisplayMode::solid),
    rotate({0, 0, 1, 0})
    {}
    
    bool isSelected() { return select_flag; }
    
    void drawAxis(GLfloat size);
    virtual ~Object() {}
    virtual void display() = 0;
};

class Cube :public Object{
public:
    static GLfloat default_size_factor;         //
    
    virtual void display();
};



#endif /* defined(__Sculpturer__Object__) */
