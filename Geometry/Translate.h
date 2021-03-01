#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "TG.h"

class TranslateTG : public TG
{
public:
    glm::vec3 traslation;
    TranslateTG(glm::vec3 trasl);
    ~TranslateTG();
};

#endif // TRANSLATE_H
