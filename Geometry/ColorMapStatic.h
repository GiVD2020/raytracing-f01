
// This file is a modified part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2017 Joe Graus <jgraus@gmu.edu>, Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "ColorMap.h"

class ColorMapStatic: public ColorMap
{
public:

  enum COLOR_MAP_TYPES
  {
    COLOR_MAP_TYPE_INFERNO = 0,
    COLOR_MAP_TYPE_JET = 1,
    COLOR_MAP_TYPE_MAGMA = 2,
    COLOR_MAP_TYPE_PARULA = 3,
    COLOR_MAP_TYPE_PLASMA = 4,
    COLOR_MAP_TYPE_VIRIDIS = 5,
    NUM_COLOR_MAP_TYPES = 6
  } ;

    double lut[256][3];

    ColorMapStatic(): lut {{0.5, 0.2, 0.7},{ 1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {1.0, 1.0, 0.0}} {}

    ColorMapStatic(const COLOR_MAP_TYPES cm);

  virtual vec3 getColor(const double value);
  // Comput [r,g,b] values of the selected colormap for
  // a given factor f between 0 and 1
  //
  // Inputs:
  //   c  colormap enum
  //   f  factor determining color value as if 0 was min and 1 was max
  // Outputs:
  //   rgb  red, green, blue value
   virtual void getColor(const double f, double *rgb);

  // Outputs:
  //   r  red value
  //   g  green value
  //   b  blue value
  virtual void getColor(const double f, double & r, double & g, double & b);

  virtual ~ColorMapStatic();

private:
   void copia(double out[256][3] , double in[256][3] );

};



