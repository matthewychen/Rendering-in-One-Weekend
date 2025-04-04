#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

// Function Declarations
void write_color(std::ostream& out, const color& pixel_colour){
    int scaledx = int(pixel_colour.x()*255.999);
    int scaledy = int(pixel_colour.y()*255.999);
    int scaledz = int(pixel_colour.z()*255.999);
    out<<scaledx<<' '<<scaledy<<' '<<scaledz<<std::endl;
}

#endif
