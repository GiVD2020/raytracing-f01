#pragma once

#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QString>
#include <QStringList>
#include "glm/glm.hpp"
#include "Renders/Camera.h"
#include "Renders/RayTracingFactory.h"

/*
 * Format del fitxer de configuració de la Visualització:
 *
 * rendertype  format del rendering: potser ONLINE, IMAGE o TEMPORAL
 * limitsMon, definits per xmin, xmax, ymin, ymax, zmin, zmax
 * lookFrom, posicio observador
 * lookAt posicio on es mira
 * vup vector de verticalitat
 * vfov vertical field of view (obertura en vertical de la camera donada en graus)
 * aspectRatio, relacio width/height
 * witdh, amplada del viewport en pixels
 * output, nom del fitxer d'output en cas de ser IMAGE o TEMPORAL
 *
 *
 * TODO FASE 2: ampliar amb la informacio de les llums
*/

class ConfigVisReader {
public:
    explicit ConfigVisReader();

    ConfigVisReader(QString filename);
    void readFile (QString fileName);

    QString                         getOutputFile();
    RayTracingFactory::RENDER_TYPES getRenderType();
    shared_ptr<Camera>              getCamera();

protected:
    void fileLineRead (QString lineReaded);

    void renderTypeFound(QStringList fields);

    void lookFromFound(QStringList list);

    void lookAtFound(QStringList list);

    void vupFound(QStringList list);

    void vfovFound(QStringList list);

    void aspectRatioFound(QStringList list);

    void widthFound(QStringList list);

    void fitxerFound(QStringList list);


private:
    RayTracingFactory::RENDER_TYPES renderingType;
    vec3 lookfrom, lookat, vup;
    double vfov, aspect_ratio;
    int width;
    QString outputFile;
};


