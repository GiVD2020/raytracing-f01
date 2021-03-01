#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}


vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
    // TO DO Fase 1:
    // Mapeig del punt en coordenades reals a coordenades de mon virtual
      vec3 puntMonVirtual;

      // Cal posar el codi per a situar el punt del mon Real al Virtual
      // Cal canviar la següent línia
      puntMonVirtual = puntMonReal;

      return puntMonVirtual;
}

float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1:
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
      double valorMonVirtual;

   // Cal canviar la següent línia
      valorMonVirtual = valorMonReal;

      return valorMonVirtual;
}

shared_ptr<ColorMap> Mapping::getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM) {
   auto cm = make_shared<ColorMapStatic>(ColorMapStatic::COLOR_MAP_TYPE_PLASMA);
   return cm;
}

shared_ptr<Material> Mapping::mapeigMaterial(int i, ColorMapStatic::COLOR_MAP_TYPES tCM, double valorMonReal) {

    // TO DO Fase 2: Cal mapejar el color difus al color de la paleta o ColorMap segons el valorMonReal i
    // els valors minims i maxims de les propietats
    // Tens els valors minims i maxim de cada propietat a l'estructura de setup d'aquesta classe

    auto cm = getColorMap(tCM);
    int idx = 255*int(valorMonReal/(setup->propLimits[i].second-setup->propLimits[i].first));

    return make_shared<Lambertian>(cm->getColor(idx));
}
