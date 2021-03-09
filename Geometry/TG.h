#ifndef TG_H
#define TG_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class TG
{
public:
    glm::mat4 matTG;
    TG();
    TG(glm::mat4 matTG);
    virtual ~TG() {};
    virtual glm::mat4 getTG();
};

#endif // TG_H
