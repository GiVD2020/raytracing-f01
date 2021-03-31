#include "Sphere.h"
#include "ScaleTG.h"

Sphere::Sphere(vec3 cen, float r, float data) :Object(data) {
    center = cen;
    radius = r;
}

bool Sphere::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    vec3 oc = raig.initialPoint() - center;
    float a = dot(raig.dirVector(), raig.dirVector());
    float b = dot(oc, raig.dirVector());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            return true;
        }
    }
    return false;
}

void Sphere::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<ScaleTG>(t)) {
    //if(t->getTG()[3][0]==0 & t->getTG()[3][1]==0  & t->getTG()[3][2]==0 &
            //t->getTG()[0][0]==t->getTG()[1][1] & t->getTG()[0][0]==t->getTG()[2][2]){
        radius *= t->getTG()[0][0];
    }else{
    //if (dynamic_pointer_cast<TranslateTG>(t)) {
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}

