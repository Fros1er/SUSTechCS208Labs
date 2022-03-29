#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cstdint>

constexpr static uint64_t MOD = 1000000007;

std::vector<uint64_t> genPath(std::vector<std::list<int>> &map, std::vector<std::list<int>> &reverseMap) {
    std::queue<int> q;
    std::vector<uint64_t> path(map.size());
    std::vector<int> inDegree(map.size());
    for (int i = 0; i < map.size(); i++) {
        inDegree[i] = static_cast<int>(reverseMap[i].size());
        if (reverseMap[i].empty()) {
            q.emplace(i);
            path[i] = 1;
        }
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto &v: map[now]) {
            if (--inDegree[v] == 0) {
                q.emplace(v);
            }
            path[v] += path[now];
            path[v] %= MOD;
        }
    }
    return std::move(path);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::list<int>> map(n), reverseMap(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        map[x - 1].emplace_back(y - 1);
        reverseMap[y - 1].emplace_back(x - 1);
    }
    auto path = genPath(map, reverseMap);
    auto reversePath = genPath(reverseMap, map);

    for (int i = 0; i < n; i++) {
        std::cout << ((path[i] % MOD) * (reversePath[i] % MOD)) % MOD << " ";
    }
}
