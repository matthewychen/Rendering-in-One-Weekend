//primary header

#ifndef MASTER_H
#define MASTER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>


// C++ Std Usings

using std::make_shared; //memory control
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity(); //useful approximations
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double random_double() { //rng
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0); //rand_max is preset, so this clamps it to 0 to 1
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

// Common Headers

#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "progressbar.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"
#include "camera.h"

#endif