#include "ConfigVisReader.h"



ConfigVisReader::ConfigVisReader(QString filename)
{
    readFile(filename);
}

RayTracingFactory::RENDER_TYPES ConfigVisReader::getRenderType() {
    return renderingType;
}


shared_ptr<Camera> ConfigVisReader::getCamera() {
    return(make_shared<Camera>(lookfrom, lookat, vup, vfov, aspect_ratio, width));
}

QString ConfigVisReader::getOutputFile() {
    return outputFile;
}

void ConfigVisReader::readFile(QString fileName) {
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


// TODO: Fase 2: Cal ampliar llegint les llums

void ConfigVisReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("renderType", fields[0], Qt::CaseInsensitive) == 0)
        renderTypeFound(fields);
    else if (QString::compare("lookFrom", fields[0], Qt::CaseInsensitive) == 0)
        lookFromFound(fields);
    else if (QString::compare("lookAt", fields[0], Qt::CaseInsensitive) == 0)
        lookAtFound(fields);
    else if (QString::compare("vup", fields[0], Qt::CaseInsensitive) == 0)
        vupFound(fields);
    else if (QString::compare("vfov", fields[0], Qt::CaseInsensitive) == 0)
        vfovFound(fields);
    else if (QString::compare("aspectRatio", fields[0], Qt::CaseInsensitive) == 0)
        aspectRatioFound(fields);
    else if (QString::compare("pixelsX", fields[0], Qt::CaseInsensitive) == 0)
        widthFound(fields);
    else if (QString::compare("output", fields[0], Qt::CaseInsensitive) == 0)
        fitxerFound(fields);
    else if (QString::compare("globalLight", fields[0], Qt::CaseInsensitive) == 0)
        globalLightFound(fields);
    else if (QString::compare("light", fields[0], Qt::CaseInsensitive) == 0)
        lightFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}


void ConfigVisReader::renderTypeFound(QStringList fields) {
    //rendertype IMAGE, ONLINE, TEMPORAL
    if (fields.size() != 2) {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    if (QString::compare("ONLINE", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::ONLINE;
    else if (QString::compare("IMAGE", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::IMAGE;
    else if (QString::compare("TEMPORAL", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::TEMPORAL;
    else std::cerr << "Error de sintaxi en el tipus de rendering" << std::endl;
}


void ConfigVisReader::lookFromFound(QStringList fields) {
    //lookFrom x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    lookfrom = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::lookAtFound(QStringList fields) {
    //lookAt x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    lookat = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::vupFound(QStringList fields) {
    //vup x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    vup = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::vfovFound(QStringList fields) {
    //vfov float
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    vfov = fields[1].toDouble();
}

void ConfigVisReader::aspectRatioFound(QStringList fields) {
    //aspectRatio float
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    aspect_ratio = fields[1].toDouble();
}

void ConfigVisReader::widthFound(QStringList fields) {
    //width integer in pixels
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    width = fields[1].toInt();
}
void ConfigVisReader::fitxerFound(QStringList fields) {
    //output nomFitxer
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    outputFile = fields[1];
}

void ConfigVisReader::globalLightFound(QStringList fields) {
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    globalLight = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::lightFound(QStringList fields) {
    if (!(fields.size() == 17 || fields.size() == 19 || fields.size() == 21)) {
        std::cerr << "Wrong data format!" << std::endl;
        return;
    }
    vec3 position = vec3(fields[2].toDouble(), fields[3].toDouble(), fields[4].toDouble());
    vec3 ambient = vec3(fields[5].toDouble(), fields[6].toDouble(), fields[7].toDouble());
    vec3 diffuse = vec3(fields[8].toDouble(), fields[9].toDouble(), fields[10].toDouble());
    vec3 specular = vec3(fields[11].toDouble(), fields[12].toDouble(), fields[13].toDouble());
    double a,b,c;
    a = fields[14].toDouble();
    b = fields[15].toDouble();
    c = fields[16].toDouble();

    if (QString::compare("noTypeYet", fields[1], Qt::CaseInsensitive) == 0){
        pointLights.push_back(make_shared<Light>(position, ambient, diffuse, specular, a, b, c));
    } else if (QString::compare("sphericalLight", fields[1], Qt::CaseInsensitive) == 0){
        int numLights = fields[17].toInt();
        double radius = fields[18].toDouble();
        vec3 p;
        for (int i=0; i < numLights; i++) {
            do {
                p = 2.0f*vec3(double(rand())/RAND_MAX, double(rand())/RAND_MAX,double(rand())/RAND_MAX) - vec3(1,1,1);
            } while (glm::length(p) >=  1.0f);
            p = p * vec3(radius);
            pointLights.push_back(make_shared<Light>(position + p, ambient/vec3(numLights*1.0), diffuse/vec3(numLights*1.0), specular/vec3(numLights*1.0), a, b, c));
        }
    } else if (QString::compare("linearLight", fields[1], Qt::CaseInsensitive) == 0){
        int numLights = fields[17].toInt();
        vec3 finalPosition = vec3(fields[18].toDouble(), fields[19].toDouble(), fields[20].toDouble());
        for (int i=0; i < numLights; i++) {
            pointLights.push_back(make_shared<Light>(position + vec3(i*1.0/numLights)*(finalPosition - position), ambient/vec3(numLights*1.0), diffuse/vec3(numLights*1.0), specular/vec3(numLights*1.0), a, b, c));
        }
    } else {
        std::cerr << "Wrong light type" << std::endl;
        return;
    }
}

std::vector<shared_ptr<Light>> ConfigVisReader::getPointLights(){
    return pointLights;
}

vec3 ConfigVisReader::getGlobalLight(){
    return globalLight;
}
