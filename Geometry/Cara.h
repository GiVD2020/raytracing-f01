#pragma once

#include <vector>
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

typedef vec4 Vertices;
// Face - representa una cara d'un objecte 3D
class Cara
{
 public:
    Cara();

    // constructor a partir de 3 o 4 indexs a vertex
    Cara(int i1, int i2, int i3, int i4=-1);

    // atributs
    vec4 color;
    vector<int> idxVertices;  // vector amb els indexs dels vertexs de la cara


    vec3 normal;
    void calculaNormal(vector<Vertices> &);
};


