#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "colour.h"


class ray {
  public:
    ray() : //empty constructor
        orig{point3()}, 
        dir{vec3()}
    {}
    ray(const point3& origin, const vec3& direction) : //constructor with 2 vector inputs
        orig{origin},//passed by address and thus
        dir{direction}
    {}

    const point3& origin() const {
        return orig;
    }
    const vec3& direction() const {
        return dir;
    }

    point3 at(double t) const {
        //double xdist = orig.x() + dir.x()*t;
        //double ydist = orig.y() + dir.y()*t;
        //double zdist = orig.z() + dir.z()*t;
        //return vec3(xdist, ydist, zdist); manual calculation not needed
        return orig + dir * t;
    };

  private:
    point3 orig;
    vec3 dir;
};

#endif
