#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(//ray is either scattered or absorbed
        const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered
    ) const {
        return false;
    }
};

class lambertian : public material {//lambertian material with guarenteed scattering and attenuation
    public:
      lambertian(const colour& albedo) : albedo(albedo) {}
  
      bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
      const override {
          auto scatter_direction = rec.normal + random_unit_vector();

          if(scatter_direction.near_zero()){
            scatter_direction = rec.normal;
          }
          scattered = ray(rec.p, scatter_direction);
          attenuation = albedo;
          return true;
      }
  

    private:
      colour albedo;
  };

  class metal : public material {
    public:
      metal(const colour& albedo) : albedo(albedo) {}
  
      bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
      const override {
          vec3 reflected = reflect(r_in.direction(), rec.normal);
          scattered = ray(rec.p, reflected);
          attenuation = albedo;
          return true;
      }
  
    private:
      colour albedo;
  };

#endif