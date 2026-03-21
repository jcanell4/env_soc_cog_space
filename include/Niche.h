#pragma once

/**
 * @file Niche.h
 * @brief Spatial/ecological unit: cohorts, nutrients, conditions, and timestep integration.
 */

#include "Cohort.h"
#include <vector>

/**
 * @class Niche
 * @brief Hosts a vector of @ref Cohort "cohorts", global nutrients, optional conditions, and rates.
 *
 * @par Timestep (@ref step)
 * 1. @ref update_nutrients — recycle dead biomass to nutrients per cohort.<br>
 * 2. @ref update_cohorts — resolve growth demands in random rotation order.<br>
 *
 * @par Growth demand codes (int in each tuple)
 * - @ref NUTRIENTS_POS — autotroph-style: competes for @ref nutrients.<br>
 * - Negative codes — decomposer: donor cohort index = @c -(code + 1).<br>
 * - Non-negative (not @ref NUTRIENTS_POS) — heterotroph: prey cohort index = @p code.
 */
class Niche {
public:
    using CohortSet = std::vector<Cohort>;

    Niche(double surface,
          double biological_potential,
          double ecological_health,
          double nutrients,
          CohortSet cohort_set,
          double return_rate);

    Niche(double surface,
          double biological_potential,
          double ecological_health,
          double nutrients,
          CohortSet cohort_set,
          double return_rate,
          std::vector<double> conditions);

    double getSurface() const;
    double getBiologicalPotential() const;
    double getEcologicalHealth() const;
    double getNutrients() const;
    const CohortSet& getCohortSet() const;
    double getReturnRate() const;
    const std::vector<double>& getConditions() const;

    /** @return surface * biological_potential * ecological_health (carrying capacity proxy). */
    double getMaxBiologicalPotential() const;

    /** @brief Sum of @ref Cohort::getDeathBiomass over all cohorts. */
    double getDeathBiomass() const;

    /** @brief Sum of @ref Cohort::getBiomass over all cohorts. */
    double getLivingBiomass() const;

    /**
     * @brief Recycle dead biomass to nutrients per cohort, then refresh ecological health.
     *
     * For each cohort: adds @c return_rate * death_biomass to @ref nutrients and calls
     * @ref Cohort::decrement_death_biomass with the same amount. Then calls
     * @ref update_ecological_health with the niche-level nutrient increment for the step.
     */
    void update_nutrients();

    /**
     * @brief Low-pass update of @ref ecological_health from Shannon diversity and recycling.
     * @param recycling_increment Change in niche nutrients from the recycling pass (typically
     *        positive after @ref update_nutrients).
     *
     * Combines @ref shannon_species_diversity (scaled) and recycling into a smoothed health value.
     */
    void update_ecological_health(double recycling_increment);

    /** @brief One simulation step: nutrients, then cohort growth resolution. */
    void step();

private:
    double surface;
    double biological_potential;
    double ecological_health;
    double nutrients;
    CohortSet cohort_set;
    double return_rate;
    /** Normalized environmental traits in [0,1] (humidity, light, temperature, ...). */
    std::vector<double> conditions;

    /**
     * @brief Visit cohorts in random rotation; apply @ref Cohort::calculate_growth_demand
     *        and update nutrients / prey / donor pools per demand code.
     */
    void update_cohorts();

    /**
     * @brief Shannon index H' on living biomass shares by @ref Cohort::getSpecieName.
     * @return 0 if there is no positive living biomass.
     */
    double shannon_species_diversity() const;
};
