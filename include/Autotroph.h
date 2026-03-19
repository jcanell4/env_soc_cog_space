#pragma once

#include "LivingBeing.h"

/**
 * Autotroph is a living entity that produces its own food.
 */
class Autotroph : public LivingBeing {
public:
    Autotroph() : LivingBeing(std::string{}, 17.5f) {}

    explicit Autotroph(std::string name, float energy_content = 17.5f);

    Autotroph(const Autotroph&) = default;
    Autotroph& operator=(const Autotroph&) = default;
    Autotroph(Autotroph&&) noexcept = default;
    Autotroph& operator=(Autotroph&&) noexcept = default;

    virtual ~Autotroph() = default;
};
