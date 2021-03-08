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
        std::cerr << "Wrong data format" << std::endl;
        return;
    }

    for (int i=0; i<n; i++) {

        shared_ptr<Object> o;

        vec3 puntBase = vec3(fields[1].toDouble(), 0.0, fields[2].toDouble());

         // Construccio de l'objecte al Mon Virtual TODO: FET A P1 4.2 A:
        //diferents tipus d'objectes (com tenen diferents constructors, cal el switch!)
        switch(mapping -> getObjectTypeProp(i)){
            case (ObjectFactory::CYLINDER):{
                //TODO:
                break;
            }
            case (ObjectFactory::SPHERE):{
                //Les coordenades al món virtual venen donades pel mètode implementat mapeigPunt,
                vec3 virtualPos = mapping->mapeigPunt(puntBase);
                //Però tenint en compte que la coordenada y és 0!
                virtualPos.y = 0;
                //El radi de l'esfera vindrà donat pel mapeig del valor en el món real al valor en el món virtual, de la propietat en qüestió, i escalarem *0.5:
                float radi = 0.5*mapping->mapeigValor(i, fields[i + 3].toFloat());
                o = ObjectFactory::getInstance().createObject(virtualPos, radi, fields[i + 3].toFloat(), ObjectFactory::SPHERE);
                break;
            }
            case (ObjectFactory::TRIANGLE):{
                //TODO: crear un triangle de referència segons diu l'enunciat i transformar-lo
                break;
            }
            default:{ //Els altres tipus no són vàlids per representar dades
                break;
            }
        }
        // Construccio i assignacio del material
        o->setMaterial(mapping->mapeigMaterial(i, mapping->getColorMapProp(i), fields[3 + i].toDouble()));

        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }
}
