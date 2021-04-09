# RayTracingGiVD 2020-21

## Equip:

**F01**: Albert Mir, Carla Morral, Martí Pedemonte, Arnau Quindós


## Features
- Fase 1
    - [X] Background amb degradat: Arnau

    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [X] 4.1.a. Mapping de mons virtuals: Albert
        - [X] 4.1.b. Hit Triangle
        - [X] 4.1.c. Hit Boundary Object: Arnau
        - [X] 4.1.d. Hit Cilindre: Martí
    - Creació de REAL DATA
        - [X] 4.2.a. Transformacions Translació i Escalat amb gizmos esferes: Arnau, Albert
        - [X] 4.2.b. Pla de terra: Martí
        - [X] 4.2.c. Gizmo de Triangle: Arnau
        - [X] 4.2.d. Gizmo de Cilindre
        - [ ] Noves dades ?
       

- Fase 2
    - [X] Antialiasing: Albert, Arnau
    - [X] Gamma Correction: Albert, Arnau
    - [X] Blin-Phong: Arnau
    - [X] Ombres amb objectes opacs: Martí
    - [X] Reflexions
    - [X] Transparències: Albert (fix by Martí)
    - [X] Visualització amb dades reals: Arnau
    
    
- Fase 3
    - [X] Texture mapping en el pla: Albert, Arnau
    - [X] MaterialTextura: Albert, Arnau
    - [ ] Nova escena de dades ?
   
- Parts opcionals
    - [X] Nous objectes paramètrics (Con): Martí
    - [ ] Penombres 
    - [ ] Diferents tipus de llums 
    - [ ] Multiple-scattering ?
    - [ ] Escena CSG 
    - [X] Ambient occlusion: Carla
    - [ ] Defocus blur
    - [ ] Més d'una propietat en les dades reals ?
    - [X] Animacions amb dades temporals: Albert (tot i que no és amb dades temporals, sino en virtualWorld)
    - [ ] Ombres atenuades segons objectes transparents
    - [X] Colors d'ombra segons els colors dels objectes transparents: Carla
    - [ ] Mapeig de les dades reals en una esfera
    - [ ] Ús de diferents paletes 
    
## Explicació de la pràctica    
_Comentaris de aspectes particulars de la vostra pràctica. Es pot seguir el guió de l'enunciat o fer una explicació més general amb alguns screenshots que avalin les vostres explicacions_

### Fase 0
    
La fase 0 és una fase premiliminar en la qual l'objectiu era familiaritzar-se amb el projecte i obtenir les primeres visualitzacions.

La primera que vam obtenir va ser el background de l'escena, un degradat des del blau RGB(0.5, 0.7, 1) fins el blanc RGB(1,1,1).

![background](/readmeFiles/fase0/fase0_background.png)

Les esferes ja estaven implementades al projecte i nosaltres vam implementar el mètode `hit` per detectar la col·lisió dels rajos del RayTracing amb les esferes de l'escena. Un cop implementat això i utilitzant la normal del raig sobre cada punt de l'objecte com a color, aquest és el resultat obtingut amb una sola esfera.

![sphere](/readmeFiles/fase0/fase0_sphere.png)

Afegint més esferes a l'escena i canviant certs paràmetres de la càmera com el `vfov` i el `lookFrom`, hem obtingut la següent imatge.

![spheres](/readmeFiles/fase0/fase0_spheres.png)

Els fitxers `configVis.txt` i `spheres.txt` utilitzats per obtenir la visualització anterior es troben al directori readmeFiles/fase0.

### Fase 1

L'objectiu de la fase 1 era construïr una escena virtual, utilitzant tant dades virtuals (esferes, triangles, cilindres...) com dades reals representades en una escena virtual. Tot i que les visualitzacions d'aquesta fase continuïn en un estat molt preliminar, tot el codi que hem fet a aquesta fase ens ha serveix per poder fer visualitzacions més interessants a la fase 2 i 3.

Les tasques d'aquesta fase es divideixen en dues parts molt diferenciades però complementàries:
- les que inclouen els nous tipus d'objectes i les seves interseccions a partir d'una escena
`VIRTUALWORLD`
- les que situen creen l'escena corresponent a les dades geolocalitzades a partir d'un fitxer de
dades `REALDATA`

#### VIRTUALWORLD

_Nota: En aquesta fase, tot i que els objectes tenen atribut `diffuse` que es pot utilitzar com a color de l'objecte, mostrarem les visualitzacions utilitzant com a color la normal del raig que intersecta cada punt de l'objecte, ja que ajuda a diferenciar millor les formes 3D._

El primer que se'ns demanava era la implementació dels objectes tipus `Triangle`, amb el seu hit corresponent. Els triangles consisteixen en 3 punts (`vec3`) que corresponen als tres vèrtexs del triangle. A continuació podem veure 3 triangles situats a una escena virtual.

![triangles](/readmeFiles/fase1/triangles.png)
    
Pel cas dels `boundaryObject`, que són malles poligonals, els hem implentat utilitzant directament l'objecte `Triangle`que acabem de crear, i al seu mètode hit no hem fet res més que utilitzar el hit del conjunt de triangles que formen la malla triangular. Un exemple és `cube.obj`, un objecte que se'ns proporcionava i que utilitza 12 triangles per formar les 6 cares del cub. Hem obtingut la visualització següent.

![cube](/readmeFiles/fase1/cube.png)
    
Finalment, també hem implementat els objectes tipus `Cylinder`, utilitzant els atributs: centre de la base, radi i alçada. Les generatrius dels cilindres sempre seran verticals, és a dir, paral·leles al vector (0,1,0), de manera que aquests 3 atributs són suficients pels cilindres que tindrem al nostre projecte. Hem afegit 3 cilindres diferents a l'escena i hem obtingut la visualització següent.

![cylinders](/readmeFiles/fase1/cylinders.png)

#### REALDATA

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

### Fase 2

L'objectiu de la fase 2 de la pràctica era crear els materials de forma completa i desenvolupar el càlcul de la il·luminació de l'escena segons el model de Blinn-Phong. 

Durant tota la part de món virtual de la fase 2 utilitzarem la mateixa escena amb mínims canvis (afegint certs objectes) per tal de veure els canvis que suposa cada nova implementació al nostre codi i poder evaluar cada part per separat.

Com les visualitzacions a partir d'aquest punt són més el·laborades, per  millorar la qualitat de les imatges resultants, hem implementat *supersampling*, i.e. tirar diversos rajos per píxel amb una certa petita variació aleatòria per reduir l'aliasing. A continuació podem veure la millora que suposa aquest petit canvi. 

`numSamples=1`        |  `numSamples=10`  
:-------------------------:|:-------------------------:
![ssaa1](/readmeFiles/fase2/ssaa1.png)  |  ![ssaa10](/readmeFiles/fase2/ssaa10.png)
![ssaa1zoom](/readmeFiles/fase2/ssaa1zoom.png)  |  ![ssaa10](/readmeFiles/fase2/ssaa10zoom.png)


El primer pas per desenvolupar escenes amb il·luminació és la creació d'un objecte `Light`, que de moment serà de tipus puntual, és a dir, un punt des d'on surten rajos de llum en totes direccions. Aquest objecte tindrà un atribut posició, tres components: ambient, difusa i especular i un polinomi d'atenuació del qual guardarem els 3 coeficients a, b, c. Aquest polinomi representa com s'atenua la llum a mesura que augmenta la distància entre el punt de llum i l'objecte que il·lumina. També tindrem llum ambient global, que representa els rajos de llum que reboten múltiples cops i acaben il·luminant tots els punts de l'escena de forma uniforme.

Per a les properes visualitzacions, utilitzarem una llum puntual a la posició (2, 8, 10) amb Ia= (0.3, 0.3, 0.3), una Id = (0.7, 0.7, 0.7), una Is = (1.0, 1.0, 1.0) i un coeficient d'atenuació de 0.5 + 0.01d^2. També tindrem una llum ambient global (0.1, 0.1, 0.1).

Hem implementat Blinn-Phong a la classe `Scene` com s'indicava a les transparències i a continuació mostrarem els resultats obtinguts pas a pas. L'esfera que utilitzarem és de material `Lambertian` amb Ka =(0.2,0.2, 0.2), Kd=(0.5, 0.5, 0.5), K_s = (1.0, 1.0, 1.0) i una shineness de 10.0.

Calcul·lant només la component ambient:

![bp1](/readmeFiles/fase2/bp_ca.png)

Només la component difusa:

![bp2](/readmeFiles/fase2/bp_cd.png)

Només la component especular:

![bp3](/readmeFiles/fase2/bp_cs.png)

Amb la suma de les tres components anteriors:

![bp4](/readmeFiles/fase2/bp_sum.png)

Afegint l'atenuació de la llum:

![bp5](/readmeFiles/fase2/bp_att.png)

Finalment, afegim la llum ambient global:

![bp6](/readmeFiles/fase2/bp_gl.png)

Afegint el raig d'ombra de Blinn-Phong:

![bp7](/readmeFiles/fase2/bp_shadow.png)

Arribats a aquest punt, podem aprofitar la varietat d'objectes que tenim implementada per aplicar Blinn-Phong a una escena més complexa, com la següent.

![bpcomplex](/readmeFiles/fase2/2a_complex.png)

_Afegim a readmeFiles/fase2 el fitxer `Scene_Fase2A_Complex.txt` que conté les 10 figures que formen l'escena._

TODO:
    - Cal explicar més Blinn-Phong / ombres?
    - Transparencies
    - Metal
    - Visualization mapping

### Fase 3

 TODO:
    - Textures
    
### Opcionals

#### Implementació de nous objectes paramètrics: Con

A part de tots els objectes que se'ns demanaven, també hem implementat els objectes tipus `Cone`, utilitzant els atributs: centre de la base, radi de la base i alçada. Els cons sempre estaran orientats verticalment, és a dir, amb l'alçada paral·lela al vector (0,1,0), de manera que aquests 3 atributs són suficients. Hem afegit uns quants cilindres diferents a l'escena, amb el color corresponent a la normal de cada cara, i hem obtingut la visualització següent.

![cones](/readmeFiles/fase3/cones.png)
  
  TODO:
    - Ambient occlusion
    - Ombres de colors
    - Animacions de dades temporals
    
### Screenshots més rellevants

_Recordeu que n'heu de triar-ne un per pujar-lo a la web: https://padlet.com/twopuig/d63depo6ql4tzqot_

       
### Informació addicional o observacions

