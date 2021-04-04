#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "ScaleTG.h"


class Cylinder: public Object
{
public:
    Cylinder(vec3 cen, float r, float h, float data);
    virtual ~Cylinder() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    virtual void applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame) override;
private:
    // Centre de la base del cilindre
    vec3 center;
    // Radi
    float radius;
    // Alçada des del centre de la base
    float height;
};

#endif // CYLINDER_H
