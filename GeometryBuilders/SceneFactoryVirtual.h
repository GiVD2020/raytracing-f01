#pragma once

#include "DataService/VirtualWorldReader.h"
#include "SceneFactory.h"
#include "Mapping.h"

class SceneFactoryVirtual : public SceneFactory
{
public:
    SceneFactoryVirtual(shared_ptr<ConfigMappingReader> mapping);

    virtual shared_ptr<Scene>  createScene(QString nomFitxer);
    virtual shared_ptr<Scene>  createScene();

private:
    void OneSphere(shared_ptr<Scene> s);
};


