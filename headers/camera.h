//camera class
#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"
#include "colour.h"

class camera {
  public: //default values
  //RENDERING SETTINGS
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1700;
    int samples_per_pixel = 10; //random samples per pixel on screen
    int max_depth = 10; //most bounces before abort

  //CAMERA PROPERTIES
    double vfov = 90;  // Vertical view angle (field of view)
    point3 lookfrom = point3(0,0,0);   // Point camera is looking from
    point3 lookat   = point3(0,0,-1);  // Point camera is looking at
    vec3   vup      = vec3(0,1,0);     // Camera-relative "up" direction. WORLD up

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    void render(const hittable& world) {//rendering block
        initialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            progressbar(image_height, j);
            for (int i = 0; i < image_width; i++) {
                colour pixel_color(0,0,0);//start each pixel black
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
    vec3   u, v, w;              // Camera frame basis vectors
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius

      

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        //auto focal_length = (lookfrom - lookat).length(); //length from camera centre to target pos
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        pixel_samples_scale = 1.0 / samples_per_pixel; //make each random sample contribute equally by adding all components into the colour result, and then dividing at the end
        
        center = lookfrom;

        w = unit_vector(lookfrom - lookat); 
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    colour ray_color(const ray& r, int depth, const hittable& world) const {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return colour(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) { 
            //vec3 direction = random_on_hemisphere(rec.normal); //scatter on random direction

            //lambertian: new direction is the normal plus some random unit vector
            //vec3 direction = rec.normal + random_unit_vector();
            //return 0.65 * ray_color(ray(rec.p, direction), depth-1, world); //if hit, recurse again in different direction but with less intensity. depth decreases as more bounces occur

            ray scatteredray;
            colour attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scatteredray))
                return attenuation * ray_color(scatteredray, depth-1, world);
            return colour(0,0,0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*colour(1.0, 1.0, 1.0) + a*colour(0.5, 0.7, 1.0);//sky colour gradient
    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }
    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
};

#endif