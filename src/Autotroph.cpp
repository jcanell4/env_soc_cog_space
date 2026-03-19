#include "Autotroph.h"
#include <utility>

Autotroph::Autotroph(std::string name, float energy_content)
    : LivingBeing(std::move(name), energy_content) {}
