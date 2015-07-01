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
#include <vector>
#include <GL/freeglut.h>
#include "Utils.h"

//namespace sc {

class Object {
public:
    /* member variables */
    
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
        rotate,
        change,
        material
    };
    enum class ControlType : int {
        x_inc, x_dec, y_inc, y_dec, z_inc, z_dec, error
    };
    std::array<GLfloat, 3>  center;          // center (x,y,z)
    std::array<GLfloat, 3>  nx, ny, nz;      // three axies vector
//    std::array<GLdouble, 3> moving = {0, 0, 0};
    GLdouble                w, h, d;         // x_factor, y_factor, z_factror
    std::array<GLdouble, 4> rotate;
    DisplayMode             display_mode;
    EditMode                edit_mode = EditMode::translate;
    int                     material_sel = 0;
    int                     rgb_channel = 0;
    bool select_flag;
    bool auto_rot_flag;
    bool axis = true;
    Material                material;
    
    /* member functions */
    
    Object() :
    center({0, 0, 0}),
    nx(x_axis), ny(y_axis), nz(z_axis),
    w(1), h(1), d(1),
    display_mode(DisplayMode::solid),
    rotate({0, 0, 1, 0}),
    auto_rot_flag(false)
    {
    }
    
    void initMaterial() {
        material.ambient = {static_cast<GLfloat>(color[0]/255.0), static_cast<GLfloat>(color[1]/255.0), static_cast<GLfloat>(color[2]/255.0), 1};
        material.diffuse = {static_cast<GLfloat>(color[0]/255.0), static_cast<GLfloat>(color[1]/255.0), static_cast<GLfloat>(color[2]/255.0), 1};
        material.emission = {0, 0, 0, 1};
    }
    
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
            {'o', ControlType::y_dec},
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
    void editMaterial(int index) {
        material_sel = index;
        std::array<GLfloat, 4> *mat = nullptr;
        switch (material_sel) {
            case 0: mat = &(material.ambient); break;
            case 1: mat = &(material.diffuse); break;
            case 2: mat = &(material.specular); break;
            default:
                mat = nullptr;
                break;
        }
        if (mat)
            DBMSG("Select material " << mat->at(0) << " " << mat->at(1) << " " << mat->at(2));
    }
    void changeChannel(int chan) {
        rgb_channel = chan;
    }
    void changeMaterial(int dir) {
        DBMSG("change material " << material_sel << " rgb: " << rgb_channel << " dir " << dir);
        auto pos = 1.0/255;
        auto neg = -pos;
        GLfloat* x;
        switch (material_sel) {
            case 0: x = material.ambient.data() + rgb_channel; break;
            case 1: x = material.diffuse.data() + rgb_channel; break;
            case 2: x = material.specular.data() + rgb_channel; break;
            default:
                break;
        }
        *x += (dir > 0) ? pos : neg;
        if (*x > 0.99999999) {
            *x = 1.0;
        }
        if (*x < 0.00000001) {
            *x = 0;
        }
        DBVAR(*x);
    }
    void translateObject(ControlType c_type) {
        auto step = 0.1;
        switch (c_type) {
            case ControlType::x_inc: center[0] += step; break;
            case ControlType::x_dec: center[0] -= step; break;
            case ControlType::y_inc: center[1] += step; break;
            case ControlType::y_dec: center[1] -= step; break;
            case ControlType::z_inc: center[2] += step; break;
            case ControlType::z_dec: center[2] -= step; break;
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
            case SystemObjectType::Cube: glutSolidCube(1); break;
            case SystemObjectType::Sphere: glutSolidSphere(1, 30, 30); break;
            case SystemObjectType::Torus: glutSolidTorus(0.2, 1, 30, 30); break;
            case SystemObjectType::Cone: glutSolidCone(1, 3, 30, 30); break;
            case SystemObjectType::Cylinder: glutSolidCylinder(0.5, 2, 10, 10); break;
            case SystemObjectType::Tetrahedron: glutSolidTetrahedron(); break;
            case SystemObjectType::Octahedron: glutSolidOctahedron(); break;
            case SystemObjectType::Dodecahedron: glutSolidDodecahedron(); break;
            case SystemObjectType::Icosahedron: glutSolidIcosahedron(); break;
            case SystemObjectType::RhombicDodecahedron: glutSolidRhombicDodecahedron(); break;
            case SystemObjectType::Teapot: glutSolidTeapot(1); break;
            case SystemObjectType::Teacup: //glutSolidTeacup(default_size_factor); break;
            case SystemObjectType::Teaspoon: //glutSolidTeaspoon(default_size_factor); break;
            default:
                break;
        }
    }
    SystemObjectType nextType() {
        int val = (int)obj_type;
        if (val < 10) val++;
        if (val == 10) val = 0;
        DBVAR(val);
        return obj_type = (SystemObjectType)val;
    }
};

class Custom: public Object {
public:
    std::vector<GLfloat>        vertices;
    std::vector<GLushort>       faces;
    std::vector<GLfloat>        vert_normal;
    
    Custom(std::vector<GLfloat> vert, std::vector<GLushort> faces, std::vector<GLfloat> vert_normal) :
    vertices(vert), faces(faces), vert_normal(vert_normal) {}

    void displayCustom() {
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glNormalPointer(GL_FLOAT, 0, vert_normal.data());
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        
        glBegin(GL_TRIANGLES);
        for(int i = 0; i < faces.size() / 3; i++) {
            for(int j = 0; j < 3; j++) {
                glArrayElement(faces[i*3+j]);
            }
        }
        glEnd();
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    virtual void display();
};

//}
#endif /* defined(__Sculpturer__Object__) */
