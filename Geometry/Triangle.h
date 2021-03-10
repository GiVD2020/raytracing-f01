#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Plane.h"

class Triangle: public Object
{
public:
    Triangle(vec3 p1, vec3 p2, vec3 p3, float data);
    virtual ~Triangle() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
private:
    // Punts del triangle, orientat CCW
    vec3 p1;
    vec3 p2;
    vec3 p3;
};

#endif // TRIANGLE_H
