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

void Camera::default_move_control(int key) {
    switch (key) {
        case 'w': move(MoveDir::forward, 1); break;
        case 's': move(MoveDir::rear, 1); break;
        case 'a': move(MoveDir::left, 1); break;
        case 'd': move(MoveDir::right, 1); break;
        case 'q': move(MoveDir::up, 1); break;
        case 'e': move(MoveDir::down, 1); break;
        case ' ': reset_rotate(); break;
        default:
            break;
    }
}

void Camera::move(MoveDir dir, GLdouble dist) {
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