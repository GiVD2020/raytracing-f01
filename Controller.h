#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include "Renders/RayTracingFactory.h"
#include "GeometryBuilders/SceneFactoryVirtual.h"
#include "GeometryBuilders/SceneFactoryData.h"
#include "GeometryBuilders/SceneFactory.h"
#include "DataService/ConfigVisReader.h"
#include "DataService/ConfigMappingReader.h"

class Controller
{
    shared_ptr<RayTracing> render;

public:
    Controller(QString dataFileName, QString configMapping, QString configVis);
    void start(int argc, char **argv);

private:
    shared_ptr<SceneFactory> getFactory(shared_ptr<ConfigMappingReader> cf);
};

#endif // CONTROLLER_H
