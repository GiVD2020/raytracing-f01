#pragma once

#include <GL/glut.h> //OpenGL Utility Toolkits

#include "RayTracing.h"

extern RayTracing *rIntern;

void RenderingSceneGLU();

class RayTracingGLU: public RayTracing
{
public:
    RayTracingGLU();
    virtual ~RayTracingGLU();

    virtual  void startRendering(int argc, char **argv);

    virtual  void initRender(string nomFitxer);
    virtual  void setPixelColor(vec3 col, int x, int y);
    virtual  void exitRender();

private:
    void (*f_render)();
};


