#pragma once

#include "glm/glm.hpp"
#include "TG.h"
#include <vector>
#include <math.h>       /* cos */

#define PI 3.14159265
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__linux__)
    #include <memory>
#endif

using namespace std;

//NO S'UTILITZA
class Animation
{
public:
 int frameIni;
 int frameFinal;
 shared_ptr<TG> transf;

 Animation(): frameIni(0), frameFinal(10), transf(NULL) {}

 //  "operator =" per la classe  Animation
 Animation &operator =(const Animation &rhs) {
   frameIni = rhs.frameIni;
   frameFinal = rhs.frameFinal;
   transf = rhs.transf;
   return *this;
 }
};
//ANIMACIONS VIRTUALWORLD
class CustomAnimation
{
public:
    int frameDuration; //Quant triga en completar-se 1 cicle de l'animació
    virtual ~CustomAnimation() {};
};

class EllipseAnimation : public CustomAnimation
{
public:
    float xRadius, zRadius;
    EllipseAnimation(float fD, float xR, float zR){
        frameDuration = fD;
        xRadius = xR;
        zRadius = zR;
    }
    /*
    * Simula elipse en el pla y = 0:
    */
    glm::vec3 getPosition(glm::vec3 center, int nFrame){
        float t = float(nFrame) / float(frameDuration) * 2 * PI;
        glm::vec3 ret= glm::vec3(center.x + xRadius * cos(t), 0 , center.z + zRadius * sin(t));
        return ret;
    }
    ~EllipseAnimation(){

    }
};

class Animable {
public:
    Animable();
    ~Animable();

    void addAnimation(shared_ptr<Animation> anim);

    std::vector<shared_ptr<Animation>> animFrames;
    // update recorre la llista de frames per detectar quina animació aplicar.
    // crida a aplicaTG quan l'ha trobada
    void update(int nframe); //NO IMPLEMENTAT
    // Obliga als objectes que tenen animacions implementar aquest mètode
    virtual void aplicaTG(shared_ptr<TG> tg) = 0;
    // ANIMAR OBJECTES DE VIRTUALWORLD:
    std::vector<shared_ptr<CustomAnimation>> animations;
    void applyAnimations(int nframe);
    virtual void applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame) = 0;
};


