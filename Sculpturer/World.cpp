//
//  World.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "utils.h"
#include "World.h"
#include <sstream>

void World::setDefaultValue() {
/*
 This function init those value those rarely changed in development. Those
 changed a lot are explicitly listed in constructor function
 */
    window_min_size = {800, 600};
    eye_move_step = 0.1;
}

World::World() {
    setDefaultValue();
    
    // color reference: http://zhongguose.com/#tiehui
    bg_color = {55.0/255, 68.0/255, 75.0/255, 1};
    
    init_done = false;
    
    // view_port parameters
    view_port_size = window_min_size;
    
    DBVAR(view_port_size[0]);
    DBVAR(view_port_size[1]);

    auto ratio = (GLfloat) view_port_size[0] / view_port_size[1];
    pers = {45.0, ratio, 0.1, 100};
    
    // look at parameters
    eye = {0, 0, 10};
    look_c = {0, 0, -10};
    look_dir = {0, 0, -10};
    
    reshape_factor = 1.0;
}

void World::init() {
    if (not init_done)
        glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    init_done = true;
}


void World::displayHUD() {
/* HUD - head up display */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    gluOrtho2D(0, view_port_size[0], 0, view_port_size[1]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3d(123/255.0, 161/255.0, 168/255.0);
    glRasterPos2i(10, view_port_size[1] - 20);
    std::string text = "Hello World";
    
    std::stringstream text_in;
    text_in << "x: " << eye[0] << " y: " << eye[1] << " z: " << eye[2] << " rotate_y: " << rotate_y;
    auto font = GLUT_BITMAP_9_BY_15;
    for (int i = 0; i < text_in.str().size(); i++) {
        char c = text_in.str()[i];
        glutBitmapCharacter(font, c);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void World::displayObject() {
    glColor3f(0/255.0, 100/255.0, 95/255.0);
    for(auto obj: objs) obj->display();
}

void World::lookUpdate() {
//    glPushMatrix();
//    glLoadIdentity();
//    glGetDoublev(GL_MODELVIEW, matrix);
//    if (not printed) for(int i = 0; i < 16; i++) {
//        printed = true;
//        DBVAR(matrix[i]);
//    }
//    glPopMatrix();
    
//    gluLookAt(eye[0], eye[1], eye[2], eye[0] + look_dir[0], eye[1] + look_dir[1], eye[2] + look_dir[2], 0, 1, 0);
    
    glLoadIdentity();
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glTranslatef(-eye[0], -eye[1], -eye[2]);

    //    //    glTranslated(-eye_move[0], -eye_move[1], eye_move[2]);

    //    //    glRotated(rotate_x, std::cosl(rotate_y), 0, -std::sinl(rotate_y));
    //    //    glRotated(rotate_z, std::cosl(rotate_x) * std::sinl(rotate_y), std::sinl(rotate_x), std::cosl(rotate_x) * std::cosl(rotate_y));
    //    glTranslatef(-eye[0], -eye[1], -eye[2]);
    //

}

void World::display() {
    init();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);

    lookUpdate();
 

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_BUFFER_BIT);
    
    displayObject();
    displayHUD();
    
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

bool World::ensureMinWindow(int width, int height) {
    if (width < window_min_size[0]) {
        glutReshapeWindow(window_min_size[0], height);
        return true;
    }
    if( height < window_min_size[1]) {
        glutReshapeWindow(width, window_min_size[1]);
        return true;
    }
    return false;
}

void World::reshape(int width, int height) {
    init();
    ensureMinWindow(width, height);
    DBMSG("window size updated: " << width << "x" << height);

    view_port_size = {width, height};
    pers[1] = (GLfloat) width / height;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#warning only perspectvie yet, should support ortho mode also
    gluPerspective(pers[0], pers[1], pers[2], pers[3]);

    glMatrixMode(GL_MODELVIEW);
}

void World::keyboard(unsigned char key, int x, int y) {
    init();
    switch (key) {
        case 27:    exit(0); break;
        case '0':
            for(auto &&obj: objs) {
                obj->display_mode =
                    (obj->display_mode == Object::DisplayMode::solid) ?
                    Object::DisplayMode::wire : Object::DisplayMode::solid;
            }
            break;
        case 's': DBVAR((eye[0] -= eye_move_step * sinl(toRadian(rotate_y)), eye[2] += eye_move_step * cosl(toRadian(rotate_y)))); break;
        case 'w':
            DBVAR((eye[0] += eye_move_step * sinl(toRadian(rotate_y)), eye[2] -= eye_move_step * cosl(toRadian(rotate_y)))); break;
        case 'a': DBVAR((eye[0] -= eye_move_step * cosl(toRadian(rotate_y)), eye[2] -= eye_move_step * sinl(toRadian(rotate_y)))); break;
        case 'd': DBVAR((eye[0] += eye_move_step * cosl(toRadian(rotate_y)), eye[2] += eye_move_step * sinl(toRadian(rotate_y)))); break;
        case 'q': DBVAR((eye[1] += eye_move_step)); break; // up
        case 'e': DBVAR((eye[1] -= eye_move_step)); break; // down
        case 'y': rotate_y = 45; break;
//        case 's': DBVAR((eye_move[2] -= eye_move_step)); break;
//        case 'w': DBVAR((eye_move[2] += eye_move_step)); break;
//        case 'a': DBVAR((eye_move[0] -= eye_move_step)); break;
//        case 'd': DBVAR((eye_move[0] += eye_move_step)); break;
//        case 'q': DBVAR((eye_move[1] += eye_move_step)); break;
//        case 'e': DBVAR((eye_move[1] -= eye_move_step)); break;
        case ' ': rotate_x = rotate_y = rotate_z = 0; break;
        default:
            break;
    }
}

void World::mouse(int button, int state, int x, int y) {
    switch ((SC_MOUSE)button) {
        case SC_MOUSE::swipe_u:
            DBVAR((rotate_x += 0.1));
            break;
        case SC_MOUSE::swipe_d:
            DBVAR((rotate_x -= 0.1));
            break;
        case SC_MOUSE::swipe_r:
            DBVAR((rotate_y -= 0.1));
            break;
        case SC_MOUSE::swipe_l:
            DBVAR((rotate_y += 0.1));
            break;
        default:
            break;
    }
}

void World::workspace() {
    init();
    auto ob1 = new Cube();
    ob1->color = {0, 110, 95};
    add(ob1);
}


