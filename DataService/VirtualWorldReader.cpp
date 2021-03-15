#include "VirtualWorldReader.h"


VirtualWorldReader::VirtualWorldReader(shared_ptr<Scene> s)
{
    scene = s;
}

void VirtualWorldReader::readFile(QString fileName, shared_ptr<Mapping> map) {

    mapping = map;
    std::cout << fileName.toStdString()<<std::endl;

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
void VirtualWorldReader::fileLineRead (QString lineReaded) {
    QStringList fields = lineReaded.split(",");
    if (QString::compare("sphere", fields[0], Qt::CaseInsensitive) == 0)
        sphereFound(fields);
    else if (QString::compare("triangle", fields[0], Qt::CaseInsensitive) == 0)
        triangleFound(fields);
    else if (QString::compare("brobject", fields[0], Qt::CaseInsensitive) == 0)
        brObjectFound(fields);
    else if (QString::compare("cylinder", fields[0], Qt::CaseInsensitive) == 0)
        cylinderFound(fields);
    else if (QString::compare("plane", fields[0], Qt::CaseInsensitive) == 0)
        planeFound(fields);
    else if (QString::compare("fittedplane", fields[0], Qt::CaseInsensitive) == 0)
        fittedPlaneFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

// Exemple d'esfera
// sphere, 0.5, 0.5, 0.0, 0.25
// centre i radi
void VirtualWorldReader::sphereFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // sphere, centre.x, centre.y, centre.z, radi, propietats del material, textura
    if (fields.size() != 15 ) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  mapping->mapeigValor(fields[4].toDouble()),
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::SPHERE);
    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()),
            vec3(fields[8].toDouble(),fields[9].toDouble(),fields[10].toDouble()),
            vec3(fields[11].toDouble(),fields[12].toDouble(),fields[13].toDouble()),
            fields[14].toDouble());
    o->setMaterial(mat);


    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}


void VirtualWorldReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    //  brobject, nomDelFitxer, propietats del material, textura

    if (fields.size() != 6) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }

    QString s = fields[1];

    shared_ptr<Object> o;

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(s,
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::BR_OBJECT);

    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

}

void VirtualWorldReader::triangleFound(QStringList fields) {

    // TODO Fase 1: Per incloure Triangle
    //  Es suposa que serà una linia del fitxer de l'estil
    //  triangle, x1, y1, z1, x2, y2, z2, x3, y3, z3, propietats del material, textura

    if (fields.size() != 13) {
        std::cerr << "Wrong triangle format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vec3 p1 = vec3(fields[1].toDouble(),fields[2].toDouble(),fields[3].toDouble());
    vec3 p2 = vec3(fields[4].toDouble(),fields[5].toDouble(),fields[6].toDouble());
    vec3 p3 = vec3(fields[7].toDouble(),fields[8].toDouble(),fields[9].toDouble());


    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(p1),
                                                  mapping->mapeigPunt(p2),
                                                  mapping->mapeigPunt(p3),
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::TRIANGLE);

    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[10].toDouble(),fields[11].toDouble(),fields[12].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

}


void VirtualWorldReader::planeFound(QStringList fields) {
    // TODO Fase 1: Per incloure pla infinit
    // Es suposa que tindràs una línia en el fitxer
    // plane, nx, ny, nz, d, propietats del material, textura
    if (fields.size() != 9) {
        std::cerr << "Wrong plane format" << std::endl;
        return;
    }

    shared_ptr<Object> o;

    vec3 normalPla = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    float dPla = fields[4].toDouble();

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(normalPla,
                                                  dPla,
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::PLANE);
    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

    // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture

}

void VirtualWorldReader::fittedPlaneFound(QStringList fields) {
    // TODO Fase 1: Per incloure pla acotat. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
    // fittedplane, nx, ny, nz, d, propietats del material, textura
    if (fields.size() != 8) {
        std::cerr << "Wrong fitted plane format" << std::endl;
        return;
    }

    shared_ptr<Object> o;

    vec3 normalPla = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    float dPla = fields[4].toDouble();

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(normalPla,
                                                  dPla,
                                                  scene->pmin.x,
                                                  scene->pmax.x,
                                                  scene->pmin.z,
                                                  scene->pmax.z,
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::FITTEDPLANE);
    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

    // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture

}

void VirtualWorldReader::cylinderFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // cylinder, centre.x, centre.y, centre.z, radi, height, propietats del material, textura
    if (fields.size() != 9 ) {
        std::cerr << "Wrong cylinder format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  mapping->mapeigValor(fields[4].toDouble()),
                                                  mapping->mapeigValor(fields[5].toDouble()),
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::CYLINDER);
    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[6].toDouble(),fields[7].toDouble(),fields[8].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}
