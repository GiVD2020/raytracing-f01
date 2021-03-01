#pragma once

#include <string.h>

#include "DataService/ConfigMappingReader.h"
#include "Geometry/ColorMap.h"
#include "Geometry/ColorMapStatic.h"
#include "Geometry/Material.h"
#include "GeometryBuilders/ObjectFactory.h"

#include <QString>

using namespace std;



class Mapping
{
public:

    Mapping();
    Mapping(const shared_ptr<ConfigMappingReader> configMapping);

    vec3  mapeigPunt(vec3 puntMonReal);
    float mapeigValor(float valorMonReal);

    shared_ptr<Material> mapeigMaterial(int i, ColorMapStatic::COLOR_MAP_TYPES tCM, double valorReal);

    int getNumProps() { return setup->numProp; };


    ObjectFactory::OBJECT_TYPES getObjectTypeProp(int i) {
        return setup->props[i].first;
    }

    ColorMapStatic::COLOR_MAP_TYPES getColorMapProp(int i) {
        return setup->props[i].second;
    }

    shared_ptr<ColorMap> getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM);


private:
    shared_ptr<ConfigMappingReader> setup;
};

