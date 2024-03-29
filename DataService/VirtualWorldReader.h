#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <iostream>
#include <sstream>

#include "glm/glm.hpp"
#include "Geometry/Scene.h"
#include "GeometryBuilders/ObjectFactory.h"
#include "GeometryBuilders/Mapping.h"

class VirtualWorldReader {
public:
    explicit VirtualWorldReader();

    VirtualWorldReader(shared_ptr<Scene> s);

    void readFile (QString fileName, shared_ptr<Mapping> map);

private:
    virtual void fileLineRead (QString lineReaded);

    shared_ptr<Scene> scene;
    shared_ptr<Mapping> mapping;

    void sphereFound(QStringList list);

    void brObjectFound(QStringList fields);

    void triangleFound(QStringList fields);

    void planeFound(QStringList fields);

    void fittedPlaneFound(QStringList fields);

    void cylinderFound(QStringList fields);

    void coneFound(QStringList fields);
  
    void readMaterialAndAnimation(QStringList fields, int startIndex, shared_ptr<Object> o);

};

