#include "Triangle.h"

#include <iostream>

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3, float data) :Object(data) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;

    // Pla que conte el triangle
    vec3 w = p3 - p2;
    vec3 v = p2 - p1;

    this->n = cross(w,v)/length(cross(w,v));
    this->plane = make_shared<Plane>(n, p1, -1.0f);

}

bool Triangle::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

    // Vectors del triangle
    vec3 w = p3 - p2;
    vec3 v = p2 - p1;
    vec3 u = p1 - p3;

    // 1. Mirem si el raig interseca amb el pla que conté el triangle
    HitInfo infoPlane;
    if (!plane->hit(raig, t_min, t_max, infoPlane)) {
        return false;
    }

    // 2. Calcul de les baricèntriques
    vec3 v1 = infoPlane.p - p1;
    if (dot(n,cross(v1,v)) < 0) {
        return false;
    }

    vec3 v2 = infoPlane.p - p2;
    if (dot(n,cross(v2,w)) < 0) {
        return false;
    }

    vec3 v3 = infoPlane.p - p3;
    if (dot(n,cross(v3,u)) < 0) {
        return false;
    }

    // Omplim el camp de info
    info.t = infoPlane.t;
    info.p = infoPlane.p;
    info.normal = n;
    info.mat_ptr = material.get();

    return true;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {

        // Transformem els 3 punts del triangle
        vec4 newp1(this->p1, 1.0);
        vec4 newp2(this->p2, 1.0);
        vec4 newp3(this->p3, 1.0);

        newp1 = t->getTG() * newp1;
        newp2 = t->getTG() * newp2;
        newp3 = t->getTG() * newp3;

        this->p1.x = newp1.x;
        this->p1.y = newp1.y;
        this->p1.z = newp1.z;
        this->p2.x = newp2.x;
        this->p2.y = newp2.y;
        this->p2.z = newp2.z;
        this->p3.x = newp3.x;
        this->p3.y = newp3.y;
        this->p3.z = newp3.z;
    }
}

vec3 Triangle::calculaBaricentre(){
    float a = 1/3;
    return a*(p1+p2+p3);
}

void Triangle::applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame){
//Implementar si es vol poder animar aquest tipus d'objecte
}
