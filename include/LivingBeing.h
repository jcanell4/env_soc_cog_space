#pragma once

/**
 * @file LivingBeing.h
 * @brief Abstract base for all species in the ecosystem model.
 */

#include <string>
#include <tuple>
#include <vector>

class Niche;

/**
 * @class LivingBeing
 * @brief Base type for living entities: identity, energy content, and abstract biomass dynamics.
 *
 * Concrete subclasses implement death and growth rules. Energy is stored per unit biomass
 * via @ref energy_content_.
 */
class LivingBeing {
public:
    virtual ~LivingBeing() = 0;

    /** @return Species name. */
    const std::string& getName() const;

    /** @return Energy per unit biomass (model-specific units). */
    float getEnergyContent() const;

    /**
     * @brief Dead biomass produced in a timestep given realized growth.
     * @param total_biomass Current living biomass of the cohort.
     * @param accepted_growth Growth actually realized (after environment limits).
     * @return Mass moved from living to dead pool for this step.
     */
    virtual double calculate_death_biomass(double total_biomass,
                                           double accepted_growth) const = 0;

    /**
     * @brief Potential growth split into tagged terms for the niche to resolve.
     * @param niche Niche context (nutrients, space, conditions, other cohorts).
     * @param cohort_biomass Current living biomass of this cohort.
     * @return List of (code, biomass_growth). Interpretation of @p code is type-specific
     *         (e.g. @ref NUTRIENTS_POS for nutrient-limited autotroph growth).
     */
    virtual std::vector<std::tuple<int, double>> calculate_growth_biomass(
        const Niche& niche,
        double cohort_biomass) const = 0;

protected:
    LivingBeing() = default;

    /** @param name Display / lookup name for the species. */
    explicit LivingBeing(std::string name, float energy_content);

    std::string name_;
    float energy_content_{0.0f};
};
