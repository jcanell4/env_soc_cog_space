#include "Cohort.h"
#include "Niche.h"

#include <algorithm>

Cohort::Cohort(const LivingBeing& specie, double biomass, double death_biomass)
    : specie(specie), biomass(biomass), death_biomass(death_biomass) {}

const std::string& Cohort::getSpecieName() const {
    return specie.getName();
}

double Cohort::getEnergy() const {
    return calculateEnergy();
}

double Cohort::calculateEnergy() const {
    // Assumption: LivingBeing::energy_content is energy per unit biomass.
    return biomass * static_cast<double>(specie.getEnergyContent());
}

double Cohort::getBiomass() const {
    return biomass;
}

double Cohort::getDeathBiomass() const {
    return death_biomass;
}

void Cohort::update_biomass(double accepted_growth) {
    biomass += accepted_growth;
    const double inc = specie.calculate_death_biomass(biomass, accepted_growth);
    update_deaths(inc);
}

void Cohort::update_deaths(double deaths) {
    if (deaths > biomass) {
        deaths = biomass;
    }
    biomass -= deaths;
    death_biomass += deaths;
}

void Cohort::decrement_death_biomass(double amount) {
    death_biomass = std::max(0.0, death_biomass - amount);
}

std::vector<std::tuple<int, double>> Cohort::calculate_growth_demand(const Niche& niche) const {
    return specie.calculate_growth_biomass(niche, biomass);
}

