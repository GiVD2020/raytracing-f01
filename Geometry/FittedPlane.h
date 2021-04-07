#pragma once

#include "Animation.h"
#include "Translate.h"
#include "Plane.h"
#include "glm/gtx/constants.hpp"
#include "MaterialTextura.h"

class FittedPlane: public Plane{
public:
    FittedPlane(vec3 normal, vec3 pass_point, float xmin, float xmax, float zmin, float zmax, float d);

    FittedPlane(vec3 normal, float d, float xmin, float xmax, float zmin, float zmax, float v);

    FittedPlane();

    bool isVisible() const {return visible;};
    void setVisible (bool vis) {visible = vis;};

    virtual ~FittedPlane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    virtual void applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame) override;
private:
    float Xmin, Xmax, Zmin, Zmax;
    bool visible;
};


