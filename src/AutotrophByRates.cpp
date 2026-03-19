#include "AutotrophByRates.h"
#include <nlohmann/json.hpp>
#include <utility>

AutotrophByRates::AutotrophByRates(std::string name,
                                   float max_growth_rate,
                                   float base_death_rate,
                                   Tolerances tolerances)
    : Autotroph(std::move(name)),
      max_growth_rate_(max_growth_rate),
      base_death_rate_(base_death_rate),
      tolerances_(std::move(tolerances)) {}

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

void AutotrophByRates::setMaxGrowthRate(float max_growth_rate) {
    max_growth_rate_ = max_growth_rate;
}

void AutotrophByRates::setBaseDeathRate(float base_death_rate) {
    base_death_rate_ = base_death_rate;
}

void AutotrophByRates::setTolerances(const Tolerances& tolerances) {
    tolerances_ = tolerances;
}
