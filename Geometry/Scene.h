#pragma once


#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Animation.h"
#include "Object.h"
#include "Sphere.h"
#include "FittedPlane.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "Transparent.h"
#include "Metal.h"
#include "ColorMap.h"
#include "Light.h"

class Scene: public Hitable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW,
           TEMPORALDATA
    } DATA_TYPES;

    typedef enum
    {
        MATERIAL,
        COLORMAP
    } MATERIAL_TYPES;

    Scene();
    virtual ~Scene() {};

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth, vec3 lookFrom);

    void update(int nframe);

    void setDimensions(vec3 p1, vec3 p2);

    // dimensions de l'escena virtual
    vec3 pmin, pmax;

    FittedPlane floor;

    // Vector d'objectes continguts a l'escena
    std::vector<shared_ptr<Object>> objects;

    // TODO FASE 2: Afegir llums a l'escena
    void setGlobalLight(vec3 globalLight);
    void setPointLights(vector<shared_ptr<Light>> pointLights);

    float shadowCalculation(vec3 point, vec3 lightPosition);
private:
    vector<shared_ptr<Light>> pointLights;
    vec3 globalLight;
    vec3 blinn_phong(Ray &ray, HitInfo &info, vec3 lookFrom);
    static const int MAXDEPTH = 0;

    constexpr static const double EPSILON = 1e-04;
};

