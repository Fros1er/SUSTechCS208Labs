#include <iostream>
#include <vector>
#include <forward_list>
#include <algorithm>

constexpr const int mod = 1e9 + 7;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::forward_list<int>> graph(n);
    std::vector<int64_t> dp(1 << n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].emplace_front(v - 1);
    }
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        dp[1 << i] = 1;
    }
    for (int i = 1; i < dp.size() - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (!((i >> j) & 1)) {
                size_t num = std::count_if(graph[j].begin(), graph[j].end(), [&i](int &v){
                    return (i >> v) & 1;
                });
                int t = i + (1 << j);
                dp[t] = (dp[t] + dp[i] * (1 << num)) % mod;
            }
        }
    }
    std::cout << dp.back() << std::endl;
}