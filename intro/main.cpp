#include <iostream>
#include <fstream>

int main() {

    // Image

    int image_width = 1024;
    int image_height = 1024;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //std::ofstream logfile("log.txt");
    //std::clog.rdbuf(logfile.rdbuf()); 
    
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\nDone.\n";
    //logfile.close();
}