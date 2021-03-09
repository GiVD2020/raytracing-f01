#include "ScaleTG.h"

ScaleTG::ScaleTG(glm::vec3 scale)
{
    matTG = glm::scale(glm::mat4(1.0f), scale);
}
