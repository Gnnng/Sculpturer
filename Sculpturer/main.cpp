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

using namespace std;

GLfloat bgColor[4] = {0.1, 0.1, 0.1, 0};

bool init() {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
    glColor3f(0, 0, 0);
    
    return true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 1);
    glVertex2f(0, 0);
    glVertex2f(0, 0.5);
    glVertex2f(0.5, 0);
    glEnd();
    
    glFlush();
    
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    glutCreateWindow("A Demo");
    
    glutDisplayFunc(display);
    
    init();
    
    std::cout << "glut version is " << glGetString(GL_VERSION) << std::endl;
    glutMainLoop();
    return 0;
}
