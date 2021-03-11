#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}

//Aquesta es crida des de VirtualWorldReader
vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
      // TO DO Fase 1 (FET):
      // Mapeig del punt en coordenades reals a coordenades de mon virtual
      // Cal posar el codi per a situar el punt del mon Real al Virtual
      // Cal canviar la següent línia
      vec3 Rmin = this->setup->Rmin;
      vec3 Rmax = this->setup->Rmax;
      vec3 Vmin = this->setup->Vmin;
      vec3 Vmax = this->setup->Vmax;

      return (puntMonReal - Rmin) / (Rmax - Rmin) * (Vmax - Vmin) + Vmin;
}

//Aquesta es crida des de VirtualWorldReader
float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1 (FET):
    // Es fa un mapejat (minR, maxR) -> (minV, maxV), però agafant l'eix amb menor diferèncie en cada cas!
    return valorMonReal / this->setup->RminDiff * this->setup->VminDiff;
}

shared_ptr<TG> Mapping::getMapeigRealAVirtual(){
    vec3 Rmin = this->setup->Rmin;
    vec3 Rmax = this->setup->Rmax;
    vec3 Vmin = this->setup->Vmin;
    vec3 Vmax = this->setup->Vmax;
    vec3 vDiv = vec3(1,1,1)/(Rmax - Rmin);
    vDiv.y = 0;
    glm::mat4 restamR = glm::translate(glm::mat4(1.0f), -Rmin);
    glm::mat4 divisioRDiff = glm::scale(glm::mat4(1.0f), vDiv);
    glm::mat4 vDiff = glm::scale(glm::mat4(1.0f), Vmax - Vmin);
    glm::mat4 sumaVmin = glm::translate(glm::mat4(1.0f), Vmin);
    //Ordre invers (matrius no són commutatives i es multiplicarà el punt per la dreta)
    auto tg = make_shared<TG>(sumaVmin*vDiff*divisioRDiff*restamR);
    return tg;
}

shared_ptr<ScaleTG> Mapping::getEscalat(int iProp, float valorMonReal){
    float minProp = setup->propLimits[iProp].first;
    float maxProp = setup->propLimits[iProp].second;
    float factor = (valorMonReal - minProp) / (maxProp - minProp) * setup->VminDiff;
    auto tg = make_shared<ScaleTG>(vec3(factor, factor, factor));
    return tg;
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
