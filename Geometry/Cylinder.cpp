#include "Cylinder.h"

Cylinder::Cylinder(vec3 cen, float r, float h, float data) :Object(data) {
    initCenter = cen;
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
    // Solucio tapa superior
    temp =  (center.y + height - raig.initialPoint().y) / raig.dirVector().y;
    float x = raig.pointAtParameter(temp).x;
    float z = raig.pointAtParameter(temp).z;
    if (temp < closestTemp && temp < t_max && temp > t_min && (x - center.x)*(x - center.x) + (z - center.z)*(z - center.z) <= radius*radius) {
        hitSurface = 2;
        closestTemp = temp;
    }
    // Solucio tapa interior
    temp =  (center.y - raig.initialPoint().y) / raig.dirVector().y;
    x = raig.pointAtParameter(temp).x;
    z = raig.pointAtParameter(temp).z;
    if (temp < closestTemp && temp < t_max && temp > t_min && (x - center.x)*(x - center.x) + (z - center.z)*(z - center.z) <= radius*radius) {
        hitSurface = 3;
        closestTemp = temp;
    }
    if (hitSurface == 1) {
        y = raig.pointAtParameter(closestTemp).y;
        info.t = closestTemp;
        info.p = raig.pointAtParameter(info.t);
        vec3 liftedCenter(center.x, y, center.z);
        info.normal = (info.p - liftedCenter) / radius;
        info.mat_ptr = material.get();
        return true;
    } else if (hitSurface == 2) {
        info.t = closestTemp;
        info.p = raig.pointAtParameter(info.t);
        vec3 normal(0, 1, 0);
        info.normal = normal;
        info.mat_ptr = material.get();
        return true;
    } else if (hitSurface == 3) {
        info.t = closestTemp;
        info.p = raig.pointAtParameter(info.t);
        vec3 normal(0, -1, 0);
        info.normal = normal;
        info.mat_ptr = material.get();
        return true;
    }
    return false;
}

void Cylinder::aplicaTG(shared_ptr<TG> t) {
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

void Cylinder::applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame){
    if(dynamic_pointer_cast<EllipseAnimation>(anim)){
        shared_ptr<EllipseAnimation> elAnim = dynamic_pointer_cast<EllipseAnimation>(anim);
        vec3 newPos = elAnim->getPosition(initCenter, nFrame);
        center = vec3(newPos.x, initCenter.y, newPos.z);
    }
}

