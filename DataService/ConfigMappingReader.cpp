#include "ConfigMappingReader.h"


ConfigMappingReader::ConfigMappingReader(QString filename)
{
  numProp = 0;
  readFile(filename);

}

void ConfigMappingReader::readFile(QString fileName) {
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }
    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes
void ConfigMappingReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("limitsMonVirtual", fields[0], Qt::CaseInsensitive) == 0)
        limitsVirtualFound(fields);
    else  if (QString::compare("limitsMonReal", fields[0], Qt::CaseInsensitive) == 0)
        limitsRealFound(fields);
    else if (QString::compare("dataType", fields[0], Qt::CaseInsensitive) == 0)
        mappingTypeFound(fields);
    else if (QString::compare("base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}


void ConfigMappingReader::mappingTypeFound(QStringList fields) {
    //rendertype VIRTUALWORLD, REAL, TEMPORAL
    if (fields.size() != 2) {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    if (QString::compare("VIRTUALWORLD", fields[1], Qt::CaseInsensitive) == 0)
        dataType = Scene::DATA_TYPES::VIRTUALWORLD;
    else if (QString::compare("REALDATA", fields[1], Qt::CaseInsensitive) == 0)
        dataType = Scene::DATA_TYPES::REALDATA;
    else if (QString::compare("TEMPORALVW", fields[1], Qt::CaseInsensitive) == 0)
        dataType = Scene::DATA_TYPES::TEMPORALVW;
    else if (QString::compare("TEMPORALDATA", fields[1], Qt::CaseInsensitive) == 0)
        dataType = Scene::DATA_TYPES::TEMPORALDATA;
    else std::cerr << "Error de sintaxi en el tipus de dades" << std::endl;
}

void ConfigMappingReader::limitsRealFound(QStringList fields) {
    // limitsMonVirtual xmin xmax zmin zmax
    if (this->dataType==Scene::DATA_TYPES::REALDATA) {
        if (fields.size() != 5 ) {
            std::cerr << "Wrong limits format" << std::endl;
            return;
        }
        Rxmin = fields[1].toDouble();
        Rxmax = fields[2].toDouble();
        Rzmin = fields[3].toDouble();
        Rzmax = fields[4].toDouble();

    } else if (this->dataType==Scene::DATA_TYPES::VIRTUALWORLD) {
        // limitsMonVirtual xmin xmax ymin ymax zmin zmax
        if (fields.size() != 7 ) {
            std::cerr << "Wrong limits format" << std::endl;
            return;
        }
        Rxmin = fields[1].toDouble();
        Rxmax = fields[2].toDouble();
        Rymin = fields[3].toDouble();
        Rymax = fields[4].toDouble();
        Rzmin = fields[5].toDouble();
        Rzmax = fields[6].toDouble();
    }
    //Fet a Fase 1 (Albert): per comoditat, oferim també els limits com a vectors:
    Rmin = vec3(Rxmin, Rymin, Rzmin);
    Rmax = vec3(Rxmax, Rymax, Rzmax);
    Rdiff = vec3(Rxmax- Rxmin, Rymax- Rymin, Rzmax - Rzmin);
    RminDiff = min({Rdiff.x, Rdiff.y, Rdiff.z});
}

void ConfigMappingReader::limitsVirtualFound(QStringList fields) {
    // limitsMonVirtual xmin xmax zmin zmax
    if (fields.size() != 7 ) {
        std::cerr << "Wrong limits format" << std::endl;
        return;
    }
    Vxmin = fields[1].toDouble();
    Vxmax = fields[2].toDouble();
    Vymin = fields[3].toDouble();
    Vymax = fields[4].toDouble();
    Vzmin = fields[5].toDouble();
    Vzmax = fields[6].toDouble();
    //Fet a Fase 1 (Albert): per comoditat, oferim també els limits com a vectors:
    Vmin = vec3(Vxmin, Vymin, Vzmin);
    Vmax = vec3(Vxmax, Vymax, Vzmax);
    Vdiff = vec3(Vxmax - Vxmin, Vymax - Vymin, Vzmax - Vzmin);
    VminDiff = min({Vdiff.x, Vdiff.y, Vdiff.z});
}

void ConfigMappingReader::baseFound(QStringList fields) {
    //base plane nx ny nz d textura
    if (fields.size() != 7) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }

    if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0) {
        // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z

        normalPlaBase = vec3(fields[2].toDouble(), fields[3].toDouble(), fields[4].toDouble());
        dPlaBase = fields[5].toDouble();

        // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
    }
}

void ConfigMappingReader::propFound(QStringList fields) {
    //prop numProp vmin vmax tipusGizmo

    std::cerr<<"Prop found"<<std::endl;
    if (fields.size() != 6) {
        std::cerr << "Wrong propietat format config mapping" << std::endl;
        return;
    }
    numProp++;
    propLimits.push_back(std::make_pair(fields[2].toDouble(), fields[3].toDouble()));
    // TODO Fase 1: Cal guardar els valors per a poder escalar els objectes i el tipus de
    // gizmo de totes les propietats (SPHERE, BR_OBJ, CILINDRE...)
    if (QString::compare("sphere", fields[4], Qt::CaseInsensitive) == 0) {
        auto tipusObj = ObjectFactory::OBJECT_TYPES::SPHERE;
        if (QString::compare("COLOR_MAP_TYPE_INFERNO", fields[5], Qt::CaseInsensitive) == 0) {
            auto tipusColorMap = ColorMapStatic::COLOR_MAP_TYPE_INFERNO;
            props.push_back(std::make_pair(tipusObj, tipusColorMap));
        }
    }
}


