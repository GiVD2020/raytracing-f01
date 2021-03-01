//
// Created by anna on 20/01/2020.
//

#include "Texture.h"

Texture::Texture(QString nomfitxer)
{
    bool success = image.load(nomfitxer);

    if (!success) std::cout << "Imatge no trobada" << endl;

}
Texture::~Texture() {

}
vec3 Texture::getColorPixel(vec2 uv) {
    QColor c(image.pixel((uv.x)*image.width(), (uv.y)*image.height() ));
    return(vec3(c.redF(), c.greenF(), c.blueF()));
}