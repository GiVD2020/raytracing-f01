#include "Cone.h"

Cone::Cone(vec3 cen, float r, float h, float data) :Object(data) {
    center = cen;
    radius = r;
    height = h;
}

bool Cone::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    vec3 oc = raig.initialPoint() - center - vec3(0,height,0);
    float a = raig.dirVector().x*raig.dirVector().x + raig.dirVector().z*raig.dirVector().z - (radius/height)*(radius/height)*raig.dirVector().y*raig.dirVector().y;
    float b = 2*(raig.dirVector().x*oc.x + raig.dirVector().z*oc.z - (radius/height)*(radius/height)*raig.dirVector().y*oc.y);
    float c = oc.x*oc.x + oc.z*oc.z - (radius/height)*(radius/height)*oc.y*oc.y;
    float discriminant = b*b - 4*a*c;
    int hitSurface = 0;
    float closestTemp = t_max;
    float y, temp;
    if (discriminant > 0) {
        // Solucio lateral mes propera
        temp = (-b - sqrt(discriminant)) / (2*a);
        y = raig.pointAtParameter(temp).y;
        if (temp < t_max && temp > t_min && y <= center.y + height && y >= center.y) {
            hitSurface = 1;
            closestTemp = temp;
        }
        // Solucio lateral mes llunyana
        temp = (-b + sqrt(discriminant)) / (2*a);
        y = raig.pointAtParameter(temp).y;
        if (temp < closestTemp && temp < t_max && temp > t_min && y <= center.y + height && y >= center.y) {
            hitSurface = 1;
            closestTemp = temp;
        }
    }
    // Solucio tapa interior
    temp =  (center.y - raig.initialPoint().y) / raig.dirVector().y;
    float x = raig.pointAtParameter(temp).x;
    float z = raig.pointAtParameter(temp).z;
    if (temp < closestTemp && temp < t_max && temp > t_min && (x - center.x)*(x - center.x) + (z - center.z)*(z - center.z) <= radius*radius) {
        hitSurface = 2;
        closestTemp = temp;
    }
    if (hitSurface == 1) {
        info.t = closestTemp;
        info.p = raig.pointAtParameter(info.t);
        float vx = info.p.x - center.x;
        float vz = info.p.z - center.z;
        float vy = sqrt(vx*vx + vz*vz)*radius/height;
        info.normal = normalize(vec3(vx, vy, vz));
        info.mat_ptr = material.get();
        return true;
    } else if (hitSurface == 2) {
        info.t = closestTemp;
        info.p = raig.pointAtParameter(info.t);
        vec3 normal(0, -1, 0);
        info.normal = normal;
        info.mat_ptr = material.get();
        return true;
    }
    return false;
}

void Cone::aplicaTG(shared_ptr<TG> t) {
    //TODO: no funciona instanceof
    //if (dynamic_pointer_cast<ScaleTG>(t)) {
    if(t->getTG()[3][0]==0 ){
        height *= t->getTG()[0][0];
    }else{
    //if (dynamic_pointer_cast<TranslateTG>(t)) {
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}

