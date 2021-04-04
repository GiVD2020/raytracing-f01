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

void VirtualWorldReader::sphereFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // sphere, centre.x, centre.y, centre.z, radi, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta
    shared_ptr<Object> o;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  mapping->mapeigValor(fields[4].toDouble()),
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::SPHERE);
    readMaterialAndAnimation(fields, 5, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}


void VirtualWorldReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    //  brobject, nomDelFitxer, propietats del material, textura
    // brobject,path, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta

    QString s = fields[1];

    shared_ptr<Object> o;

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(s,
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::BR_OBJECT);

    //LLegir material i animació (en cas de TemporalVW)
    readMaterialAndAnimation(fields, 2, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

}

void VirtualWorldReader::triangleFound(QStringList fields) {

    // TODO Fase 1: Per incloure Triangle
    //  Es suposa que serà una linia del fitxer de l'estil
    //  triangle, x1, y1, z1, x2, y2, z2, x3, y3, z3, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta

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

    //LLegir material i animació (en cas de TemporalVW)
    readMaterialAndAnimation(fields, 10, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

}


void VirtualWorldReader::planeFound(QStringList fields) {
    // TODO Fase 1: Per incloure pla infinit
    // Es suposa que tindràs una línia en el fitxer
    // plane, nx, ny, nz, d, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta
    shared_ptr<Object> o;

    vec3 normalPla = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    float dPla = fields[4].toDouble();

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(normalPla,
                                                  dPla,
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::PLANE);

    //LLegir material i animació (en cas de TemporalVW)
    readMaterialAndAnimation(fields, 5, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);

    // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture

}

void VirtualWorldReader::fittedPlaneFound(QStringList fields) {
    // TODO Fase 1: Per incloure pla acotat. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
    // fittedplane, nx, ny, nz, d, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta
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

    //LLegir material i animació (en cas de TemporalVW)
    readMaterialAndAnimation(fields, 5, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);


}

void VirtualWorldReader::cylinderFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // cylinder, centre.x, centre.y, centre.z, radi, height, 3 float (ambient), 3 float (diffuse), 3 float (specular), beta
    shared_ptr<Object> o;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  mapping->mapeigValor(fields[4].toDouble()),
                                                  mapping->mapeigValor(fields[5].toDouble()),
                                                  -1.0f,
                                                  ObjectFactory::OBJECT_TYPES::CYLINDER);

    //LLegir material i animació (en cas de TemporalVW)
    readMaterialAndAnimation(fields, 6, o);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}

void VirtualWorldReader::readMaterialAndAnimation(QStringList fields, int startIndex, shared_ptr<Object> o){
    int i = startIndex;
    int j = i + 11;
    // Construccio i assignacio del material
    vec3 ambient = vec3(fields[i].toDouble(),fields[i+1].toDouble(),fields[i+2].toDouble());
    vec3 diffuse =vec3(fields[i+3].toDouble(),fields[i+4].toDouble(),fields[i+5].toDouble());
    vec3 specular= vec3(fields[i+6].toDouble(),fields[i+7].toDouble(),fields[i+8].toDouble());
    float shineness = fields[i+9].toDouble();

    if (QString::compare("LAMBERTIAN", fields[i+10], Qt::CaseInsensitive) == 0) {
        auto mat = make_shared<Lambertian>(ambient, diffuse, specular, shineness);
        o->setMaterial(mat);
    } else if (QString::compare("METAL", fields[i+10], Qt::CaseInsensitive) == 0) {
        auto mat = make_shared<Metal>(ambient, diffuse, specular, shineness);
        o->setMaterial(mat);
    } else if (QString::compare("TRANSPARENT", fields[i+10], Qt::CaseInsensitive) == 0) {
        vec3 k = vec3(fields[i+11].toDouble(), fields[i+12].toDouble(),fields[i+13].toDouble());
        float refractionRatio = fields[i+14].toDouble();
        j = i + 15;
        auto mat = make_shared<Transparent>(ambient, diffuse, specular, shineness, k, refractionRatio);
        o->setMaterial(mat);
    }else if(QString::compare("TEXTURE", fields[i+10], Qt::CaseInsensitive) == 0){
        shared_ptr<Texture> tex = make_shared<Texture>(fields[i+11]);
        auto mat = make_shared<MaterialTextura>(ambient,diffuse,specular,shineness, tex);
        o->setMaterial(mat);
        j = i + 12;
    }
    else {
        std::cerr << "Wrong material name (" << fields[i+10].toStdString() << ")" << std::endl;
        return;
    }

    //Check for animation:
    if(mapping->getDataType() == Scene::DATA_TYPES::TEMPORALVW){
        //Un objecte pot tenir més d'una animació, es van llegint sequencialment:
        while(fields.size() >= j + 1){
            if(QString::compare("ELLIPSE", fields[j], Qt::CaseInsensitive) == 0){
                float xRadius = fields[j+1].toFloat();
                float zRadius = fields[j+2].toFloat();
                int framesPerVolta = fields[j+3].toInt();
                cout << "Animació: Ellipse: " << "Radi eix x " << xRadius << " | Radi eix z " << zRadius << " | Frames per volta " << framesPerVolta << endl;
                o->animations.push_back(make_shared<EllipseAnimation>(framesPerVolta, xRadius, zRadius));
                j = j+4;
            }
        }
    }
}

