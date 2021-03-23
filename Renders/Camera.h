#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define _USE_MATH_DEFINES
    #include <cmath>
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Geometry/Ray.h"
using namespace glm;


// Classe que codifica les propietats físiques de la càmera
class Camera {

public:

    Camera();

    Camera(vec3 lookfrom,
                vec3 lookat,
                vec3   vup,
                double vfov, // vertical field-of-view in degrees
                double aspect_ratio, double pixelsX);

    Ray getRay(float s, float t) ;

    vec3 getOrigin();
    static vec3 random_in_unit_disk() {
        vec3 p;
        do {
            p = 2.0f*vec3(double(rand())/RAND_MAX,double(rand())/RAND_MAX,0) - vec3(1,1,0);
        } while (dot(p,p) >= 1.0);
        return p;
    }

    // Viewport: mides del frame buffer
    int viewportX;
    int viewportY;

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;



};



