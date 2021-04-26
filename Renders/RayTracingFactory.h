#pragma once

#include "RayTracingGLU.h"
#include "RayTracingPPM.h"
#include "RayTracingTemps.h"
#include "GeometryBuilders/Mapping.h"
class RayTracingFactory
{
    static RayTracingFactory* instance;
    RayTracingFactory();

public:
    typedef enum  {
        ONLINE, IMAGE, TEMPORAL
    } RENDER_TYPES;

    static RayTracingFactory *getInstance() {
          if (instance==nullptr)
              instance = new RayTracingFactory();
          return instance;
    }
    shared_ptr<RayTracing> getRender(RENDER_TYPES t, QString filename, Mapping mapping);
    ~RayTracingFactory() {
        delete instance;
    }

};

