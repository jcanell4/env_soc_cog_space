#pragma once

#include "LivingBeing.h"

/**
 * Cohort represents a group of organisms of the same species.
 *
 * The species reference, biomass, and death_biomass are immutable from outside the class.
 */
class Cohort {
public:
    Cohort(const LivingBeing& spacie, double biomass, double death_biomass = 0.0);

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

private:
    // Spelling kept as requested by the user.
    const LivingBeing& spacie;
    double biomass;
    double death_biomass;
};

