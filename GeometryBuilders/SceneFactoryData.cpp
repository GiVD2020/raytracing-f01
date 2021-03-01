#include "SceneFactoryData.h"

SceneFactoryData::SceneFactoryData(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);
}


shared_ptr<Scene>  SceneFactoryData::createScene(QString filename) {

    auto scene = make_shared<Scene>();
    auto rdr = make_shared<RealDataReader>(scene);
    // TODO: Fase 1: construccio de l'escena dins de dataReader
    rdr->readFile(filename, map);
    return scene;
}

shared_ptr<Scene> SceneFactoryData::createScene() {
    auto scene= make_shared<Scene>();
    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui

    return scene;
}
