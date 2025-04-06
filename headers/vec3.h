#ifndef VEC3_H
#define VEC3_H //declares definition of 3-dim vector class

#include <cmath>
#include <iostream>

class vec3 {
  public:
    double e[3]; //array of 3 doubles

    vec3() : e{0,0,0} {} //default constructor, 0 vector
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} //constructor with 3 doubles

    double x() const { return e[0]; } //helper function returns each of the 3 vector components, call with instance.x() etc.
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } //operator overloading that inverts the vector, use -instance
    double operator[](int i) const { return e[i]; } //returns ith component of vector, use instance[i], cannot be modified. activates on const. vec3 only
    double& operator[](int i) { return e[i]; } //returns ith component of vector by address, allowing modification. activates on non-const

    vec3& operator+=(const vec3& v) {//addition of vector
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(double t) {//scalar multiplication of vector
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {//scalar division. calls inverse of scalar multiplication
        return *this *= 1/t;
    }

    double length() const {//pythagorean length
        return std::sqrt(length_squared());
    }

    double length_squared() const {//non-rooted pythagorean length
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random() { //returns random clamped vector
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) { //returns random vector between a min and max
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions. Needed to catch issues
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {//prints vector to console
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {//return a new vec3 where the output is the sum of the two inputs, vectors added by pairs
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {//same thing with subtraction
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {//same thing with multiplication
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {//scalar multiplication implementation
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {//accounting for reverse order
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {//division
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {//dot product (sum of the corresponding parts)
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {//cross product (perpendicular vector)
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {//scales the vector down so that the pythagorean length is 1
    return v / v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {//perfect reflection based on the normal vector of the point of collision
    return v - 2*dot(v,n)*n;
}

#endif