# RayTracingGiVD 2020-21 (WIP)

En aquest readme mostrarem els resultats que hem obtingut seguint el guió proposat, així com escenes extres que hem creat i parts opcionals que decidit implementar.

## Fase 0

La fase 0 és una fase premiliminar en la qual l'objectiu era familiaritzar-se amb el projecte i obtenir les primeres visualitzacions.

La primera que vam obtenir va ser el background de l'escena, un degradat des del blau RGB(0.5, 0.7, 1) fins el blanc RGB(1,1,1).

![background](/readmeFiles/fase0/fase0_background.png)

Les esferes ja estaven implementades al projecte i nosaltres vam implementar el mètode `hit` per detectar la col·lisió dels rajos del RayTracing amb les esferes de l'escena. Un cop implementat això i utilitzant la normal del raig sobre cada punt de l'objecte com a color, aquest és el resultat obtingut amb una sola esfera.

![sphere](/readmeFiles/fase0/fase0_sphere.png)

Afegint més esferes a l'escena i canviant certs paràmetres de la càmera com el `vfov` i el `lookFrom`, hem obtingut la següent imatge.

![spheres](/readmeFiles/fase0/fase0_spheres.png)

Els fitxers `configVis.txt` i `spheres.txt` utilitzats per obtenir la visualització anterior es troben al directori readmeFiles/fase0.

## Fase 1

L'objectiu de la fase 1 era construïr una escena virtual, utilitzant tant dades virtuals (esferes, triangles, cilindres...) com dades reals representades en una escena virtual. Tot i que les visualitzacions d'aquesta fase continuïn en un estat molt preliminar, tot el codi que hem fet a aquesta fase ens ha serveix per poder fer visualitzacions més interessants a la fase 2 i 3.

Les tasques d'aquesta fase es divideixen en dues parts molt diferenciades però complementàries:
- les que inclouen els nous tipus d'objectes i les seves interseccions a partir d'una escena
`VIRTUALWORLD`
- les que situen creen l'escena corresponent a les dades geolocalitzades a partir d'un fitxer de
dades `REALDATA`

### VIRTUALWORLD

_Nota: En aquesta fase, tot i que els objectes tenen atribut `diffuse` que es pot utilitzar com a color de l'objecte, mostrarem les visualitzacions utilitzant com a color la normal del raig que intersecta cada punt de l'objecte, ja que ajuda a diferenciar millor les formes 3D._

El primer que se'ns demanava era la implementació dels objectes tipus `Triangle`, amb el seu hit corresponent. Els triangles consisteixen en 3 punts (`vec3`) que corresponen als tres vèrtexs del triangle. A continuació podem veure 3 triangles situats a una escena virtual.

![triangles](/readmeFiles/fase1/triangles.png)
    
Pel cas dels `boundaryObject`, que són malles poligonals, els hem implentat utilitzant directament l'objecte `Triangle`que acabem de crear, i al seu mètode hit no hem fet res més que utilitzar el hit del conjunt de triangles que formen la malla triangular. Un exemple és `cube.obj`, un objecte que se'ns proporcionava i que utilitza 12 triangles per formar les 6 cares del cub. Hem obtingut la visualització següent.

![cube](/readmeFiles/fase1/cube.png)
    
Finalment, també hem implementat els objectes tipus `Cylinder`, utilitzant els atributs: centre, radi i alçada. Les generatrius dels cilindres sempre seran verticals, és a dir, paral·leles al vector (0,1,0), de manera que aquests 3 atributs són suficients pels cilindres que tindrem al nostre projecte. Hem afegit 3 cilindres diferents a l'escena i hem obtingut la visualització següent.

![cylinders](/readmeFiles/fase1/cylinders.png)

TODO: Explicar con? @pedemonte96

### REALDATA

En aquesta fase hem implementat el mapeig de dades del món real a dades del món virtual. L'objectiu final és poder representar dades geolocalitzades en una visualització per representar dades. 

Per exemple, podríem representar la població de cada capital europea de la següent forma. Un conjunt esferes sobre un pla (que té de textura el mapa d'Europa), on el radi de cada esfera es proporcional a la població i cada esfera està situada al punt del mapa que representa la seva geolocalització real. De moment, a aquesta fase només hem implementat la part del mapeig.

Hem implementat el mapeig de dades reals a virtuals i els mètodes `aplicaTG` de cada tipus d'objecte utilitzant la classe `TG` que havíem fet a la pràctica 0, tal com se'ns recomanava al guió. Per exemple, per mapejar un punt geolocalitzat del món real al món virtual utilitzem una sèrie de transformacions geomètriques aplicades seqüencialment que resulten en una nova transformaicó geomètrica que és que necessitem, com podem veure a continuació.

    glm::mat4 restamR = glm::translate(glm::mat4(1.0f), -Rmin);
    glm::mat4 divisioRDiff = glm::scale(glm::mat4(1.0f), vDiv);
    glm::mat4 vDiff = glm::scale(glm::mat4(1.0f), Vmax - Vmin);
    glm::mat4 sumaVmin = glm::translate(glm::mat4(1.0f), Vmin);
    auto tg = make_shared<TG>(sumaVmin*vDiff*divisioRDiff*restamR);
    
També se'ns demanava implementar la classe `FittedPlane`, que ens serveix per situar a sobre objectes a les escenes, com si fos el terra. A continuació en mostrem un exemple.
    
![fittedplane](/readmeFiles/fase1/fittedplane.png)

Hem creat un fitxer de dades `data10.txt` de món real amb 10 files de dades amb valors arbitraris, tal com es demanava al guió. Podem visualitzar aquestes dades amb diferents objectes. A continuació mostrem les visualitzacions utilitzant esferes i cilindres.


Utilitzant `Sphere`         |  Utilitzant `Cylinder`
:-------------------------:|:-------------------------:
![data10spheres](/readmeFiles/fase1/data10spheres.png)  |  ![data10cylinders](/readmeFiles/fase1/data10cylinders.png)

Els fitxers `data10.txt`,`configVisData10.txt` i `configMappingData10.txt` utilitzats per obtenir les visualitzacions anteriors es troben a readmeFiles/fase1.

El que ens interessa d'aquesta fase és que el mapeig (tant de posició com de valor) es realitzi correctament, ja que quan introduïm la resta de funcionalitats a les fases 2 i 3 serà imprescindible aquesta part. Amb les visualitzacions anteriors podem veure que (en principi) això es realitza correctament, però ho tornarem a veure més endavant en les properes fases.

## Fase 2

## Fase 3

Code:

    example
