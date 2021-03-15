#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Light
{
public:
    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, double a, double b, double c);
    glm::vec3 position, ambient, diffuse, specular;
    double a, b, c; //a*d² + b*d + c

    glm::vec3 get_vector_L(glm::vec3 s);
    float apply_atenuation(glm::vec3 s);
};

