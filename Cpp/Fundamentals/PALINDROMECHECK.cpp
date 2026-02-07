#include <iostream>
#include <string>
#include <cctype>

bool isPalindrome(std::string s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        if (!std::isalnum(s[left])) {
            left++;
        } else if (!std::isalnum(s[right])) {
            right--;
        } else {
            // Compare characters (case-insensitive)
            if (std::tolower(s[left]) != std::tolower(s[right])) {
                return false;
            }
            left++;
            right--;
        }
    }
    return true;
}