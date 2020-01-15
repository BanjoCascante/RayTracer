#pragma once

#include <cstdlib>

inline float randomDouble() {
    return rand() / (RAND_MAX+1.0f);
}