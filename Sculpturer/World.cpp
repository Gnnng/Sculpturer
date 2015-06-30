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
#include <sstream>
#include <cassert>

#include "World.h"


World::World() : camera({0, 0, 0}), window({800, 600}) {
    // color reference: http://zhongguose.com/#tiehui
    bg_color = {55.0/255, 68.0/255, 75.0/255, 1};
    
    // init flag reset
    init_done = false;
    
    // init window
    window.fovy = 45;
    
    // init camera
    camera.eye[2] = 10;
    camera.eye[1] = 4;
    camera.rotate_x = 30;
    camera.move_step = 0.05;
    camera.auto_move_flag = true;
    
    // init auto update
    update_time = 15;
}

void World::init() {
    if (not init_done)
        glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    init_done = true;
}

void getFPS()
{
    static int frame = 0, time, timebase = 0;
    static char buffer[256];
    
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        sprintf(buffer,"FPS:%4.2f", frame*1000.0/(time-timebase));
        timebase = time;
        frame = 0;
    }

    glutSetWindowTitle(buffer);
}

void World::displayHUD() {
/* HUD - head up display */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    gluOrtho2D(0, window.size[0], 0, window.size[1]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
//    glColor3d(123/255.0, 161/255.0, 168/255.0);
    glColor3ub(255, 255, 255);
    glRasterPos2i(10, window.size[1] - 20);
    std::string text = "Hello World";
    
    std::stringstream text_in;
    auto eye = camera.eye;
    auto rotate_y = camera.rotate_y;
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
    glMatrixMode(GL_MODELVIEW);

    for(auto obj: objs) {
        assert(pick_map.find(obj) != pick_map.end());
        glPushName(pick_map[obj]);
//        DBVAR(pick_map[obj]);
        if (pick_id == pick_map[obj]){
            DBMSG("select " << pick_id);
        }
//        obj->display();
        if (pick_id == pick_map[obj]) {
            glClearStencil(0);
            glClear(GL_STENCIL_BUFFER_BIT);
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 1, -1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            obj->display();
            glStencilFunc(GL_NOTEQUAL, 1, -1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glLineWidth(10);
            glPolygonMode(GL_FRONT, GL_LINE);
            auto old = obj->color;
            obj->color = {255, 0, 0};
            obj->display();
            obj->color = old;
            glDisable(GL_STENCIL_TEST);
        } else {
            glLineWidth(1);
            glClear(GL_STENCIL_BUFFER_BIT);
            obj->display();
        }
        glPopName();
    }
}


void World::display() {
    init();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);

    camera.updateLookAt();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    displayObject();
//    displayHUD();
//    drawGrid(10, 1);
    glFlush();
    glutSwapBuffers();
//    getFPS();
}

void World::reshape(int width, int height) {
    window.size = {width, height};
    init();
    DBMSG("window size updated: "
          << window.size[0] << "x" << window.size[1]);
    
    glViewport(0, 0, window.size[0], window.size[1]);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#warning only perspectvie yet, should support ortho mode also
    gluPerspective(window.fovy, window.getAspect(), window.z_near, window.z_far);

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
        /* use default camera controy */
        case 'w': camera.move(Camera::MoveDir::forward, 1, false); break;
        case 's': camera.move(Camera::MoveDir::rear, 1, false); break;
        case 'a': camera.move(Camera::MoveDir::left, 1, false); break;
        case 'd': camera.move(Camera::MoveDir::right, 1, false); break;
        case 'q': camera.move(Camera::MoveDir::up, 1, false); break;
        case 'e': camera.move(Camera::MoveDir::down, 1, false); break;
        case ' ': camera.resetRotate(); break;
        case '1': camera.auto_move_flag = camera.auto_move_flag ? false : true;
        default:
            break;
    }
}

void World::mouse(int button, int state, int x, int y) {
//    DBVAR(button); DBVAR(state);
    switch ((ButtonType)button) {
        case ButtonType::button_l:
            switch ((ButtonState)state) {
                case ButtonState::down: pickObject(x, y);
                    break;
                case ButtonState::up: pick_id = 0;
                    break;
                default:
                    break;
            }
            break;
//        case ButtonType::button_r:
        case ButtonType::swipe_u: camera.turn(Camera::TurnDir::up, 1); break;
        case ButtonType::swipe_d: camera.turn(Camera::TurnDir::down, 1); break;
        case ButtonType::swipe_l: camera.turn(Camera::TurnDir::left, 1); break;
        case ButtonType::swipe_r: camera.turn(Camera::TurnDir::right, 1); break;
        default:
            break;
    }
}

void World::pickObject(int x, int y) {
    {
        // start picking
        GLint viewport[4];
        glSelectBuffer((GLsizei)sel_buf.size(), sel_buf.data());
        glRenderMode(GL_SELECT);
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(x, viewport[3] - y, sel_area_size[0], sel_area_size[1], viewport);
        gluPerspective(window.fovy, window.getAspect(), window.z_near, window.z_far);
        glMatrixMode(GL_MODELVIEW);
        glInitNames();
        DBMSG("Picking start");
    }
    
    display();
    
    {
        // finish picking
        DBMSG("Picking finished");
        int hits;
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glFlush();

        hits = glRenderMode(GL_RENDER);
        if (hits != 0) {
            //            processHits(hits, selectBuf);
            DBMSG("Pick hits = " << hits);
            GLuint min = 0xffffffff;
            GLuint *ptr = sel_buf.data();
            for (auto i = 0; i < hits; i++) {
                int size = *ptr;
                ptr++;
                DBVAR(*ptr);
                DBVAR(*(ptr+2));
                if (*ptr < min) {
                    min = *ptr;
                    pick_id = *(ptr + 2);
                }
                ptr += size + 2;
            }
            DBVAR(pick_id);
        }

    }
}


void World::workspace() {
    init();
    auto ob1 = new Cube();
    ob1->center = {2, 0, 2};
    ob1->auto_rot_flag = true;
    add(ob1);
    
    auto ob2 = new Cube(219, 206, 84);
    ob2->center = {0, 0, -3};
//    ob2->auto_rot_flag = false;
    add(ob2);
}

void World::auto_update(int id) {
    globe->camera.autoMove();
    glutPostRedisplay();
    glutTimerFunc(globe->update_time, World::auto_update, 0);
}

void World::drawGrid(GLfloat size, GLfloat step) {
    // disable lighting
    //        glDisable(GL_LIGHTING);
    
    glBegin(GL_LINES);
    
    glColor3f(0.5f, 0.5f, 0.5f);
    for(float i=step; i <= size; i+= step)
    {
        glVertex3f(-size, 0,  i);   // lines parallel to X-axis
        glVertex3f( size, 0,  i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f( size, 0, -i);
        
        glVertex3f( i, 0, -size);   // lines parallel to Z-axis
        glVertex3f( i, 0,  size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0,  size);
    }
    
    // x-axis
    glVertex3f(-size, 0, 0);
    glVertex3f( size, 0, 0);
    
    // z-axis
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0,  size);
    
    glEnd();
    
    // enable lighting back
    //        glEnable(GL_LIGHTING);
}

