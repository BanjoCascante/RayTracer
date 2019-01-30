#ifndef VEC3_H
#define VEC3_H


#include <math.h>
class vec3
{
public:
    vec3();
    vec3(float x, float y, float z);
    inline float x() const { return v[0]; };
    inline float y() const { return v[1]; };
    inline float z() const { return v[2]; };
    inline float r() const { return v[0]; };
    inline float g() const { return v[1]; };
    inline float b() const { return v[2]; };
    inline const vec3& operator+() const {return *this; };
    inline const vec3& operator-() const { return vec3(-v[0], -v[1], -v[2]); }
    inline const float operator[] (int i) const{ return v[i]; };
    inline const float& operator[](int i){ return v[i]; };
    inline vec3& operator+= (const vec3& v2);
    inline vec3& operator-= (const vec3& v2);
    inline vec3& operator*= (const vec3& v2);
    inline vec3& operator/= (const vec3& v2);
    inline vec3& operator*= (const float& t);
    inline vec3& operator/= (const float& t);
    inline float squaredLength() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; };
    inline float length() const { return float(sqrt(squaredLength())); };
    inline void makeUnitVector();
    ~vec3();
private:
    float v[3]{};
};


inline float dot(const vec3& v1, const vec3 & v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3& v1, const vec3 & v2) {
    return vec3(v1.y()*v2.z() - v1.z()*v2.y(),
        v1.z()*v2.x() - v1.x()*v2.z(),
        v1.x()*v2.y() - v1.y()*v2.x()
    );
}

inline vec3 operator+ (const vec3& v1, const vec3& v2) {
    return vec3(
        v1.x() + v2.x(),
        v1.y() + v2.y(),
        v1.z() + v2.z()
    );
}

inline vec3 operator- (const vec3& v1, const vec3& v2) {
    return vec3(
        v1.x() - v2.x(),
        v1.y() - v2.y(),
        v1.z() - v2.z()
    );
}
inline vec3 operator* (const vec3& v1, const vec3& v2) {
    return vec3(
        v1.x() * v2.x(),
        v1.y() * v2.y(),
        v1.z() * v2.z()
    );
}

inline vec3 operator/ (const vec3& v1, const vec3& v2) {
    return vec3(
        v1.x() / v2.x(),
        v1.y() / v2.y(),
        v1.z() / v2.z()
    );
}

inline vec3 operator*(const vec3&  vec, float t) {
    return vec3{ vec.x()*t,vec.y()*t,vec.z()*t };
}

inline vec3 operator*(float t , const vec3& vec) {
    return vec3{ vec.x()*t,vec.y()*t,vec.z()*t };
}

inline vec3 operator/(const vec3&  vec, float t) {
    return vec3{ vec.x()/t,vec.y()/t,vec.z()/t };
}

inline vec3 operator/(float t, const vec3& vec) {
    return vec3{ vec.x()/t,vec.y()/t,vec.z()/t };
}


inline vec3 unitVector(vec3 vec) {
    return vec/vec.length();
}

#endif // !VEC3_H
