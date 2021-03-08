#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}


vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
      // TO DO Fase 1 (FET):
      // Mapeig del punt en coordenades reals a coordenades de mon virtual
      // Cal posar el codi per a situar el punt del mon Real al Virtual
      // Cal canviar la següent línia
      vec3 Rmin = vec3(this->setup->Rxmin, this->setup->Rymin, this->setup->Rzmin);
      vec3 Rmax = vec3(this->setup->Rxmax, this->setup->Rymax, this->setup->Rzmax);
      vec3 Vmin = vec3(this->setup->Vxmin, this->setup->Vymin, this->setup->Vzmin);
      vec3 Vmax = vec3(this->setup->Vxmax, this->setup->Vymax, this->setup->Vzmax);

      return (puntMonReal - Rmin) / (Rmax - Rmin) * (Vmax - Vmin) + Vmin;
}

float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1 (FET):
    // Es fa un mapejat (minR, maxR) -> (minV, maxV), però agafant l'eix amb menor diferèncie en cada cas!
        float diffXV = setup->Vxmax - setup->Vxmin;
        float diffYV = setup->Vymax - setup->Vymin;
        float diffZV = setup->Vzmax - setup->Vzmin;
        float minDiffV = min({diffXV, diffYV, diffZV});
        float diffXR = setup->Vxmax - setup->Vxmin;
        float diffYR = setup->Vymax - setup->Vymin;
        float diffZR = setup->Vzmax - setup->Vzmin;
        float minDiffR = min ({diffXR, diffYR, diffZR});

        return valorMonReal / minDiffR * minDiffV;
}

float Mapping::mapeigValor(int i, float valorMonReal){
    // TO DO Fase 1 (FET):
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
    // (mínim propietat, màxim propietat) -> (0, minDiff), on minDiff és el mínim rang entre el màxim i mínim valor a cada eix (configMapping.txt)
      float diffXV = setup->Vxmax - setup->Vxmin;
      float diffYV = setup->Vymax - setup->Vymin;
      float diffZV = setup->Vzmax - setup->Vzmin;
      float minDiffV = min({diffXV, diffYV, diffZV});
      float minProp = setup->propLimits[i].first;
      float maxProp = setup->propLimits[i].second;
      return (valorMonReal - minProp)/ (maxProp - minProp) * minDiffV;
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
