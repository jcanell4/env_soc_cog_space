#include "Niche.h"
#include <algorithm>
#include <utility>

Niche::Niche(double surface,
             double biological_potential,
             double ecological_health,
             double nutrients,
             CohortSet cohort_set,
             double return_rate)
    : surface(surface),
      biological_potential(biological_potential),
      ecological_health(std::clamp(ecological_health, 0.0, 1.0)),
      nutrients(nutrients),
      cohort_set(std::move(cohort_set)),
      return_rate(return_rate) {}

double Niche::getSurface() const {
    return surface;
}

double Niche::getBiologicalPotential() const {
    return biological_potential;
}

double Niche::getEcologicalHealth() const {
    return ecological_health;
}

double Niche::getNutrients() const {
    return nutrients;
}

const Niche::CohortSet& Niche::getCohortSet() const {
    return cohort_set;
}

double Niche::getReturnRate() const {
    return return_rate;
}

double Niche::getMaxBiologicalPotential() const {
    return surface * biological_potential * ecological_health;
}

double Niche::getDeathBiomass() const {
    double total = 0.0;
    for (const auto& cohort : cohort_set) {
        total += cohort.getDeathBiomass();
    }
    return total;
}

void Niche::update_nutrients() {
    nutrients += return_rate * getDeathBiomass();
}

