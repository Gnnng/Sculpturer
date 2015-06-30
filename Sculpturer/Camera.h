//
//  Camera.h
//  Sculpturer
//
//  Created by Gong Deli on 6/30/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__Camera__
#define __Sculpturer__Camera__

#include "Utils.h"

class Camera {
public:
    enum class TurnDir : int {left, right, up, down};
    enum class MoveDir : int {left, right, forward, rear, up, down};
    
    std::array<GLdouble, 3>     eye;
    GLdouble                    rotate_x, rotate_y, rotate_z;
    GLdouble                    move_step, turn_step;
    bool                        auto_move_flag;
    MoveDir                     last_move_dir;
    GLdouble                    last_move_dist;
    GLdouble                    auto_move_count;

    Camera(std::array<GLdouble, 3> e) :
        eye(e), move_step(0.1), turn_step(0.1),
        rotate_x(0), rotate_y(0), rotate_z(0), auto_move_flag(false) {}
    
    void resetRotate() { rotate_x = rotate_y = rotate_z = 0; }
    void turn(TurnDir dir, GLdouble angle);
    void move(MoveDir dir, GLdouble dist, bool auto_call);
    void autoMove();
    
    void updateLookAt();
};


#endif /* defined(__Sculpturer__Camera__) */
