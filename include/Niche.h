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

    double getSurface() const;
    double getBiologicalPotential() const;
    double getEcologicalHealth() const;
    double getNutrients() const;
    const CohortSet& getCohortSet() const;
    double getReturnRate() const;

    /** Maximum niche potential: surface * biological_potential * ecological_health. */
    double getMaxBiologicalPotential() const;

    /** Sum of death_biomass over all cohorts in this niche. */
    double getDeathBiomass() const;

    /** Adds return_rate * getDeathBiomass() to nutrients (nutrient recycling from dead biomass). */
    void update_nutrients();

private:
    double surface;
    double biological_potential;
    double ecological_health;
    double nutrients;
    CohortSet cohort_set;
    double return_rate;
};

