#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>

constexpr uint64_t Mod = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::list<int>> graph(n);
    std::vector<bool> passed(n, false);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].emplace_front(b - 1);
        graph[b - 1].emplace_front(a - 1);
    }
    uint64_t ans = 1;
    std::queue<int> q;
    q.emplace(0);

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        passed[now] = true;
        int cnt = 1;
        for (auto &v: graph[now]) {
            if (!passed[v]) {
                ans *= (cnt++);
                ans %= Mod;
                q.emplace(v);
            }
        }
    }
    std::cout << ans % Mod << std::endl;
}
