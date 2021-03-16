#include "Controller.h"

Controller::Controller(QString dataFileName, QString configMapping, QString configVis)
{
    //
    // ETAPA 1: Carrega l'escena a visualitzar
    // a. A partir de dades virtuals (ja siguin construïdes pel programa o objectes .obj)
    // b. A partir de dades geolocalitzades
    // Ambdos casos necessiten un mappeig al món virtual a visualitzar (localitzant els objectes i definint els materials)

       shared_ptr<ConfigMappingReader> mapping = make_shared<ConfigMappingReader>(configMapping);
       auto factory = getFactory(mapping);

       shared_ptr<Scene> scene;
       scene = factory->createScene(dataFileName);

    // ETAPA 2: Configuració de la visualització
    // a. Definició de la càmera
    // b. Definició del viewport
    // c. Set up de l'escena

    // Us del fitxer extern per definir la configuracio de visualització
    auto visSetup = make_shared<ConfigVisReader>(configVis);

    // TODO Fase 1: Cal posar les dimensions de l'escena virtual usant setDimensions de la classe Scene (FET)
    vec3 pmin(mapping->Vxmin,mapping->Vymin, mapping->Vzmin);
    vec3 pmax(mapping->Vxmax, mapping->Vymax, mapping->Vzmax);
    scene->setDimensions(pmin, pmax);
    //FASE2: posem llums a l'escenar
    scene->setGlobalLight(visSetup->getGlobalLight());
    scene->setPointLights(visSetup->getPointLights());
    // ETAPA 2: Inicialitzacio del Rendering
    // usa un  Template Factory per a construir el tipus de render
     render = RayTracingFactory::getInstance()->getRender(visSetup->getRenderType(), visSetup->getOutputFile());
     render->setScene(scene);
     render->setCamera(visSetup->getCamera());

}

void Controller::start(int argc, char **argv) {
    // ETAPA 2: Activació del Rendering
    render->startRendering(argc, argv);
}

shared_ptr<SceneFactory> Controller::getFactory(shared_ptr<ConfigMappingReader> cf) {

    if(cf->dataType == Scene::DATA_TYPES::VIRTUALWORLD)
    {
        return make_shared<SceneFactoryVirtual>(cf);
    }
    else if(cf->dataType == Scene::DATA_TYPES::REALDATA)
    {
        return make_shared<SceneFactoryData>(cf);
    }

    //TO DO:  Afegir les factories de dades temporals en les animacions
    return nullptr;
}



