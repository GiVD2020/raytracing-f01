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
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    vec3 newp = rec.p + 0.01f*(target-rec.p);
    r_out.push_back( Ray(newp, target-newp));
    color = diffuse;
    return true;
}
