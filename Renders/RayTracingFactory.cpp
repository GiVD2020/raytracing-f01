#include "RayTracingFactory.h"

RayTracingFactory *RayTracingFactory::instance = nullptr;

RayTracingFactory::RayTracingFactory() {

}
shared_ptr<RayTracing> RayTracingFactory::getRender(RENDER_TYPES t, QString filename)
{
    shared_ptr<RayTracing> r;
    switch (t) {
    case ONLINE:
        r =  make_shared<RayTracingGLU>();
        break;
    case IMAGE:
        r = make_shared<RayTracingPPM>();
        r->setOutputFile(filename);
        break;
    case TEMPORAL:
        r = make_shared<RayTracingTemps>();
         r->setOutputFile(filename);
        break;
         }
    return r;
}

