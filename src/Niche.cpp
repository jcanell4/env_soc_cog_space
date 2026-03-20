#include "Niche.h"
#include "Constants.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <map>
#include <random>
#include <string>
#include <tuple>
#include <utility>

static std::vector<double> clamp_conditions(std::vector<double> v) {
    for (auto& x : v) {
        x = std::clamp(x, 0.0, 1.0);
    }
    return v;
}

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

Niche::Niche(double surface,
             double biological_potential,
             double ecological_health,
             double nutrients,
             CohortSet cohort_set,
             double return_rate,
             std::vector<double> conditions)
    : surface(surface),
      biological_potential(biological_potential),
      ecological_health(std::clamp(ecological_health, 0.0, 1.0)),
      nutrients(nutrients),
      cohort_set(std::move(cohort_set)),
      return_rate(return_rate),
      conditions(clamp_conditions(std::move(conditions))) {}

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

const std::vector<double>& Niche::getConditions() const {
    return conditions;
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

double Niche::getLivingBiomass() const {
    double total = 0.0;
    for (const auto& cohort : cohort_set) {
        total += cohort.getBiomass();
    }
    return total;
}

void Niche::update_nutrients() {
    initial_nutrients = nutrients;
    for (auto& cohort : cohort_set) {
        const double death = cohort.getDeathBiomass();
        const double recycled = return_rate * death;
        nutrients += recycled;
        cohort.decrement_death_biomass(recycled);
    }
    update_ecological_health(nutrients - initial_nutrients);
}

void Niche::update_ecological_health(double recycling_increment) {
    const double h = shannon_species_diversity();
    diversity_factor = h / 2.0;
    recycling_factor = recycling_increment * 0.1;
    ecological_health = ecological_health * 0.9  + 0.05 * diversity_factor + recycling_factor * 0.05;
}

void Niche::step() {
    update_nutrients();
    update_cohorts();
}

void Niche::update_cohorts() {
    CohortSet& cohorts = cohort_set;
    const std::size_t n = cohorts.size();
    if (n == 0) {
        return;
    }

    // Random rotation: first cohort in vector does not always get priority.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(0, n - 1);
    const std::size_t start = dist(gen);

    for (std::size_t i = 0; i < n; ++i) {
        const std::size_t idx = (start + i) % n;
        const auto demand_terms = cohorts[idx].calculate_growth_demand(*this);
        for (const auto& demand : demand_terms) {
            const int code = std::get<0>(demand);
            const double amount = std::get<1>(demand);
            if (code == NUTRIENTS_POS) {
                // Autotroph-style growth limited by niche nutrients (per demand term).
                if (amount > nutrients) {
                    cohorts[idx].update_biomass(nutrients);
                    nutrients = 0.0;
                } else {
                    cohorts[idx].update_biomass(amount);
                    nutrients -= amount;
                }
                break;
            } else if (code < 0) {
                // Decomposers: feed from another cohort's death_biomass; index encoded as -(code + 1).
                const std::size_t donor_idx = static_cast<std::size_t>(-(code + 1));
                if (donor_idx >= cohorts.size()) {
                    break;
                }
                if (amount > cohorts[donor_idx].getDeathBiomass()) {
                    cohorts[idx].update_biomass(cohorts[donor_idx].getDeathBiomass());
                    cohorts[donor_idx].decrement_death_biomass(cohorts[donor_idx].getDeathBiomass());
                } else {
                    cohorts[idx].update_biomass(amount);
                    cohorts[donor_idx].decrement_death_biomass(amount);
                }
                break;
            } else {
                // Heterotroph-style growth limited by prey cohort living biomass (code = prey index).
                const std::size_t prey_idx = static_cast<std::size_t>(code);
                if (prey_idx >= cohorts.size()) {
                    break;
                }
                if (amount > cohorts[prey_idx].getBiomass()) {
                    cohorts[idx].update_biomass(cohorts[prey_idx].getBiomass());
                    cohorts[prey_idx].update_deaths(cohorts[prey_idx].getBiomass());
                } else {
                    cohorts[idx].update_biomass(amount);
                    cohorts[prey_idx].update_deaths(amount);
                }
                break;
            }
        }
    }
}

double Niche::shannon_species_diversity() const {
    std::map<std::string, double> living_biomass_by_species;
    for (const auto& cohort : cohort_set) {
        living_biomass_by_species[cohort.getSpecieName()] += cohort.getBiomass();
    }

    double total_living = 0.0;
    for (const auto& entry : living_biomass_by_species) {
        total_living += entry.second;
    }
    if (total_living <= 0.0) {
        return 0.0;
    }

    double h = 0.0;
    for (const auto& entry : living_biomass_by_species) {
        const double bio = entry.second;
        if (bio > 0.0) {
            const double p = bio / total_living;
            h -= p * std::log(p);
        }
    }
    return h;
}

