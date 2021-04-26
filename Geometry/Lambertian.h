#pragma once

#include "Material.h"

class Lambertian : public Material
{

public:
    Lambertian(const vec3& color);
    Lambertian(vec3 a, vec3 d, vec3 s, float beta);
    virtual ~Lambertian();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;

private:
    static const int NUMRAYS = 3;
};
