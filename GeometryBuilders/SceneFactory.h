#pragma once

#include <string.h>
#include <QString>

#include "Geometry/Scene.h"
#include "Geometry/ColorMap.h"
#include "DataService/ReadObj.h"
#include "ObjectFactory.h"
#include "Mapping.h"

class SceneFactory
{
public:
    SceneFactory() {};
    virtual ~SceneFactory() {};

    virtual shared_ptr<Scene> createScene()=0;
    virtual shared_ptr<Scene> createScene(QString nomFitxer)=0;

protected:
    shared_ptr<Mapping> map;
};

