#include "RayTracingTemps.h"

RayTracingTemps::RayTracingTemps()
{
}

RayTracingTemps::~RayTracingTemps()
{
}

void RayTracingTemps::renderingScene(){

    string resultName;
    for (unsigned long i=0; i<MAXFRAMES; i++ ) {
        resultName = filename.toStdString() + std::to_string(i) + ".ppm";
        RayTracingPPM::initRender(resultName);
        // update dels objectes de l'escena per a posar-los al seu lloc,
        // en el cas que tinguin animacions associades
        scene->update(i);
        // càlcul del frame concret
        RayTracing::rendering();
        myfile.close();
    }
    // Cal cridar a la destructora de Render i no a la de RaytracingPPM,
    // tot i que doni el warning
    RayTracing::exitRender();
}
