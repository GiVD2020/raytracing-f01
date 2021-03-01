#include "TG.h"

TG::TG()
{
 matTG = glm::mat4(1.0f);
}

TG::~TG()
{

}

glm::mat4 TG::getTG() {
    return matTG;
}
