#include "stdafx.h"
#include "Hitable.h"

bool Hitable::hit(const ray & r, float tMin, float tMax, HitRecord & rec) const
{
    return false;
}

Hitable::~Hitable()
{
}
