//
//  World.h
//  Sculpturer
//
//  Created by Gong Deli on 6/18/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#ifndef __Sculpturer__World__
#define __Sculpturer__World__

#include <vector>
#include <functional>
#include <map>
#include <string>
#include <sstream>

#include "Utils.h"
#include "Camera.h"
#include "Object.h"
#include "Window.h"
#include "Light.h"
#include "Bmp.h"

class World {
public:
    enum class ButtonType : int {
        button_l, // 0
        button_m, // not captured
        button_r,
        swipe_d,
        swipe_u,
        swipe_r,
        swipe_l
    };
    enum class ButtonState : int { down, up };

    std::vector<Object *>       objs;
    std::array<GLclampf, 4>     bg_color;
    Camera                      camera;
    Window                      window;
    GLint                       update_time;
    bool init_done;
    std::array<GLuint, 1000>    sel_buf;
    std::array<GLint, 2>        sel_area_size = {5, 5};
    GLuint                      pick_id = 0;
    GLuint                      pick_count = 0;
    std::map<Object *, int>     pick_map;
    std::vector<Light>          lights;
    World();
    ~World();

    void init();
    
    void display();
    void displayObject();
    void displayHUD();
    void displayLights();

    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    void update();
    static void auto_update(int id);
    void pickObject(int x, int y);
    void printScreen() {
        static int count = 0;
        std::ostringstream fname;
        fname << "screenshots-" << count << ".bmp";
        GLubyte* pixels = new GLubyte[3 * window.size[0] * window.size[1]];
        glReadPixels(0, 0, window.size[0], window.size[1], GL_RGB, GL_UNSIGNED_BYTE, (GLvoid* )pixels);
        SaveImage((char *)fname.str().c_str(), (void *)pixels, window.size[0], window.size[1]);
    }
    
    void workspace();
    void add(Object *o) { objs.push_back(o); pick_map[o] = ++pick_count; DBVAR(pick_map[o]);}
    void drawGrid(GLfloat size, GLfloat step);
};

#endif /* defined(__Sculpturer__World__) */
