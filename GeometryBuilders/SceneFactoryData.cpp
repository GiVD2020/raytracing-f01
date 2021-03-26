#include "SceneFactoryData.h"
#include "Geometry/FittedPlane.h"

SceneFactoryData::SceneFactoryData(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);
}


shared_ptr<Scene>  SceneFactoryData::createScene(QString filename) {

    auto scene = make_shared<Scene>();
    auto rdr = make_shared<RealDataReader>(scene);
    // TODO: Fase 2E: Invertir eix Z mapeig

    // TODO: Fase 1: construccio de l'escena dins de dataReader
    rdr->readFile(filename, map);
    // FASE 1 posar fitted plane (FET Martí)
    vec3 normal = map->getNormalBasePlane();
    float d = map->getdBasePlane();
    vec3 vmax = map->getVirtualMaxCoord();
    vec3 vmin = map->getVirtualMinCoord();
    FittedPlane floor(normal, d, vmin.x, vmax.x, vmin.z, vmax.z, 0.0);
    //TODO: Provisional Fase 2 E
    auto mat = make_shared<Lambertian>(vec3(0.1,0.1,0.1),vec3(0.7,0.4,0.4),vec3(0.0,0.0,0.0),0);
    floor.setMaterial(mat);
    scene->floor = floor;
    return scene;
}

shared_ptr<Scene> SceneFactoryData::createScene() {
    auto scene= make_shared<Scene>();
    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui

    return scene;
}
