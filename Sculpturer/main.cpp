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
    
    globe->init(argc, argv);
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
    glutTimerFunc(globe->update_time, World::auto_update, 0);
    
    glutMainLoop();

    return 0;
}
