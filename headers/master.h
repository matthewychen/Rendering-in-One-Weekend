//primary header

#ifndef MASTER_H
#define MASTER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


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

// Common Headers

#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "progressbar.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"

#endif