#pragma once

#include <string>

/**
 * LivingBeing is the base type for all living entities in the ecosystem model.
 * It stores identity and energy as protected members (writable by derived types),
 * while exposing public getters for read-only access.
 */
class LivingBeing {
public:
    virtual ~LivingBeing() = 0;

    const std::string& getName() const;
    float getEnergyContent() const;

protected:
    LivingBeing() = default;
    explicit LivingBeing(std::string name, float energy_content);

    std::string name_;
    float energy_content_{0.0f};
};

