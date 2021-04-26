#include "Light.h"
# define M_PI           3.14159265358979323846

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, double a, double b, double c)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->a = a;
    this->b = b;
    this->c = c;
    this->direction = glm::vec3(0,0,0);
    this->angle = -1;
}

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, double a, double b, double c, glm::vec3 dir, double ang)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->a = a;
    this->b = b;
    this->c = c;
    this->direction = glm::normalize(dir);
    this->angle = ang;
}

glm::vec3 Light::get_vector_L(glm::vec3 s){
    return this->position-s;
}

float Light::get_atenuation(glm::vec3 p){
    float d = glm::length(this->position-p);
    return 1./(this->a*d*d + this->b*d + this->c);
}

bool Light::isPointInCone(glm::vec3 point){
    if (this->angle < 0 || this->angle > M_PI || glm::length(direction) < 0.01) {
        return true;
    } else {
        glm::vec3 dirPoint = glm::normalize(point - this->position);
        double anglePointLight = glm::acos(glm::dot(dirPoint, this->direction));
        if (anglePointLight <= this->angle) {
            return true;
        }
    }
    return false;
}

