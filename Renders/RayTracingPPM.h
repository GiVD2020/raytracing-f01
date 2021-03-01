#pragma once

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include "RayTracing.h"

class RayTracingPPM: public RayTracing {
protected:
    ofstream myfile;
public:
    RayTracingPPM();
    virtual ~RayTracingPPM();

    virtual void initRender(string nomFitxer);
    virtual void setPixelColor(vec3 col, int x, int y);
    virtual void exitRender();

};


