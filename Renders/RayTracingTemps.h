#pragma once

#include "RayTracingPPM.h"

class RayTracingTemps : public RayTracingPPM
{

public:
    RayTracingTemps(int numFrames);
    virtual ~RayTracingTemps();

    virtual void renderingScene();

private:
    int numFrames;
};

