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
    for (int i = 0; i < 1; i++) {
        vec3 target = rec.normal + this->RandomInSphere();
        vec3 newp = rec.p + 0.01f*target;
        r_out.push_back(Ray(newp, target));
    }
    color = diffuse;
    return true;
}
