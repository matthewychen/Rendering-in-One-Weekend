#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

// Function Declarations
void write_color(std::ostream& out, const color& pixel_colour){
    int scaledr = int(pixel_colour.x()*255.999);
    int scaledg = int(pixel_colour.y()*255.999);
    int scaledb = int(pixel_colour.z()*255.999);

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(scaledr));
    int gbyte = int(256 * intensity.clamp(scaledg));
    int bbyte = int(256 * intensity.clamp(scaledb));//makes sure that the pixels written to file are within the specified range

    out<<scaledr<<' '<<scaledg<<' '<<scaledb<<std::endl;

}

#endif
