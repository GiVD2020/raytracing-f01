#include "Camera.h"

Camera::Camera() {
    float aspect = 1;
    viewportX = 400;
    viewportY = 400;
    auto vup = vec3(0,1,0);
    auto lookat = vec3(0,0,0);
    auto lookfrom = vec3(0,0,10);

    float theta = M_PI/2.0;
    float window_height = 2*tan(theta/2);
    float window_width = aspect * window_height;
    origin = lookfrom;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);
    float half_width = window_width/2.0;
    float half_height = window_height/2.0;
    lower_left_corner = origin  - half_width*u -half_height*v - w;
    horizontal = window_width*u;
    vertical = window_height*v;

}


Camera::Camera(
            vec3 lookfrom,
            vec3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio, double pixelsX)
{
    auto theta = (vfov)*M_PI/180.0;
    auto h = tan(theta/2);
    float window_height = 2.0 * h;
    float window_width = aspect_ratio * window_height;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = window_width * u;
    vertical = window_height * v;
    float half_width = window_width/2.0;
    float half_height = window_height/2.0;
    lower_left_corner = origin  - (half_width)*u -(half_height)*v - w;
    horizontal = window_width*u;
    vertical = window_height*v;

    viewportX = pixelsX;
    viewportY = pixelsX/aspect_ratio;
}

vec3 Camera::getOrigin(){
    return origin;
}
Ray Camera::getRay(float s, float t) {
     return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
}


