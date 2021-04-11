#include "RayTracing.h"



// Metode raytracing principal

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel
// 3) Actualitza la sortida corresponent segons la implementació del mètode setPixelColor de cada fill

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

void RayTracing::rendering() {
    // Recorregut de cada pixel de la imatge final
    for (int y = cam->viewportY-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < cam->viewportX; x++) {

            vec3 col(0, 0, 0);
            for(int i = 0; i < numSamples; i++){
                float u = (float(x) + glm::linearRand(-0.5, 0.5))/ float(cam->viewportX);
                float v = (float(y) + glm::linearRand(-0.5, 0.5))/ float(cam->viewportY);
                Ray r = cam->getRay(u, v);
                col += scene->ComputeColor(r, 0, cam->getOrigin(), vec3(1));
            }

            col /= numSamples;
            setPixelColor(sqrt(col), x, y);

        }
    }
    std::cerr << "\nNumber ComputeColor calls: "<< scene->numCompColors;
    std::cerr << "\nDone.\n";
}

void RayTracing::exitRender() {

}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void RayTracing::startRendering(int argc, char **argv) {
    renderingScene();
}

void RayTracing::renderingScene()  {
    initRender(filename.toStdString());
    rendering();
    exitRender();
}

void RayTracing::setCamera(shared_ptr<Camera> c) {
    cam = c;
}
void RayTracing::setScene(shared_ptr<Scene> s) {
    scene = s;
}

void RayTracing::setOutputFile(QString output) {
    filename = output;
}



