//
//  main.cpp
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include <iostream>
#include <string>

#include "Utils.h"
#include "World.h"
#include "Object.h"


using namespace std;

World* globe; // current world to render

int main(int argc, char * argv[]) {
    globe = new World();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize(globe->window.size[0], globe->window.size[1]);
    glutCreateWindow(globe->window.name.c_str());
    
    DBVAR(glGetString(GL_VERSION));
    DBVAR(glGetString(GL_VENDOR));
    DBVAR(glGetString(GL_RENDERER));
    DBVAR(GLUT_API_VERSION);

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
    glutMouseFunc([](int button, int state, int x, int y){
        globe->mouse(button, state, x, y);
    });
    glutIdleFunc([](){
        glutPostRedisplay();
    });

    glutMainLoop();

    return 0;
}
