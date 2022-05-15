#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (auto &v: nums) {
        std::cin >> v;
    }
    std::vector<int> unique{nums[0]};
    unique.reserve(n);
    for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
        if (*(it - 1) != *it) {
            unique.push_back(*it);
        }
    }
    std::vector<std::vector<int>> dp(unique.size(), std::vector<int>(unique.size()));
    for (int i = 1; i < unique.size(); i++) {
        for (int j = 0; j < unique.size() - i; j++) {
            int l = j, r = j + i;
            dp[l][r] = ((unique[l] == unique[r]) ? dp[l + 1][r - 1] : std::min(dp[l][r - 1], dp[l + 1][r])) + 1;
        }
    }
    std::cout << dp[0].back() << std::endl;
}
