#include "Scene.h"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}


/*
** TODO: FASE 1: Metode que testeja la interseccio contra tots els objectes de l'escena
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {


    // TODO FASE 0 i FASE 1: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode intersection per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el IntersectionInfo del raig,
    // pero no en aquesta funcio.

    float minim_t = t_max;
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (objects[i]->hit(raig, t_min, minim_t, info)) {
            minim_t = info.t;
        }
    }
    if (abs(minim_t - t_max) < 0.0001) {
        return false;
    }
    return true;
}


/*
** TODO: Funcio ComputeColorRay es la funcio recursiva del RayTracing.
** TODO: FASE 0 per a fer el degradat del fons
** TODO: FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::ComputeColor (Ray &ray, int depth ) {

    vec3 color;
    vec3 ray2;
    ray2 = normalize(ray.direction);

    HitInfo info;
    if (hit(ray, 0, 100, info)){
        //Segons el color del material de l'objecte:
        //color = info.mat_ptr->diffuse;
        //Segons el color de les normals en els punts d'intersecció
        color = 0.5f*vec3(info.normal.x + 1, info.normal.y + 1, info.normal.z + 1);
    } else {
        vec3 color1 = vec3(0.5, 0.7, 1);
        vec3 color2 = vec3(1, 1 ,1);
        // TODO: A canviar el càlcul del color en les diferents fases
        double y = 0.5*(ray2.y+1);
        color = (float)y*color1 + (float)(1-y)*color2;
    }

    return color;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}



void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

