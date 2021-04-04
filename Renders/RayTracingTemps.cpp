#include "RayTracingTemps.h"

RayTracingTemps::RayTracingTemps(int numFrames)
{
    this->numFrames = numFrames;
}

RayTracingTemps::~RayTracingTemps()
{
}

void RayTracingTemps::renderingScene(){
    string resultName;
    for (int f=0; f< numFrames; f++ ) {
        resultName = filename.toStdString() + std::to_string(f) + ".ppm";
        RayTracingPPM::initRender(resultName);
        // update dels objectes de l'escena per a posar-los al seu lloc,
        // en el cas que tinguin animacions associades
        scene->update(f);
        // càlcul del frame concret
        RayTracing::rendering();
        myfile.close();
    }
    // Cal cridar a la destructora de Render i no a la de RaytracingPPM,
    // tot i que doni el warning
    RayTracing::exitRender();
}
