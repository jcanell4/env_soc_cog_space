#pragma once

/**
 * @file Cohort.h
 * @brief Population pool for one species reference: living and dead biomass.
 */

#include "LivingBeing.h"

#include <tuple>
#include <vector>

class Niche;

/**
 * @class Cohort
 * @brief One cohort: fixed @ref LivingBeing reference, mutable living and dead biomass.
 *
 * Dynamics go through @ref update_biomass, @ref update_deaths, and @ref decrement_death_biomass.
 * Growth demand is delegated to the species via @ref calculate_growth_demand.
 */
class Cohort {
public:
    /**
     * @param specie Species model (must outlive the cohort).
     * @param biomass Initial living biomass.
     * @param death_biomass Initial dead biomass pool for this cohort.
     */
    Cohort(const LivingBeing& specie, double biomass, double death_biomass = 0.0);

    /** @return Name of the referenced species. */
    const std::string& getSpecieName() const;

    /** @brief Shorthand for @ref calculateEnergy(). */
    double getEnergy() const;

    /** @return biomass * species energy_content. */
    double calculateEnergy() const;

    double getBiomass() const;
    double getDeathBiomass() const;

    /**
     * @brief Apply accepted growth then species death model for this step.
     * @param accepted_growth Mass added to living biomass before death flux is computed.
     */
    void update_biomass(double accepted_growth);

    /**
     * @brief Move mass from living to dead without using @ref calculate_death_biomass.
     * @param deaths Amount to subtract from living and add to dead (capped by current biomass).
     */
    void update_deaths(double deaths);

    /**
     * @brief Remove mass from the dead pool only (e.g. decomposition export).
     * @param amount Subtracted from @ref death_biomass, floored at zero.
     */
    void decrement_death_biomass(double amount);

    /**
     * @brief Species growth demand for this cohort's current biomass.
     * @return Same structure as @ref LivingBeing::calculate_growth_biomass.
     */
    std::vector<std::tuple<int, double>> calculate_growth_demand(const Niche& niche) const;

private:
    const LivingBeing& specie;
    double biomass;
    double death_biomass;
};
