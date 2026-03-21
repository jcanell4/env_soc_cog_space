#pragma once

/**
 * @file Autotroph.h
 * @brief Abstract autotroph: tolerances, resilience, and environment coupling.
 */

#include "LivingBeing.h"

#include <tuple>
#include <vector>

class Niche;

/**
 * @class Autotroph
 * @brief Producer organism: extends @ref LivingBeing with tolerance vector and resilience.
 *
 * Remains abstract: @ref calculate_death_biomass and @ref calculate_growth_biomass must be
 * implemented by concrete models (e.g. @ref AutotrophByRates).
 */
class Autotroph : public LivingBeing {
public:
    Autotroph() : LivingBeing(std::string{}, 17.5f), resilience_(0.5) {}

    explicit Autotroph(std::string name,
                       float energy_content = 17.5f,
                       double resilience = 0.5);

    explicit Autotroph(std::string name,
                       std::vector<double> tolerances,
                       float energy_content = 17.5f,
                       double resilience = 0.5);

    Autotroph(const Autotroph&) = default;
    Autotroph& operator=(const Autotroph&) = default;
    Autotroph(Autotroph&&) noexcept = default;
    Autotroph& operator=(Autotroph&&) noexcept = default;

    virtual ~Autotroph() = default;

    /** @brief Ideal environmental conditions per trait (each in [0,1]). */
    const std::vector<double>& getTolerances() const;
    /** @brief Replace tolerances; values are clamped to [0,1]. */
    void setTolerances(std::vector<double> tolerances);

    /** @return Resilience in [0,1] (mortality response to unmet growth potential). */
    double getResilience() const;
    void setResilience(double resilience);

    /**
     * @brief Scalar mismatch between niche conditions and tolerances, scaled by niche potential.
     *
     * Uses normalized Euclidean distance between @p niche conditions and @ref tolerances_,
     * divided by sqrt(dim), then multiplied by @ref Niche::getBiologicalPotential().
     */
    double getEnvironmentSensitivity(const Niche& niche) const;

    /**
     * @brief L2 distance between parallel vectors @p conditions and @ref tolerances_.
     * @return 0 if sizes differ or either vector is empty.
     */
    double distanceToEnvironmentConditions(const std::vector<double>& conditions) const;

    virtual double calculate_death_biomass(double total_biomass,
                                           double accepted_growth) const override = 0;

    virtual std::vector<std::tuple<int, double>> calculate_growth_biomass(
        const Niche& niche,
        double cohort_biomass) const override = 0;

protected:
    std::vector<double> tolerances_;
    double resilience_{0.5};
};
