#include "Lambertian.h"

#include "glm/glm.hpp"

using namespace glm;

Lambertian::Lambertian(const vec3& color): Material()
{
    diffuse = color;
}

Lambertian::Lambertian(vec3 a, vec3 d, vec3 s, float beta): Material(a,d,s,vec3(0,0,0),beta)
{
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 newp = r_in.initialPoint() + 0.01f*r_in.dirVector();
    vec3 target = newp + rec.normal + this->RandomInSphere();
    r_out.push_back( Ray(newp, target-newp));
    color = diffuse;
    return true;
}
