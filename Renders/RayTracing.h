#pragma once

#include "Geometry/Scene.h"
#include "Camera.h"

class RayTracing
{
private:
    int numSamples = 10;
protected:
    // Scene: scena virtual dels objectes amb els seus materials i textures i les llums
    shared_ptr<Scene> scene;
    // Camera: on está l'observador
    shared_ptr<Camera> cam;
    QString filename;


public:

    void setScene(shared_ptr<Scene> s);
    void setCamera(shared_ptr<Camera> c);
    void setOutputFile(QString output);

    virtual void startRendering(int argc, char **argv);

    virtual void initRender(string nomFitxer) = 0;
    virtual void setPixelColor(vec3 color, int x, int y) = 0;
    virtual void exitRender();

    // rendering: metode principal de Raytracing
    void rendering();

    // renderingScene: metode que fa les inicialitzacions, el rendering i el final segons
    // en quin render es faci: PPM, GLU o animacio
    virtual void renderingScene();

};


