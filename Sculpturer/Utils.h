#ifndef __UTILS_H__
#define __UTILS_H__


#ifdef NDEBUG
#define DEBUG_TEST_COND 0
#else
#define DEBUG_TEST_COND 1
#endif

/* get only filename */
#include <cstring>
#define __FILENAME__ \
    (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

/* show more precise infomartion */
#ifdef DBINFO_POS
#define __DB_POS__ \
    "[" << __FILENAME__ << ":" << __LINE__ << "] " <<
#else
#define __DB_POS__ "" <<
#endif

/* define print macros */
#include <iostream>
#define DBVAR(var) \
    do { \
        if (DEBUG_TEST_COND) \
        std::cout << "[DEBUG] " << __DB_POS__ \
        #var << "\t"  << (var) << \
        std::endl; \
    } while (0)

#define DBMSG(msg) \
    do { \
        if (DEBUG_TEST_COND) \
        std::cout << "[DEBUG] " << __DB_POS__ \
        msg << \
        std::endl;\
    } while (0)

#define LOG(msg) \
    do { \
        if (DEBUG_TEST_COND) \
        std::cout << "[LOG] " << __DB_POS__ \
        msg << \
        std::endl; \
    } while (0)

#include <cmath>
#include <algorithm>
#include <array>
#include <iostream>
#include <cstring>

#include <GL/freeglut.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

class Utils {
public:
    static GLdouble toDegree(GLdouble rad) { return rad / (3.14159265358/180); }
    static GLdouble toRadian(GLdouble deg) { return deg * 3.14159265358 / 180; }
};

class World;
extern World* globe;


#endif /* __UTILS_H__ */