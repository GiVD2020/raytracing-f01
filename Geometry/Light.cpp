#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, double a, double b, double c)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->a = a;
    this->b = b;
    this->c = c;
}

glm::vec3 Light::get_vector_L(glm::vec3 s){
    return (glm::normalize(this->position)-s);
}

float Light::apply_atenuation(glm::vec3 s){
    float d = glm::length(get_vector_L(s));
    return 1./(this->a + (this->b * d) + this->c * d * d);
}



