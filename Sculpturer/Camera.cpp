//
//  Camera.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/30/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include <cmath>
#include <cassert>

#include "Camera.h"

void Camera::move(MoveDir dir, GLdouble dist, bool auto_call) {
    if (auto_move_flag) {
        last_move_dir = dir;
        last_move_dist = dist;
        if (auto_call) {

        } else {
//            DBMSG("reset move count");
            auto_move_count = 30;
        }
    }

    auto ang_rad = Utils::toRadian(rotate_y);
    auto sel_f = dir == MoveDir::forward ? 1.0 : -1.0;
    auto sel_l = dir == MoveDir::left ? 1.0 : -1.0;
    auto sel_u = dir == MoveDir::up ? 1.0 : -1.0;
    
    auto sin_v = move_step * std::sinl(ang_rad) * dist;
    auto cos_v = move_step * std::cosl(ang_rad) * dist;

    switch (dir) {
        case MoveDir::forward:
        case MoveDir::rear:
            eye[0] += sin_v * sel_f; eye[2] -= cos_v * sel_f;
            break;
        case MoveDir::left:
        case MoveDir::right:
            eye[0] -= sel_l * cos_v; eye[2] -= sel_l * sin_v;
            break;
        case MoveDir::up:
        case MoveDir::down:
            eye[1] += dist * move_step * sel_u;
        default:
            assert("Should not" != "reach here");
            break;
    }
}

void Camera::autoMove() {
    if (not auto_move_flag)
        return;
    auto_move_count--;
    if (auto_move_count <= 0)
        return;
    move(last_move_dir, last_move_dist, true);
}

void Camera::turn(TurnDir dir, GLdouble angle) {
    switch (dir) {
        case TurnDir::left: rotate_y += angle * turn_step; break;
        case TurnDir::right: rotate_y -= angle * turn_step; break;
        case TurnDir::up: rotate_x += angle * turn_step; break;
        case TurnDir::down: rotate_x -= angle * turn_step; break;
        default:
            break;
    }
}

void Camera::updateLookAt() {
    glLoadIdentity();
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glTranslatef(-eye[0], -eye[1], -eye[2]);
}