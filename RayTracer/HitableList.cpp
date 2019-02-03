#include "stdafx.h"
#include "HitableList.h"

HitableList::HitableList()
{
}


HitableList::~HitableList()
{
}

bool HitableList::hit(const ray & r, float tMin, float tMax, HitRecord & rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    float closestSoFar = tMax;
    for (std::shared_ptr<Hitable> object : itemList) {
        if (object->hit(r, tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}
