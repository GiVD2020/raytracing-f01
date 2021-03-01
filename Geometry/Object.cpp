#include "Object.h"


Object::Object()
{
    data = -1;
    material = nullptr;
}

Object::Object(float d)
  {
    data = d;
    material = nullptr;
  }

float Object::getData() {
    return data;
}

void Object::setMaterial(shared_ptr<Material> m) {
    material = m;
}

shared_ptr<Material> Object::getMaterial() {
    return material;
}
