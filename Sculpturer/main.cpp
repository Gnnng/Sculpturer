//
//  main.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include <iostream>
#include <string>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include "World.h"
#include "Object.h"

using namespace std;

World* globe; // current world to render

int main(int argc, char * argv[]) {
    globe = new World();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(globe->view_port_size[0], globe->view_port_size[1]);
    glutCreateWindow("Sculpturer");
    
    globe->workspace();

    glutDisplayFunc([]() {
        globe->display();
    });
    glutReshapeFunc([](int w, int h) {
        globe->reshape(w, h);
    });
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        globe->keyboard(key, x, y);
    });
    glutIdleFunc([](){
        glutPostRedisplay();
    });
    glutMainLoop();

    return 0;
}
