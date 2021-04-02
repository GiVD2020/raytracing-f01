#pragma once

#include "Ray.h"

using namespace std;
class Material;


class HitInfo
{
public:
    float     t;         // t del raig on s'ha intersecat
    vec3      p;         // punt del raig on hi ha la intersecció
    vec3      normal;    // normal en el punt d'intersecció
    Material *mat_ptr;   // material de l'objecte que s'ha intersectat
    vec2      uv;        //coordenades de textura (u,v) en cas de que el material sigui textura
    int indObject;
    HitInfo():
        t(std::numeric_limits<float>::infinity()),
        p(0.0f),
        normal(0.0f),
        mat_ptr(NULL),
        uv(0,0)
        {}

    //  "operator =" per la classe  IntersectionInfo
    HitInfo &operator =(const HitInfo &rhs) {
      p = rhs.p;
      mat_ptr = rhs.mat_ptr;
      normal = rhs.normal;
      t = rhs.t;
      return *this;
    }
};

class Hitable
{
public:
    Hitable();
    ~Hitable();
    // S'obliga a implementar-lo en les classes filles: es un metode abstracte
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;
};

