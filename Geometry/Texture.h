//
// Created by anna on 20/01/2020.
//

#ifndef RAYDATA_TEXTURE_H
#define RAYDATA_TEXTURE_H

#include <QImage>
#include <QColor>

#include <string>
#include <iostream>
#include "glm/glm.hpp"

using namespace glm;

using namespace std;

class Texture
{
    QImage image;

public:
    Texture(QString nomfitxer);
    virtual ~Texture();

    vec3 getColorPixel(vec2 uv);

};

#endif //RAYDATA_TEXTURE_H
