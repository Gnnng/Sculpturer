//
//  Object.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Object__
#define __Sculpturer__Object__

#include <map>
#include <GL/freeglut.h>
#include "Utils.h"

class Object {
public:
    static std::array<GLfloat, 3> x_axis, y_axis, z_axis;
    static GLfloat default_size_factor;
    
    std::array<GLubyte, 3>  color;
    enum class DisplayMode : int {
        wire,
        solid
    };
    enum class EditMode : int {
        translate,
        scale,
        rotate
    };
    enum class ControlType : int {
        x_inc, x_dec, y_inc, y_dec, z_inc, z_dec, error
    };
    std::array<GLfloat, 3>  center;          // center (x,y,z)
    std::array<GLfloat, 3>  nx, ny, nz;      // three axies vector
    std::array<GLdouble, 3> moving = {0, 0, 0};
    GLdouble                w, h, d;         // x_factor, y_factor, z_factror
    std::array<GLdouble, 4> rotate;
    DisplayMode             display_mode;
    EditMode                edit_mode;
    bool select_flag;
    bool auto_rot_flag;
    
    Object() :
    center({0, 0, 0}),
    nx(x_axis), ny(y_axis), nz(z_axis),
    w(1), h(1), d(1),
    display_mode(DisplayMode::solid),
    rotate({0, 0, 1, 0}),
    auto_rot_flag(false)
    {}

    bool isSelected() { return select_flag; }
    void autoRotate() { if (auto_rot_flag) rotate[0] += 1; };
    void drawAxis(GLfloat size);
    virtual ~Object() {}
    virtual void display() = 0;
    void keyboard(int key) {
        static std::map<int, ControlType> key_map = {
            {'i', ControlType::z_dec},
            {'k', ControlType::z_inc},
            {'l', ControlType::x_inc},
            {'j', ControlType::x_dec},
            {'u', ControlType::y_inc},
            {'o', ControlType::y_dec}
        };
        
        auto control = key_map[key];
        switch (edit_mode) {
            case EditMode::translate: translateObject(control); break;
            case EditMode::scale: scaleObject(control); break;
            case EditMode::rotate: rotateObject(control); break;
            default:
                break;
        }
    }
    void translateObject(ControlType c_type) {
        auto step = 0.1;
        switch (c_type) {
            case ControlType::x_inc: moving[0] += step; break;
            case ControlType::x_dec: moving[0] -= step; break;
            case ControlType::y_inc: moving[1] += step; break;
            case ControlType::y_dec: moving[1] -= step; break;
            case ControlType::z_inc: moving[2] += step; break;
            case ControlType::z_dec: moving[2] -= step; break;
            default:
                break;
        }
    }
    void rotateObject(ControlType c_type) {
        auto step = 1.0;
        switch (c_type) {
            case ControlType::x_inc: rotate[0] += step; break;
            case ControlType::x_dec: rotate[0] -= step; break;
            case ControlType::y_inc: rotate[1] += step; break;
            case ControlType::y_dec: rotate[1] -= step; break;
            case ControlType::z_inc: rotate[2] += step; break;
            case ControlType::z_dec: rotate[2] -= step; break;
            default:
                break;
        }
    }
    void scaleObject(ControlType c_type) {
        auto step = 0.1;
        switch (c_type) {
            case ControlType::x_inc: w += step; break;
            case ControlType::x_dec: w -= step; break;
            case ControlType::y_inc: h += step; break;
            case ControlType::y_dec: h -= step; break;
            case ControlType::z_inc: d += step; break;
            case ControlType::z_dec: d -= step; break;
            default:
                break;
        }
    }
};

class Cube :public Object{
public:
    enum class SystemObjectType : int {
        Cube, Sphere, Torus, Cone, Cylinder, Tetrahedron, Octahedron, Dodecahedron,
        Icosahedron, RhombicDodecahedron, Teapot, Teacup, Teaspoon
    };
    SystemObjectType obj_type = SystemObjectType::Cube;
    Cube() { color = {86, 149, 151}; }
    Cube(GLubyte r, GLubyte g, GLubyte b) { color = {r, g, b}; }
    virtual void display();
    
    void drawSystemObject(SystemObjectType obj) {
        switch (obj) {
            case SystemObjectType::Cube: glutSolidCube(default_size_factor); break;
            case SystemObjectType::Sphere: glutSolidSphere(default_size_factor, 10, 10); break;
            case SystemObjectType::Torus: glutSolidTorus(default_size_factor, 4, 3, 5); break;
            case SystemObjectType::Cone: glutSolidCone(default_size_factor, 3, 3, 5); break;
            case SystemObjectType::Cylinder: glutSolidCylinder(1, 5, 10, 10); break;
            case SystemObjectType::Tetrahedron: glutSolidTetrahedron(); break;
            case SystemObjectType::Octahedron: glutSolidOctahedron(); break;
            case SystemObjectType::Dodecahedron: glutSolidDodecahedron(); break;
            case SystemObjectType::Icosahedron: glutSolidIcosahedron(); break;
            case SystemObjectType::RhombicDodecahedron: glutSolidRhombicDodecahedron(); break;
            case SystemObjectType::Teapot: glutSolidTeapot(default_size_factor); break;
            case SystemObjectType::Teacup: //glutSolidTeacup(default_size_factor); break;
            case SystemObjectType::Teaspoon: //glutSolidTeaspoon(default_size_factor); break;
            default:
                break;
        }
    }
    SystemObjectType nextType() {
        int val = (int)obj_type;
        if (val < 11) val++;
        if (val == 11) val = 0;
        DBVAR(val);
        return obj_type = (SystemObjectType)val;
    }
};


#endif /* defined(__Sculpturer__Object__) */
