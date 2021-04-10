#ifndef TRANSPARENT_H
#define TRANSPARENT_H
#include "Material.h"
class Transparent : public Material
{

public:
    float DEFAULT_RATIO=1.0;
    Transparent(vec3 a, vec3 d, vec3 s, float beta, vec3 k, float refRatio, float dmax);
    Transparent(vec3 a, vec3 d, vec3 s, float beta, float refRatio, float dmax);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
    float dmax;
private:
    float refRatio;
};

#endif // TRANSPARENT_H
