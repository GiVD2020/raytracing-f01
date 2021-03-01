#pragma once

#include "Ray.h"
#include "Hitable.h"
#include "Material.h"
#include "Lambertian.h"
#include "Animation.h"

using namespace std;
// Es la classe pare de tots els objectes que s'han de visualitzar.
// Es fa una classe Objectes que hereda de Hitable i ha d'implementar el metode intersection

class Object: public Hitable, public Animable {
  public:
    Object();
    Object(float d);
    virtual ~Object() {};

    // Metodes a implementar en les classes filles: son  metodes abstractes
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;
    virtual void aplicaTG(shared_ptr<TG>) = 0;

    float    getData();
    void     setMaterial(shared_ptr<Material> m);

    shared_ptr<Material> getMaterial();

protected:
    shared_ptr<Material> material;   // Material de l'objecte
    float data;           // valor samplejat per aquest objecte,
                          // en el cas que provingui d'un fitxer de dades
                          // sino, per defecte és -1
};

