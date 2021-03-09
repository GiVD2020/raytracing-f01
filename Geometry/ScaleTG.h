#ifndef SCALETG_H
#define SCALETG_H

#include "TG.h"

class ScaleTG : public TG
{
public:
    glm::vec3 scale;
    ScaleTG(glm::vec3 scale);
};

#endif // SCALETG_H
