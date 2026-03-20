#include "AutotrophByRates.h"
#include "Constants.h"
#include "Niche.h"

#include <nlohmann/json.hpp>
#include <algorithm>
#include <vector>
#include <utility>

static std::vector<double> to_double_vector(const AutotrophByRates::Tolerances& v) {
    std::vector<double> out;
    out.reserve(v.size());
    for (float x : v) {
        out.push_back(static_cast<double>(x));
    }
    return out;
}

AutotrophByRates::AutotrophByRates(std::string name,
                                   float max_growth_rate,
                                   float base_death_rate,
                                   Tolerances tolerances)
    : Autotroph(std::move(name)),
      max_growth_rate_(max_growth_rate),
      base_death_rate_(base_death_rate),
      tolerances_(std::move(tolerances)) {
    // Keep base-class tolerance vector in sync for environment sensitivity computation.
    Autotroph::setTolerances(to_double_vector(tolerances_));
}

AutotrophByRates::AutotrophByRates(const nlohmann::json& j)
    : Autotroph(j.value("name", std::string{}), j.value("energy_content", 17.5f)),
      max_growth_rate_(j.value("max_growth_rate", 0.0f)),
      base_death_rate_(j.value("base_death_rate", 0.0f)) {
    tolerances_.clear();
    if (j.contains("tolerances") && j["tolerances"].is_array()) {
        for (const auto& value : j["tolerances"]) {
            if (value.is_number()) {
                tolerances_.push_back(value.get<float>());
            }
        }
    }

    // Keep base-class tolerance vector in sync for environment sensitivity computation.
    Autotroph::setTolerances(to_double_vector(tolerances_));
}

float AutotrophByRates::getMaxGrowthRate() const {
    return max_growth_rate_;
}

float AutotrophByRates::getBaseDeathRate() const {
    return base_death_rate_;
}

const AutotrophByRates::Tolerances& AutotrophByRates::getTolerances() const {
    return tolerances_;
}

double AutotrophByRates::calculate_death_biomass(double total_biomass,
                                                 double accepted_growth) const {
    const double max_growth_abs = static_cast<double>(max_growth_rate_) * total_biomass;

    double resilience_component = 0.0;
    if (max_growth_abs != 0.0) {
        resilience_component =
            getResilience() * ((max_growth_abs - accepted_growth) / max_growth_abs) * total_biomass;
    }

    return total_biomass * static_cast<double>(base_death_rate_) + resilience_component;
}

std::vector<std::tuple<int, double>> AutotrophByRates::calculate_growth_biomass(
    const Niche& niche,
    double cohort_biomass) const {
    const double surface = niche.getSurface();
    if (surface <= 0.0) {
        return {{NUTRIENTS_POS, 0.0}};
    }

    // [1] Nutrients per unit surface.
    const double nutrients_per_surface = niche.getNutrients() / surface;

    // [2] Growth limitation from nutrient availability vs environment sensitivity.
    const double sensitivity = getEnvironmentSensitivity(niche);
    const double denom = nutrients_per_surface + sensitivity;
    const double nutrient_factor = (denom > 0.0) ? (nutrients_per_surface / denom) : 0.0;

    // [3] Space limitation: 1 - (living_biomass / max_supported_biomass).
    const double max_potential = niche.getMaxBiologicalPotential();
    double space_factor = 0.0;
    if (max_potential > 0.0) {
        space_factor = 1.0 - (niche.getLivingBiomass() / max_potential);
        space_factor = std::clamp(space_factor, 0.0, 1.0);
    }

    // [4] Maximum growth for this cohort biomass.
    const double max_growth = static_cast<double>(max_growth_rate_) * cohort_biomass;

    return {{NUTRIENTS_POS, max_growth * space_factor * nutrient_factor}};
}

void AutotrophByRates::setMaxGrowthRate(float max_growth_rate) {
    max_growth_rate_ = max_growth_rate;
}

void AutotrophByRates::setBaseDeathRate(float base_death_rate) {
    base_death_rate_ = base_death_rate;
}

void AutotrophByRates::setTolerances(const Tolerances& tolerances) {
    tolerances_ = tolerances;
    // Keep base-class tolerance vector in sync for environment sensitivity computation.
    Autotroph::setTolerances(to_double_vector(tolerances_));
}
