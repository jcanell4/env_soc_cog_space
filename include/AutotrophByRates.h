#pragma once

#include "Autotroph.h"
#include <nlohmann/json_fwd.hpp>
#include <tuple>
#include <vector>

/**
 * AutotrophByRates models an autotroph using explicit rate parameters:
 * maximum growth rate, base death rate, and positional tolerance values.
 */
class AutotrophByRates : public Autotroph {
public:
    using Tolerances = std::vector<float>;

    AutotrophByRates() = default;

    AutotrophByRates(std::string name,
                     float max_growth_rate,
                     float base_death_rate,
                     Tolerances tolerances);

    /** Construct from JSON keys: name, energy_content, max_growth_rate, base_death_rate, and tolerances (float array). */
    explicit AutotrophByRates(const nlohmann::json& j);

    float getMaxGrowthRate() const;
    float getBaseDeathRate() const;
    const Tolerances& getTolerances() const;
    double calculate_death_biomass(double total_biomass,
                                   double accepted_growth) const override;

    std::vector<std::tuple<int, double>> calculate_growth_biomass(
        const Niche& niche,
        double cohort_biomass) const override;

    void setMaxGrowthRate(float max_growth_rate);
    void setBaseDeathRate(float base_death_rate);
    void setTolerances(const Tolerances& tolerances);

private:
    float max_growth_rate_{0.0f};
    float base_death_rate_{0.0f};
    Tolerances tolerances_;
};
