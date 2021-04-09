#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {


    cout << "Init..." <<endl;

    Q_INIT_RESOURCE(resources);
    //auto controller = make_shared<Controller>("://resources/dataBCN.txt", "://resources/configMappingDataBCN.txt", "://resources/configVisDataBCN.txt");
    //auto controller = make_shared<Controller>("://resources/spheres.txt", "://resources/configMapping_Fase2A.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/boundaryObject.txt", "://resources/configMapping.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/3D_Scene_myScene.txt", "://resources/configMapping.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/Scene_Fase2A.txt", "://resources/configMapping_Fase2A.txt", "://resources/configVis.txt");
    auto controller = make_shared<Controller>("://resources/sphere.txt", "://resources/configMapping_Fase2A.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/dadesEuropa.txt", "://resources/configMappingDataEuropa.txt", "://resources/configVisDataEuropa.txt");
    //auto controller = make_shared<Controller>("://resources/dadesEuropa.txt", "://resources/configMappingDataEuropa.txt", "://resources/configVisDataEuropa.txt");
    //auto controller = make_shared<Controller>("://resources/Scene_TemporalVW.txt", "://resources/configMappingDataTemporalVW.txt", "://resources/configVisDataTemporalVW.txt");
    controller->start(argc, argv);

    return(0);
}
