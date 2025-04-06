#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "master.h"
#include "interval.h"

class material;

class hit_record {
    public:
      point3 p; //point of hit
      vec3 normal; //normal at point p
      double t; //position on ray where it hit
      bool front_face; //whether it hit from the outside or the inside
      shared_ptr<material> mat; //pointer to the appropriate material type
  
      void set_face_normal(const ray& r, const vec3& outward_normal) {
          // Sets the hit record normal vector.
          // NOTE: the parameter `outward_normal` is assumed to have unit length.
  
          front_face = dot(r.direction(), outward_normal) < 0; //if direction is the same as the outward normal, it is on the inside
          normal = front_face ? outward_normal : -outward_normal; //if the ray is coming from the inside, the normal should be pointing against the normal and back into the hittable object
      }
  };

class hittable {//base class for objects that can be hittablew
  public:
    virtual ~hittable() = default; //generates destructor. allows overwriting in derived classes

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0; //returns true if the object is hit, false if not
    //ray_tmin makes sure no duplicate hits are counted, usually set to some small number
    //ray_tmax maximum allowable t, allows hits behind other objects to be 
    //now both contained in ray_t
    //=0 means its a pure virtual function and forces derived classes to implement it
};

#endif