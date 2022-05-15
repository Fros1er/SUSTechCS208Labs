#include <iostream>
#include <vector>

constexpr const int mod = 1e9 + 7;

int main() {
    int n, l, r, max = 0, sum = 0;
    std::cin >> n >> l >> r;
    std::vector<int> scores(n);
    for (auto &v: scores) {
        std::cin >> v;
        max = std::max(max, v);
        sum += v;
    }
    std::vector<int> bucket(max + 1);
    for (auto &v: scores) {
        bucket[v]++;
    }
    std::vector<std::vector<int>> dp(max + 1, std::vector<int>(std::min(sum - l, r) + 1));
    dp[0][0] = 1;
    for (int i = 1; i < dp.size(); i++) {
        std::copy(dp[i - 1].begin(), dp[i - 1].begin() + i, dp[i].begin());
        for (int j = i; j < dp[i].size(); j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            for (int k = 1; k <= bucket[i] && j - k * i >= 0; k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k * i]) % mod;
            }
        }
    }
    int ans = 0;
    for (int i = std::max(sum - r, l); i < dp[max].size(); i++) {
        ans = (ans + dp[max][i]) % mod;
    }
    std::cout << ans << std::endl;
}
