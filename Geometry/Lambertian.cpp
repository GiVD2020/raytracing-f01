#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    diffuse = color;
}

Lambertian::Lambertian(vec3 d, vec3 a, vec3 s, float beta): Material(d,a,s,vec3(0,0,0),beta)
{
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back( Ray(rec.p, target-rec.p));
    color = diffuse;
    return true;
}
