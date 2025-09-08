#include "safe_max.hpp"
#include <cmath>      // for std::isnan, std::isinf
#include <limits>     // for std::numeric_limits
#include <vector>

// Function that returns the maximum finite value in a vector<double>
// NaN and Inf values are ignored
double safe_max(const std::vector<double>& v) {
    double max_val = -std::numeric_limits<double>::infinity();
    bool found_valid = false;

    for (double val : v) {
        if (!std::isnan(val) && !std::isinf(val)) {
            if (!found_valid || val > max_val) {
                max_val = val;
                found_valid = true;
            }
        }
    }

    if (!found_valid) {
        // If no valid element was found, return NaN
        return std::numeric_limits<double>::quiet_NaN();
    }
    return max_val;
}
