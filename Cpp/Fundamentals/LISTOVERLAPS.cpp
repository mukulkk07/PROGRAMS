#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<int> findOverlap(const std::vector<int>& listA, const std::vector<int>& listB) {
    std::set<int> setA(listA.begin(), listA.end());
    std::set<int> overlap;

    for (int num : listB) {
        if (setA.count(num)) {
            overlap.insert(num);
        }
    }
    return std::vector<int>(overlap.begin(), overlap.end());
}