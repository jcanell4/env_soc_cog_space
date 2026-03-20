#include "Autotroph.h"
#include "Niche.h"

#include <algorithm>
#include <cmath>
#include <utility>

Autotroph::Autotroph(std::string name, float energy_content, double resilience)
    : LivingBeing(std::move(name), energy_content),
      resilience_(std::clamp(resilience, 0.0, 1.0)) {}

Autotroph::Autotroph(std::string name,
                     std::vector<double> tolerances,
                     float energy_content,
                     double resilience)
    : LivingBeing(std::move(name), energy_content),
      tolerances_(std::move(tolerances)),
      resilience_(std::clamp(resilience, 0.0, 1.0)) {
    // Normalize tolerance values so they stay compatible with niche conditions in [0, 1].
    for (auto& x : tolerances_) {
        x = std::clamp(x, 0.0, 1.0);
    }
}

const std::vector<double>& Autotroph::getTolerances() const {
    return tolerances_;
}

void Autotroph::setTolerances(std::vector<double> tolerances) {
    for (auto& x : tolerances) {
        x = std::clamp(x, 0.0, 1.0);
    }
    tolerances_ = std::move(tolerances);
}

double Autotroph::getResilience() const {
    return resilience_;
}

void Autotroph::setResilience(double resilience) {
    resilience_ = std::clamp(resilience, 0.0, 1.0);
}

double Autotroph::getEnvironmentSensitivity(const Niche& niche) const {     
    const auto& conditions = niche.getConditions();
    if (conditions.empty()) {
        return 0.0;
    }

    const double distance = distanceToEnvironmentConditions(conditions);
    const double max_distance = std::sqrt(static_cast<double>(conditions.size()));
    if (max_distance == 0.0) {
        return 0.0;
    }
    const double sensitivity = distance / max_distance;

    return niche.getBiologicalPotential() * sensitivity;
}

double Autotroph::distanceToEnvironmentConditions(const std::vector<double>& conditions) const {
    const auto& tolerances = getTolerances();

    if (conditions.empty() || tolerances.empty() || conditions.size() != tolerances.size()) {
        return 0.0;
    }

    double sum_sq = 0.0;
    for (size_t i = 0; i < conditions.size(); ++i) {
        const double diff = conditions[i] - tolerances[i];
        sum_sq += diff * diff;
    }

    return std::sqrt(sum_sq);
}
