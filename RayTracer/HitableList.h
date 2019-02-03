#pragma once

#include <list>
#include "Hitable.h"
#include <memory>
class HitableList : public Hitable
{
public:
    HitableList();
    HitableList(std::list<std::shared_ptr<Hitable>> &&itemListParam) { itemList = std::move(itemListParam);};
    virtual ~HitableList();
    // Inherited via Hitable
    virtual bool hit(const ray & r, float tMin, float tMax, HitRecord & rec) const override;

private:
    std::list<std::shared_ptr<Hitable>> itemList;


};

