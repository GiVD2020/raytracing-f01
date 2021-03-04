#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {


    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);

    auto controller = make_shared<Controller>("://resources/data0.txt", "://resources/configMappingData0.txt", "://resources/configVis.txt");

    controller->start(argc, argv);

    return(0);
}
