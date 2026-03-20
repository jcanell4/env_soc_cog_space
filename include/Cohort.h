#pragma once

#include "LivingBeing.h"

#include <tuple>
#include <vector>

class Niche;

/**
 * Cohort represents a group of organisms of the same species.
 *
 * The species reference is fixed; biomass and death_biomass change only via the update methods below.
 */
class Cohort {
public:
    Cohort(const LivingBeing& specie, double biomass, double death_biomass = 0.0);

    // Returns the species name (read-only).
    const std::string& getSpecieName() const;

    // Returns total cohort energy (derived from species energy_content and biomass).
    double getEnergy() const;

    // Calculates the total cohort energy as: biomass * energy_content.
    double calculateEnergy() const;

    // Returns cohort biomass (read-only).
    double getBiomass() const;

    // Returns biomass of dead organisms in this cohort (read-only).
    double getDeathBiomass() const;

    /**
     * Updates cohort biomass accounting: applies growth then death flux via the species'
     * calculate_death_biomass(total_biomass, accepted_growth).
     */
    void update_biomass(double accepted_growth);

    /**
     * Applies a direct death mass transfer: subtracts `deaths` from living biomass
     * and adds the same amount to death_biomass.
     */
    void update_deaths(double deaths);

    /** Decreases death_biomass by `amount` (clamped so death_biomass does not go below 0). */
    void decrement_death_biomass(double amount);

    /**
     * Returns the same vector of (code, biomass_growth) terms as the species'
     * calculate_growth_biomass for this cohort's biomass.
     */
    std::vector<std::tuple<int, double>> calculate_growth_demand(const Niche& niche) const;

private:
    const LivingBeing& specie;
    double biomass;
    double death_biomass;
};

