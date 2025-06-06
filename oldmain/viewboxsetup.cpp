#include "headers/colour.h"
#include "headers/ray.h"
#include "headers/vec3.h"

#include <iostream>

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction()); //creates new vector.
    auto a = 0.5*(unit_direction.y() + 1.0); //generates a scaling factor based on the geometry. a is between 0 and 1.
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0, 0.7, 1.0); //return colour based on scalin
    return color(0,0,0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0; //distance from eye point
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0); //width vector
    auto viewport_v = vec3(0, -viewport_height, 0); //height vector. points negative, because the coordinate system is defined as increasing when going up. So because this is pointing from top to bottom this will be negative.

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2; //move 1/2 of the width and height away from the middle of the viewport
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); //situated 1/2u and v away from 0,0.

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center; //ray starts at camera centre and points towards point on viewpoint
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r); //black pixel
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}