#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
using namespace glm;

class Ray {
  public:
    vec3 origin;
    vec3 direction;

    Ray() {}

    Ray(const vec3 &orig, const vec3 &dir):
      origin(orig),
      direction(dir)
    {}

    /* retorna el punt del raig en en temps/lambda t */
    vec3 operator() (const float &t) const {
      return origin + direction*t;
    }

    vec3 initialPoint() const       { return origin; }
    vec3 dirVector() const    { return direction; }
    vec3 pointAtParameter(float t) const { return origin + t*direction; }

};

