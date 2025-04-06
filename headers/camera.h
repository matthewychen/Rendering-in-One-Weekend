//camera class
#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
  public: //default values
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1700;
    int samples_per_pixel = 10; //random samples per pixel on screen
    int max_depth = 10; //most bounces before abort

    void render(const hittable& world) {
        initialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            progressbar(image_height, j);
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);//start each pixel black
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);//accumulate ray colour of bounces
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        progressbar(image_height, image_height);
    }

  private:
    int    image_height;
    point3 center;         
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 pixel00_loc;    
    vec3   pixel_delta_u;  
    vec3   pixel_delta_v;
      

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);
        pixel_samples_scale = 1.0 / samples_per_pixel; //make each random sample contribute equally
        
        center = point3(0, 0, 0);

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center 
                                - vec3(0, 0, focal_length) 
                                - viewport_u/2 
                                - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) { 
            //vec3 direction = random_on_hemisphere(rec.normal); //scatter on random direction

            //lambertian: new direction is the normal plus some random unit vector
            vec3 direction = rec.normal + random_unit_vector();

            return 0.65 * ray_color(ray(rec.p, direction), depth-1, world); //if hit, recurse again in different direction but with less intensity. depth decreases as more bounces occur
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);//sky colour gradient
    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
};

#endif