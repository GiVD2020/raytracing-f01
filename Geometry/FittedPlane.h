#pragma once

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "glm/gtx/constants.hpp"


class FittedPlane: public Object{
public:
    FittedPlane(vec3 normal, vec3 pass_point, float xmin, float xmax, float zmin, float zmax, float d);

    FittedPlane(vec3 normal, float d, float xmin, float xmax, float zmin, float zmax, float v);

    FittedPlane();

    bool isVisible() const {return visible;};
    void setVisible (bool vis) {visible = vis;};

    virtual ~FittedPlane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

private:
    vec3 normal;
    vec3 point;
    float Xmin, Xmax, Zmin, Zmax;
    bool visible;
};


