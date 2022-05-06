#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cstring>

// compile time calculation is not working
constexpr const int64_t mod = 1e9 + 7;
constexpr const int precalculated_size = 55;
constexpr const int precalculated_depth = (precalculated_size + 1) / 2;
using precaled_arr_type = std::array<std::array<int64_t, precalculated_size + 1>, precalculated_depth + 1>;

constexpr std::tuple<precaled_arr_type, precaled_arr_type, precaled_arr_type> precalculate() {
    precaled_arr_type dp{}, left{}, right{};
    for (int i = 1; i <= precalculated_size; ++i) {
        dp[1][i] = 1;
    }
    for (int i = 1; i <= precalculated_size; i++) {
        left[1][i] = i;
        right[1][i] = right[1][i - 1] + dp[1][i] * i;
    }

    for (int i = 2; i <= precalculated_depth; i++) {
        for (int j = i + 1; j <= precalculated_size; j++) {
            dp[i][j] = ((j - 1) * left[i - 1][j - 2] - right[i - 1][j - 2]) % mod;
            left[i][j] = (left[i][j - 1] + dp[i][j]) % mod;
            right[i][j] = (right[i][j - 1] + dp[i][j] * j) % mod;
        }
    }
    return {dp, left, right};
}

int main() {
    int n, m;
    std::cin >> n >> m;
    auto [pre_dp, pre_left, pre_right] = precalculate();
    int depth = (std::min(n, m) + 1) / 2, index = std::max(n, m);
    auto get_ans = [&depth, &n, &m](auto &dp) {
        int64_t ans = 0;
        for (int i = 1; i <= depth; i++) {
            ans = (ans + dp[i][n] * dp[i][m] % mod) % mod;
        }
        while (ans < 0) {
            ans += mod;
        }
        return ans;
    };
    if (n <= precalculated_size && m <= precalculated_size) {
        std::cout << get_ans(pre_dp) << std::endl;
        return 0;
    }
    std::vector<std::vector<int64_t>> dp(1001, std::vector<int64_t>(2001, 0));
    auto left = dp, right = dp;
    for (int i = 0; i <= precalculated_depth; i++) {
        memcpy(dp[i].data(), pre_dp[i].data(), (precalculated_size + 1) * sizeof(int64_t));
    }
    std::fill(dp[1].begin() + precalculated_size, dp[1].end(), 1);

    for (int i = precalculated_size; i <= index; i++) {
        left[1][i] = i;
        right[1][i] = right[1][i - 1] + dp[1][i] * i;
    }

    for (int i = precalculated_depth + 1; i <= depth; i++) {
        for (int j = i + 1; j <= index; j++) {
            dp[i][j] = ((j - 1) * left[i - 1][j - 2] - right[i - 1][j - 2]) % mod;
            left[i][j] = (left[i][j - 1] + dp[i][j]) % mod;
            right[i][j] = (right[i][j - 1] + dp[i][j] * j) % mod;
        }
    }

    std::cout << get_ans(dp) << std::endl;
}
