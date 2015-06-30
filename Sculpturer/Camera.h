//
//  Camera.h
//  Sculpturer
//
//  Created by Gong Deli on 6/30/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Camera__
#define __Sculpturer__Camera__

#include <stdio.h>
#include <array>
#include <GL/freeglut.h>

class Camera {
public:
    enum class TurnDir : int {left, right, up, down};
    enum class MoveDir : int {left, right, forward, rear, up, down};
    
    std::array<GLdouble, 3>     eye;
    GLdouble                    rotate_x, rotate_y, rotate_z;
    GLdouble                    move_step, turn_step;
    
    Camera(std::array<GLdouble, 3> e) :
        eye(e), move_step(0.1), turn_step(0.1),
        rotate_x(0), rotate_y(0), rotate_z(0) {}
    
    void default_move_control(int key);
    void reset_rotate() { rotate_x = rotate_y = rotate_z = 0; }
    void turn(TurnDir dir, GLdouble angle);
    void move(MoveDir dir, GLdouble dist);
    void updateLookAt();
};


#endif /* defined(__Sculpturer__Camera__) */
