#include "Triangle.h"

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3, float data) :Object(data) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

bool Triangle::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    // Calculem la normal al triangle
    vec3 w = p2-p1;
    vec3 v = p3-p1;
    vec3 n = cross(w,v);

    // Caldulem la d del pla que conté el triangle
    float d = -dot(n,p1);

    // Comprovem si el normal al triangle i el raig son ortogonals.
    // En aquest cas son paralels i no hi ha interseccio
    float denum = dot(n,raig.dirVector());
    if (denum == 0) {
        return false;
    }

    // 2) Imposem que la recta p+tv compleixi l'eq del pla
    // A(p1 + tv1) + ... + D = 0
    // Aillem la t
    float num = -dot(n,raig.initialPoint()) - d;
    float t = num/denum;

    // Retornem false si no estem en el rang demanat
    if (t < t_min || t > t_max) {
        return false;
    }

    vec3 v1 = p3-p1;
    vec3 v2 = p2-p3;
    vec3 v3 = p2-p1;

    vec3 p = raig.pointAtParameter(t);

    float s1 = dot(cross(v2-v1,p-v1),n);
    float s2 = dot(cross(v3-v2,p-v2),n);
    float s3 = dot(cross(v1-v3,p-v3),n);

    if (s1*s2 > 0 && s1*s3 > 0 && s2*s3 > 0) {
        // Omplim el camp de info:
        info.t = t;
        info.p = p;
        // La normal a un triangle es la mateixa per tots els punts
        info.normal = n;
        info.mat_ptr = material.get();
        return true;
    }
    return false;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {

}
