#pragma once

#include <string>
#include <tuple>
#include <vector>

class Niche;

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
    virtual double calculate_death_biomass(double total_biomass,
                                           double accepted_growth) const = 0;

    /**
     * Computes potential growth biomass terms for this species in the given niche.
     * Each entry is (code, biomass_growth); concrete types define meaning of the int codes.
     */
    virtual std::vector<std::tuple<int, double>> calculate_growth_biomass(
        const Niche& niche,
        double cohort_biomass) const = 0;

protected:
    LivingBeing() = default;
    explicit LivingBeing(std::string name, float energy_content);

    std::string name_;
    float energy_content_{0.0f};
};

