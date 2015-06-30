//
//  Window.h
//  Sculpturer
//
//  Created by Gong Deli on 6/30/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Window__
#define __Sculpturer__Window__

#include <string>
#include "Utils.h"

class Window {
public:
    std::array<GLint, 2>        size;
    std::string                 name = "Sculpturer";
    // Perspective parameters
    GLdouble                    fovy, z_near, z_far;
    //    GLdouble                    aspect; // not used yet


    Window(std::array<GLint, 2> win) :
        size(win), fovy(45), z_near(0.1), z_far(100){}
    
    GLdouble getAspect() { return (GLdouble) size[0]/size[1]; };
};

#endif /* defined(__Sculpturer__Window__) */
