#ifndef MATERIALTEXTURA_H
#define MATERIALTEXTURA_H
#include "Material.h"
#include "Texture.h"
#include <memory>
class MaterialTextura : public Material
{

public:
    MaterialTextura(vec3 a, vec3 d, vec3 s, float beta, shared_ptr<Texture> texture);
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
    vec3 getDiffuse(vec2 point) const override;
    vec3 getAmbient(vec2 point) const;
    bool ignoreLights = false;
protected:
    shared_ptr<Texture> texture;
};


#endif // MATERIALTEXTURA_H
