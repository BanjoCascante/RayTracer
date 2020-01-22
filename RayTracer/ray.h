#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray
{
public:

    ray();
    ray(const vec3& origin, const vec3& direction);
    vec3 pointAtParameter(float t) const;
    ~ray();
    vec3 origin;
    vec3 direction;
private:
};

#endif // !RAY_H
