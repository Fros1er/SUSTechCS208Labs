#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

struct edge {
    int a, b;
    int64_t weight;

    int getChild(int index) {
        return (a == index) ? b : a;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::list<int>> graph(n);
    std::vector<edge> edges(n - 1);
    std::vector<std::pair<int64_t, int64_t>> dp(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        a--;
        b--;
        edges[i] = {a, b, w};
        graph[a].emplace_back(i);
        graph[b].emplace_back(i);
    }
    std::function<int64_t(int, int)> cal = [&cal, &graph, &n, &dp, &edges](int index, int fa) {
        if (graph[index].size() == 1 && index != n - 1) {
            dp[index] = {0, 0};
            return static_cast<int64_t>(0);
        }
        for (auto &v: graph[index]) {
            int ch = edges[v].getChild(index);
            if (ch != fa) {
                dp[ch].second = cal(ch, index);
                dp[index].first += dp[ch].second;
            }
        }
        int64_t max = dp[index].first;
        for (auto &v: graph[index]) {
            int ch = edges[v].getChild(index);
            if (ch != fa) {
                max = std::max(max, edges[v].weight + dp[index].first + dp[ch].first - dp[ch].second);
            }
        }
        dp[index].second = max;
        return max;
    };

    std::cout << cal(n - 1, -1) << std::endl;
}
