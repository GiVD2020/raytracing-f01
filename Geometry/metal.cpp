#include "metal.h"

#include "glm/glm.hpp"

using namespace glm;

Metal::Metal(const vec3& color)
{
    specular = color;
}

Metal::Metal(vec3 a, vec3 d, vec3 s, float beta): Material(a,d,s,vec3(0,0,0),beta)
{
}

Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 a = reflect(r_in.dirVector(), rec.normal);
    r_out.push_back(Ray(r_in.initialPoint(), a));
    color = specular;
    return true;
}
