#pragma once

#include <vector>
#include "Hitable.h"
#include <memory>
class HitableVector : public Hitable
{
public:
    HitableVector();
    HitableVector(std::vector<std::shared_ptr<Hitable>> &&itemListParam) { itemVector = std::move(itemListParam);};
    virtual ~HitableVector();
    // Inherited via Hitable
    virtual bool hit(const ray & r, float tMin, float tMax, HitRecord & rec) const override;

private:
    std::vector<std::shared_ptr<Hitable>> itemVector;


};

