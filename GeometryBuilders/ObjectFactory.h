#pragma once

#include "Geometry/Object.h"
#include "Geometry/Sphere.h"
#include "Geometry/Plane.h"
#include "Geometry/Triangle.h";

class ObjectFactory
{
    ObjectFactory(){};

public:
    enum  OBJECT_TYPES{
        SPHERE,
        PLANE,
        TRIANGLE
    };

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(vec3 v, double aux, float data, OBJECT_TYPES t);
    shared_ptr<Object> createObject(vec3 p1, vec3 p2, vec3 p3, float data, OBJECT_TYPES t);
};

