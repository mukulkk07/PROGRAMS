#include <vector>
#include <set>

std::vector<int> removeDuplicates(const std::vector<int>& input) {
    // A set automatically discards duplicates
    std::set<int> uniqueSet(input.begin(), input.end());
    return std::vector<int>(uniqueSet.begin(), uniqueSet.end());
}