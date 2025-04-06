#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using colour = vec3;
inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}
// Function Declarations
void write_color(std::ostream& out, const colour& pixel_colour){
    int scaledr = int(pixel_colour.x()*255.999);
    int scaledg = int(pixel_colour.y()*255.999);
    int scaledb = int(pixel_colour.z()*255.999);

    int gammar = linear_to_gamma(scaledr);
    int gammag = linear_to_gamma(scaledg);
    int gammab = linear_to_gamma(scaledb);

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(gammar));
    int gbyte = int(256 * intensity.clamp(gammag));
    int bbyte = int(256 * intensity.clamp(gammab));//makes sure that the pixels written to file are within the specified range

    out<<scaledr<<' '<<scaledg<<' '<<scaledb<<std::endl;

}

#endif
