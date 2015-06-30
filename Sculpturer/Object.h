//
//  Object.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Object__
#define __Sculpturer__Object__

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
    std::array<GLfloat, 3> center;              // center (x,y,z)
    std::array<GLfloat, 3> nx, ny, nz;          // three axies vector
    GLdouble w, h, d;                           // x_factor, y_factor, z_factror
    std::array<GLdouble, 4> rotate;
    DisplayMode display_mode;
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
