#pragma once

#include <vector>
#include "Light.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class PointLight : public Light{
public:
    PointLight();
    glm::vec3 position;
    double a, b, c; //a*d² + b*d + c
};

