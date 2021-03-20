#include "Transparent.h"

#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"
using namespace glm;

Transparent::Transparent(vec3 a, vec3 d, vec3 s, float beta, float refRatio): Material(a,d,s,vec3(0,0,0),beta)
{
    this->refRatio = refRatio;
}

Transparent::~Transparent()
{
}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    //Ha de retornar un únic raig transmés i retornar la kt del material si el raig és transmés
    float epsilon = 0.0001;
    vec3 normal;
    float ratio;
    if(glm::dot(r_in.dirVector(), rec.normal) > epsilon){
        normal = -rec.normal;
        ratio = DEFAULT_RATIO / refRatio;
    }else{
        normal = rec.normal;
        ratio = refRatio / DEFAULT_RATIO;
    }

    vec3 t = glm::refract(r_in.dirVector(), normal, ratio);
    if(length(t) < epsilon){ //Aleshores hi ha reflexió total interna:
        t = glm::reflect(r_in.dirVector(), normal);
        color = specular;
    }else{
        color = vec3(1) - specular;
    }
    r_out.push_back(Ray(rec.p+0.01f*t, t));
    return true;
}
