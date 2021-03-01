#pragma once

#include "glm/glm.hpp"

using namespace glm;

class ColorMap
{

 public:

  virtual vec3 getColor(const double value) = 0;
  // Comput [r,g,b] values of the selected colormap for
  // a given factor f between 0 and 1
  //
  // Inputs:
  //   f  factor determining color value as if 0 was min and 1 was max
  // Outputs:
  //   rgb  red, green, blue value

  virtual void getColor(const double f, double *rgb) = 0;

  // Inputs:
  //   f  factor determining color value as if 0 was min and 1 was max
  // Outputs:
  //   r  red value
  //   g  green value
  //   b  blue value
  virtual void getColor(const double f, double & r, double & g, double & b) = 0;

};

