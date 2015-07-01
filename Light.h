//
//  Light.h
//  Sculpturer
//
//  Created by Gong Deli on 7/1/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Light__
#define __Sculpturer__Light__

#include <array>
#include "Utils.h"
#include "Object.h"

class Light : public Object {
public:
    GLuint              id = -1;     // OpenGL light id (0~7), -1 = not init
    Material            material;
    std::array<GLfloat, 4>  position;

    Light(){
        material.ambient = {0, 0, 0, 1};
        material.diffuse = {0, 0, 0, 1};
        material.specular = {0, 0, 0, 1};
        material.shininess = {0, 0, 0, 1};
        position = {5, 5, 5, 1};
        center = {5, 5, 5};
    }
    GLuint toGLID(GLuint id) { return (0x4000 | (id & 0x0007)); }
    void open() {
        glLightfv(toGLID(id), GL_AMBIENT, material.ambient.data());
        glLightfv(toGLID(id), GL_DIFFUSE, material.diffuse.data());
        glLightfv(toGLID(id), GL_SPECULAR, material.specular.data());
        glLightfv(toGLID(id), GL_POSITION, position.data());
        glEnable(GL_LIGHTING);
        glEnable(toGLID(id));
    }
    void close() { glDisable(toGLID(id)); glDisable(GL_LIGHTING);}
    virtual void display() {
        glPushMatrix();
        glTranslated(center[0], center[1], center[2]);
        position = {center[0], center[1], center[2], 1};
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glColorMaterial(GL_FRONT, GL_EMISSION);
        glColor3ubv(color.data());
        glutSolidSphere(0.5, 30, 30);
        glDisable(GL_LIGHTING);
        drawAxis(1);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
};

#endif /* defined(__Sculpturer__Light__) */
