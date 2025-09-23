#include <iostream>
#include <vector>
#include <utility>
#include <limits>

// Function to find the three smallest values and their indices
std::vector<int> three_min(const std::vector<double>& v) {
    // Initialize with +infinity and invalid index
    std::vector<double> min_vals(3, std::numeric_limits<double>::infinity());
    std::vector<int> min_idx(3, -1);

    for (int i = 0; i < (int)v.size(); ++i) {
        double val = v[i];

        // Insert val into min_vals if it's among the 3 smallest
        for (int k = 0; k < 3; ++k) {
            if (val < min_vals[k]) {
                // Shift larger values to the right
                for (int j = 2; j > k; --j) {
                    min_vals[j] = min_vals[j-1];
                    min_idx[j] = min_idx[j-1];
                }
                // Insert new min
                min_vals[k] = val;
                min_idx[k] = i;
                break;
            }
        }
    }

    return {min_idx};
}
