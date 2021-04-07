#pragma once

#include <string.h>

#include "DataService/ConfigMappingReader.h"
#include "Geometry/ColorMap.h"
#include "Geometry/ColorMapStatic.h"
#include "Geometry/Material.h"
#include "GeometryBuilders/ObjectFactory.h"
#include "Geometry/Translate.h"
#include "Geometry/ScaleTG.h"

#include <QString>

using namespace std;



class Mapping
{
public:

    Mapping();
    Mapping(const shared_ptr<ConfigMappingReader> configMapping);

    vec3  mapeigPunt(vec3 puntMonReal);
    float mapeigValor(float valorMonReal);
    float mapeigValor(int i ,float valorMonReal);

    shared_ptr<Material> mapeigMaterial(int i, ColorMapStatic::COLOR_MAP_TYPES tCM, double valorReal);

    int getNumProps() { return setup->numProp; };

    vec3 getNormalBasePlane(){ return setup->normalPlaBase; };
    float getdBasePlane(){ return setup->dPlaBase; };
    shared_ptr<Texture> getTextureBasePlane(){return setup->texturePlaBase; };
    vec3 getVirtualMaxCoord(){ return setup->Vmax; };
    vec3 getVirtualMinCoord(){ return setup->Vmin; };

    shared_ptr<TG> getMapeigRealAVirtual();
    shared_ptr<ScaleTG> getEscalat(int iProp, float valorMonReal);


    ObjectFactory::OBJECT_TYPES getObjectTypeProp(int i) {
        return setup->props[i].first;
    }

    ColorMapStatic::COLOR_MAP_TYPES getColorMapProp(int i) {
        return setup->props[i].second;
    }

    shared_ptr<ColorMap> getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM);

    Scene::DATA_TYPES    getDataType();
    int                  getNumFrames();
private:
    shared_ptr<ConfigMappingReader> setup;
};

