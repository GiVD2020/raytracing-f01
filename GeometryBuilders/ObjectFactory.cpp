#include "ObjectFactory.h"

//! createObject
/*!
  \sa testMe()
  \param x coordenada x on cal colocar el centre de l'objecte en el món virtual
  \param y coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param z coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param aux paràmetre addicional per codificar el radi de l'esfera o la d del pla.
  \param v valor d'escalaque cal aplicar a l'objecte
  \param t tipus d'objecte a construir: SPHERE, PLANE, ....
*/

shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, float data, OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE:
        o = make_shared<Sphere>(v, aux, data);
        break;
    case PLANE:
        o = make_shared<Plane>(v, aux, data);
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<Object> ObjectFactory::createObject(vec3 p1, vec3 p2, vec3 p3, float data, OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    switch (t) {
        case TRIANGLE:
            o = make_shared<Triangle>(p1, p2, p3, data);
        break;
    default:
        break;
    }
}
