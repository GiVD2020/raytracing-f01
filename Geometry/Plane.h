#pragma once

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "glm/gtx/constants.hpp"


class Plane: public Object{
public:
    Plane(vec3 normal, vec3 pass_point, float d);

    Plane(vec3 normal, float d, float v);

    virtual ~Plane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

private:
    vec3 normal;
    vec3 point;
};


