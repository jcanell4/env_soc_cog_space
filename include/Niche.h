#pragma once

#include "Cohort.h"
#include <vector>

/**
 * Niche models an ecological niche and its capacity to host living beings.
 *
 * nutrients: quantity of inorganic nutrients available in this niche.
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

    /** Maximum niche potential: surface * biological_potential * ecological_health. */
    double getMaxBiologicalPotential() const;

    /** Sum of death_biomass over all cohorts in this niche. */
    double getDeathBiomass() const;

    /** Sum of living biomass over all cohorts in this niche. */
    double getLivingBiomass() const;

    /**
     * Per cohort: adds return_rate * cohort.death_biomass to niche nutrients and removes
     * that same mass from the cohort's death_biomass (recycling).
     */
    void update_nutrients();

    /**
     * Updates ecological_health from living species diversity using Pielou's evenness
     * J = H' / ln(S) (clamped to [0, 1]), with H' from shannon_species_diversity and S
     * the number of species with positive living biomass. If S < 2, sets health to 0.
     */
    void update_ecological_health(double recycling_increment);

    /** Advances this niche by one simulation timestep. */
    void step();

private:
    double surface;
    double biological_potential;
    double ecological_health;
    double nutrients;
    CohortSet cohort_set;
    double return_rate;
    /**
     * Niche environmental conditions encoded as normalized values in [0, 1].
     * Examples: humidity, sun radiance, temperature, etc.
     */
    std::vector<double> conditions;

    /** Random-order pass over cohorts: growth demand vs nutrients, death updates. */
    void update_cohorts();

    /**
     * Shannon diversity index H' = -sum_i p_i ln(p_i) over species,
     * where p_i is the proportion of living biomass of species i in this niche.
     * Cohorts with the same specie name are pooled. Returns 0 if there is no living biomass.
     */
    double shannon_species_diversity() const;
};
