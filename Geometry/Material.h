#pragma once

#include <vector>
#include "Ray.h"
#include "Hitable.h"


// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();
    Material(vec3 d);
    Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta);
    ~Material();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const = 0;
    vec3 diffuse;

protected:
    vec3 RandomInSphere() const;
};


