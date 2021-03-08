#include "Cylinder.h"

Cylinder::Cylinder(vec3 cen, float r, float h, float data) :Object(data) {
    center = cen;
    radius = r;
    height = h;
}

bool Cylinder::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    vec3 oc = raig.initialPoint() - center;
    float a = raig.dirVector().x*raig.dirVector().x + raig.dirVector().z*raig.dirVector().z;
    float b = 2*(raig.dirVector().x*oc.x + raig.dirVector().z*oc.z);
    float c = oc.x*oc.x + oc.z*oc.z - radius*radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        // Solucio lateral mes propera
        float temp = (-b - sqrt(discriminant)) / (2*a);
        float y = raig.pointAtParameter(temp).y;
        if (temp < t_max && temp > t_min && y <= center.y + height && y >= center.y) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            vec3 liftedCenter(center.x, y, center.z);
            info.normal = (info.p - liftedCenter) / radius;
            info.mat_ptr = material.get();
            return true;
        }
        // Solucio lateral mes llunyana
        temp = (-b + sqrt(discriminant)) / (2*a);
        y = raig.pointAtParameter(temp).y;
        if (temp < t_max && temp > t_min && y <= center.y + height && y >= center.y) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            vec3 liftedCenter(center.x, y, center.z);
            info.normal = (info.p - liftedCenter) / radius;
            info.mat_ptr = material.get();
            return true;
        }
    }
    return false;
}

void Cylinder::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}

