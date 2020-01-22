#include "stdafx.h"
#include "HitableVector.h"

HitableVector::HitableVector()
{
}


HitableVector::~HitableVector()
{
}

bool HitableVector::hit(const ray & r, float tMin, float tMax, HitRecord & rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    float closestSoFar = tMax;
    //for (std::shared_ptr<Hitable> object : itemVector) {
    int vectorLength = (int)itemVector.size();
    for (int i = 0; i < vectorLength; i++) {
        if (itemVector[i]->hit(r, tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}
