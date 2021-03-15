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


