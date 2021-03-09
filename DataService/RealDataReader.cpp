#include "RealDataReader.h"


RealDataReader::RealDataReader(shared_ptr<Scene> s)
{
    scene = s;
}

void RealDataReader::readFile(QString fileName, shared_ptr<Mapping> map) {
    QFile file(fileName);

    mapping = map;

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
void RealDataReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}



void RealDataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    int n = mapping->getNumProps();

    if (fields.size() != (3 + n)) {
        std::cerr << "Wrong data format in RealDataReader: required " << n + 3 << " fields, but found instead " << fields.size() << std::endl;
        return;
    }

    shared_ptr<TG> mapeigRealAVirtual = mapping->getMapeigRealAVirtual();
    vec3 puntBase = vec3(fields[1].toDouble(), 0.0, fields[2].toDouble());

    for (int i=0; i<n; i++) {

        shared_ptr<Object> o;

        //Escalat segons la propietat:
        shared_ptr<ScaleTG> escalat = mapping->getEscalat(i, fields[i + 3].toFloat());

         // Construccio de l'objecte al Mon Virtual TODO: FET A P1 4.2 A:
        o = ObjectFactory::getInstance().createObject(puntBase, fields[i + 3].toFloat(), mapeigRealAVirtual, escalat, mapping->getObjectTypeProp(i));

        // Construccio i assignacio del material
        o->setMaterial(mapping->mapeigMaterial(i, mapping->getColorMapProp(i), fields[3 + i].toDouble()));

        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }
}
