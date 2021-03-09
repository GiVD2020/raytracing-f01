#include "TG.h"

TG::TG()
{
 matTG = glm::mat4(1.0f);
}

TG::TG(glm::mat4 matTG)
{
 this->matTG = matTG;
}

glm::mat4 TG::getTG() {
    return matTG;
}
