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
      metal(const colour& albedo, const double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {} //clamp fuzz to max 1
  
      bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
      const override {
          vec3 reflected = reflect(r_in.direction(), rec.normal); //reflected trajectory
          reflected = unit_vector(reflected) + (fuzz * random_unit_vector()); //add fuzz
          scattered = ray(rec.p, reflected);
          attenuation = albedo;
          //return true;
          return (dot(scattered.direction(), rec.normal) > 0);//if not reflected just absorb
      }
  
    private:
      colour albedo;
      double fuzz;
  };

  class dielectric : public material {
    public:
      dielectric(double refraction_index) : refraction_index(refraction_index) {}
  
      bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
      const override {
          attenuation = colour(1.0, 1.0, 1.0);//no attenuation at first
          double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;
  
          vec3 unit_direction = unit_vector(r_in.direction());
          double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
          double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
  
          bool cannot_refract = ri * sin_theta > 1.0;
          vec3 direction;
  
          if (cannot_refract || reflectance(cos_theta, ri) > random_double())
              direction = reflect(unit_direction, rec.normal);
          else
              direction = refract(unit_direction, rec.normal, ri);
  
          scattered = ray(rec.p, direction);
          return true;
      }
  
    private:
      // Refractive index in vacuum or air, or the ratio of the material's refractive index over
      // the refractive index of the enclosing media
      double refraction_index;

      static double reflectance(double cosine, double refraction_index) {//given as a function of the incidence angle and the refraction index
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
  };

#endif