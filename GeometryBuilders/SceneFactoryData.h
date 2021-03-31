#pragma once


#include "Geometry/ColorMapStatic.h"
#include "DataService/RealDataReader.h"
#include "SceneFactory.h"
#include "Mapping.h"
#include "Geometry/MaterialTextura.h"

class SceneFactoryData : public SceneFactory
{
public:
    SceneFactoryData(shared_ptr<ConfigMappingReader> mapping);
    virtual shared_ptr<Scene>  createScene(QString nomFitxer);
    virtual shared_ptr<Scene>  createScene();
};


