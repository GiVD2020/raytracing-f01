#pragma once

#include "Geometry/Object.h"
#include "Geometry/Sphere.h"
#include "Geometry/Plane.h"

class ObjectFactory
{
    ObjectFactory(){};

public:
    enum  OBJECT_TYPES{
        SPHERE,
        PLANE
    };

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(vec3 v, double aux, float data, OBJECT_TYPES t);
};

