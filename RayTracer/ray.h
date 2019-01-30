#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray
{
public:

    ray();
    ray(const vec3& origin, const vec3& direction);
    vec3 origin() const ;
    vec3 direction() const;
    vec3 pointAtParameter(float t);
    ~ray();
private:
    vec3 originVec;
    vec3 directionVec;
};

#endif // !RAY_H
