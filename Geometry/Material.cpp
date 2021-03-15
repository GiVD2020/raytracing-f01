#include "Material.h"



Material::Material():
    diffuse(1.0f)
  {}

Material::~Material()
{}

Material::Material(vec3 d){
    diffuse = d;
}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){
    // TO DO: Fase 2
    diffuse = d;
    ambient = a;
    specular = s;
    shineness = beta;
    //TODO: k es transparencia per apartat D
}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(double(rand())/RAND_MAX, double(rand())/RAND_MAX,double(rand())/RAND_MAX) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

