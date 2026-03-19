#include "LivingBeing.h"
#include <utility>

LivingBeing::~LivingBeing() = default;

LivingBeing::LivingBeing(std::string name, float energy_content)
    : name_(std::move(name)), energy_content_(energy_content) {}

const std::string& LivingBeing::getName() const {
    return name_;
}

float LivingBeing::getEnergyContent() const {
    return energy_content_;
}

