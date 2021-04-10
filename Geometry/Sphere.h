/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef SPHEREH
#define SPHEREH

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Translate.h"
#include "MaterialTextura.h"

class Sphere: public Object  {
public:
        Sphere(vec3 cen, float r, float data);
        virtual ~Sphere() {}
        virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
        virtual void aplicaTG(shared_ptr<TG> tg) override;
        virtual void applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame) override;
private:
        //Animation purposes:
        vec3 initCenter;
        // Centre de l'esfera
        vec3 center;
        // Radi de l'esfera
        float radius;
        //Angle (per animació de rotació)
        float angle;

};


#endif



