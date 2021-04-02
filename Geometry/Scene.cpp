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
            info.indObject = i;
        }
    }
    // hit of the floor
    if (floor.isVisible()) {
        if (floor.hit(raig, t_min, minim_t, info)) {
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
vec3 Scene::ComputeColor (Ray &ray, int depth, vec3 lookFrom) {

    vec3 color;
    vec3 recColor = vec3(0);
    vec3 scatterColor;
    vec3 ray2;
    vector<Ray> reflected;
    ray2 = normalize(ray.dirVector());

    HitInfo info;
    if (hit(ray, 0, 100, info)){
        //Segons el color que ens dona Blinn-Phong:
        color = blinn_phong(ray, info, lookFrom);
        if (depth == MAXDEPTH) {
            return color;
        }
        info.mat_ptr->scatter(ray, info, scatterColor, reflected);
        int reflectedAmount = reflected.size();
        for (int i = 0; i < reflectedAmount; i++) {
            recColor += ComputeColor(reflected[i], depth+1, lookFrom);
        }
        recColor /= max({1, reflectedAmount});
        //return (vec3(1)-info.mat_ptr->k)*color + recColor * scatterColor;
        return color + recColor * scatterColor;// Blinn-phong al transparent
    } else {
        if (depth == 0) {
            vec3 color1 = vec3(0.5, 0.7, 1);
            vec3 color2 = vec3(1, 1 ,1);
            // TODO: A canviar el càlcul del color en les diferents fases
            double y = 0.5*(ray2.y+1);
            color = (float)y*color1 + (float)(1-y)*color2;
            return color;
        }
        return globalLight;
    }

}

vec3 Scene::blinn_phong(Ray &ray, HitInfo &info, vec3 lookFrom){
    vec3 ca = vec3(0,0,0);
    vec3 cd = vec3(0,0,0);
    vec3 cs = vec3(0,0,0);
    vec3 diffuse;
    vector<HitInfo> infoOmbra;
    //Per cada Light
    for(int i=0; i<pointLights.size(); i++){
        //Component ambient
        ca += info.mat_ptr->ambient * this->pointLights[i]->ambient;
        diffuse = info.mat_ptr->getDiffuse(info.uv);

        float atenuacio = this->pointLights[i]->get_atenuation(info.p);

        float factorOmbra = shadowCalculation(info.p, this->pointLights[i]->position);

        //Component difusa amb atenuacio
        cd += factorOmbra*atenuacio*this->pointLights[i]->diffuse * diffuse*
                std::max(dot(info.normal, glm::normalize(pointLights[i]->get_vector_L(info.p))), 0.0f);
        vec3 H = normalize(lookFrom-info.p + pointLights[i]->get_vector_L(info.p));
        //vec3 H = normalize(-ray.dirVector() + pointLights[i]->get_vector_L(info.p));

        //Component especular amb atenuacio
        cs += factorOmbra*atenuacio*this->pointLights[i]->specular * info.mat_ptr->specular*
                pow(std::max(dot(info.normal, H), 0.0f), info.mat_ptr->shineness);
    }

    vec3 global = this->globalLight*info.mat_ptr->ambient;

    //Ambient occlusion: suposem escenes outdoor i llancem n raigs aleatoris des de p cap al 'cel'
    float AOFactor = 1;
    if(AOACTIVATED) {
        AOFactor = ambientOcclusionFactor(info);
    }

    //Retornem la llum ambient global més les tres components
    return  AOFactor*global + ca + cd + cs;
}


bool Scene::hitOmbra(vector<HitInfo>& infoOmbra, vec3 point, vec3 lightPosition) {
    vec3 director = normalize(lightPosition - point);
    float tMax = length(lightPosition - point);
    Ray shadowRay = Ray(point, director);
    HitInfo info;
    int indBefore = -1;
    while (hit(shadowRay, EPSILON, tMax, info)) {
        //Si hi ha un objecte Lambertian no calcularem aquesta ombra
        if(dynamic_cast<Lambertian*>(info.mat_ptr)) {
            return false;
        }
        if(indBefore != info.indObject) {
            infoOmbra.push_back(info);
            shadowRay.origin = info.p;
            tMax = length(lightPosition - info.p);
        }
        indBefore = info.indObject;
    }
    //Ara toca ordenar el vector d'objectes de mes proper a menys proper
    //TODO
    return true;
}

float Scene::ambientOcclusionFactor(HitInfo info) {
    vec3 rayOrigin;
    vec3 rayDir;
    HitInfo rayInfo;
    int numSkyRays = 0;
    for(int i = 0; i < NUMRAYSAO; i++) {
        rayDir = info.normal + info.mat_ptr->RandomInSphere();
        rayOrigin = info.p + 0.01f*rayDir;
        if(!hit(Ray(rayOrigin, rayDir), 0, 100, rayInfo)) {
            numSkyRays ++;
        }
    }
    return numSkyRays/NUMRAYSAO;
}

float Scene::shadowCalculation(vec3 point, vec3 lightPosition) {
    vec3 director = normalize(lightPosition - point);
    float tMax = length(lightPosition - point);
    float tMin = 0.01; //Should be 0.0 but to avoid shadow acne must be some small epsilon
    Ray shadowRay = Ray(point, director);
    HitInfo info = HitInfo();
    if (this->hit(shadowRay, tMin, tMax, info)) {
        return 0.0;
    } else {
        return 1.0;
    }
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

void Scene::setGlobalLight(vec3 globalLight){
    this->globalLight = globalLight;
}

void Scene::setPointLights(vector<shared_ptr<Light>> pointLights){
    for (unsigned int i = 0; i< pointLights.size(); i++){
        this->pointLights.push_back(pointLights[i]);
    }
}
