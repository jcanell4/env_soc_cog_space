#pragma once

#include "LivingBeing.h"

#include <tuple>
#include <vector>

class Niche;

/**
 * Autotroph is a living entity that produces its own food.
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

    const std::vector<double>& getTolerances() const;
    void setTolerances(std::vector<double> tolerances);
    double getResilience() const;
    void setResilience(double resilience);

    /**
     * Computes environment sensitivity as described by:
     * biological_potential / average(product(C, T))
     * where C = niche conditions vector and T = autotroph tolerances vector.
     */
    double getEnvironmentSensitivity(const Niche& niche) const;

    /**
     * Computes distance between environment `conditions` (e.g. humidity, sun radiance)
     * and this autotroph's `tolerances_` vector (same characteristics by position).
     *
     * Distance is computed as Euclidean (L2) norm.
     */
    double distanceToEnvironmentConditions(const std::vector<double>& conditions) const;

    /**
     * Computes dead biomass contribution for the next step.
     * Must be implemented by each concrete autotroph model.
     */
    virtual double calculate_death_biomass(double total_biomass,
                                           double accepted_growth) const override = 0;

    virtual std::vector<std::tuple<int, double>> calculate_growth_biomass(
        const Niche& niche,
        double cohort_biomass) const override = 0;

protected:
    std::vector<double> tolerances_;
    double resilience_{0.5};
};
