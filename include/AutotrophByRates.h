#pragma once

/**
 * @file AutotrophByRates.h
 * @brief Concrete autotroph parameterized by growth/death rates and JSON loading.
 */

#include "Autotroph.h"
#include <nlohmann/json_fwd.hpp>
#include <tuple>
#include <vector>

/**
 * @class AutotrophByRates
 * @brief Autotroph with explicit @em max_growth_rate, @em base_death_rate, and float tolerances.
 *
 * Growth demand terms use @ref NUTRIENTS_POS as the channel code for nutrient-limited growth.
 * Tolerances are mirrored to the @ref Autotroph base as doubles for environment sensitivity.
 */
class AutotrophByRates : public Autotroph {
public:
    using Tolerances = std::vector<float>;

    AutotrophByRates() = default;

    AutotrophByRates(std::string name,
                     float max_growth_rate,
                     float base_death_rate,
                     Tolerances tolerances);

    /**
     * @brief Parse from JSON: name, energy_content, max_growth_rate, base_death_rate, tolerances[].
     */
    explicit AutotrophByRates(const nlohmann::json& j);

    float getMaxGrowthRate() const;
    float getBaseDeathRate() const;

    /** @brief Tolerances as stored for this concrete type (float); base class holds double copy. */
    const Tolerances& getTolerances() const;

    /**
     * @brief Death biomass: base rate + resilience term from unmet potential growth.
     * @see AutotrophByRates.cpp for full formula.
     */
    double calculate_death_biomass(double total_biomass,
                                   double accepted_growth) const override;

    /**
     * @brief Single growth term: ( @ref NUTRIENTS_POS , potential growth after nutrient/space factors).
     */
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
