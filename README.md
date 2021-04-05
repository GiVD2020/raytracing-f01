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

Els fitxers `configVis.txt` i `spheres.txt` utilitzats per obtenir la visualització anterior es troben al directori readmeFiles.

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

    (Imatge triangle)
    
Pel cas dels `boundaryObject`, que són malles poligonals, els hem implentat utilitzant directament l'objecte `Triangle`que acabem de crear, i al seu mètode hit no hem fet res més que utilitzar el hit del conjunt de triangles que formen la malla triangular. Un exemple és `cube.obj`, un objecte que se'ns proporcionava i que utilitza 12 triangles per formar les 6 cares del cub. Hem obtingut la visualització següent.

    (Imatge triangle)
    
Finalment, també hem implementat els objectes tipus `Cylinder`, utilitzant els atributs: centre, radi i alçada. Les generatrius dels cilindres sempre seran verticals, és a dir, paral·leles al vector (0,1,0), de manera que aquests 3 atributs són suficients pels cilindres que tindrem al nostre projecte.

    (Imatge cilindre)

TODO: Explicar con? @pedemonte96

### REALDATA (TODO)

## Fase 2

## Fase 3

Code:

    example
