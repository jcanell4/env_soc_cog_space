#include "Cohort.h"

Cohort::Cohort(const LivingBeing& spacie, double biomass, double death_biomass)
    : spacie(spacie), biomass(biomass), death_biomass(death_biomass) {}

const std::string& Cohort::getSpecieName() const {
    return spacie.getName();
}

double Cohort::getEnergy() const {
    return calculateEnergy();
}

double Cohort::calculateEnergy() const {
    // Assumption: LivingBeing::energy_content is energy per unit biomass.
    return biomass * static_cast<double>(spacie.getEnergyContent());
}

double Cohort::getBiomass() const {
    return biomass;
}

double Cohort::getDeathBiomass() const {
    return death_biomass;
}

