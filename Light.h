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

struct Material {
    static std::array<GLfloat, 4> no_color, white_diffuse;
    std::array<GLfloat, 4>   ambient, diffuse, specular, shininess, emission;
};

class Light {
public:
    GLuint              id = -1;     // OpenGL light id (0~7), -1 = not init
    Material            material;
    std::array<GLfloat, 4>  position;

    void display();

    GLuint toGLID(GLuint id) { return (0x4000 | (id & 0x0007)); }

    Light(){
        material.ambient = Material::no_color;
        material.diffuse = Material::no_color;
        material.specular = Material::no_color;
        material.shininess = Material::no_color;
        position = {5, 5, 5, 1};
    }
    void open() {
        glLightfv(toGLID(id), GL_AMBIENT, material.ambient.data());
        glLightfv(toGLID(id), GL_DIFFUSE, material.diffuse.data());
        glLightfv(toGLID(id), GL_SPECULAR, material.specular.data());
        glLightfv(toGLID(id), GL_POSITION, position.data());
        glEnable(GL_LIGHTING);
        glEnable(toGLID(id));
    }
    void close() { glDisable(toGLID(id)); glDisable(GL_LIGHTING);}
};

#endif /* defined(__Sculpturer__Light__) */
