#ifndef CONE_H
#define CONE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "ScaleTG.h"


class Cone: public Object
{
public:
    Cone(vec3 cen, float r, float h, float data);
    virtual ~Cone() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
private:
    // Centre de la base del cilindre
    vec3 center;
    // Radi
    float radius;
    // Alçada des del centre de la base
    float height;
};

#endif // CONE_H
