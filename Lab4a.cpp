#include <iostream>
#include <forward_list>
#include <vector>
#include <queue>
#include <cstdint>
#include <optional>
#include <cmath>

constexpr static int64_t MOD = 1000000007;

struct Num {
    double logRes = -10000000000;
    int64_t val = 0;
    bool modded = false;

    bool operator>(const Num &rhs) const {
        if (modded) {
            if (!rhs.modded) return true;
            return logRes > rhs.logRes;
        }
        if (rhs.modded) return false;
        return val > rhs.val;
    }
};

struct Node {
    int64_t h{}, a{}, b{}, c{};
    double logh{}, logb{};
    bool visited = false;

    Node() = default;

    Node(int64_t h, int64_t a, int64_t b, int64_t c) :
            h(h), a(a), b(b), c(c), logh(std::log(h)), logb(std::log(b)) {}

    std::optional<Num> calculateThis(const Num &pre) const {
        if (pre.modded) {
            if (pre.logRes < logh) return std::nullopt;
            return Num{pre.logRes + logb, (pre.val * b) % MOD, true};
        }
        if (pre.val < h) return std::nullopt;
        int64_t max = std::max(std::max(pre.val + a, pre.val * b), c);
        return Num{std::log(max), (max) % MOD, max >= MOD};
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    int64_t n, m, c;
    std::cin >> n >> m >> c;
    std::vector<std::forward_list<int>> map(n);
    std::vector<int> inDegree(n);
    std::vector<Node> mapInfo(n);
    for (int i = 0; i < n; i++) {
        int64_t h, a, b, tc;
        std::cin >> h >> a >> b >> tc;
        mapInfo[i] = {h, a, b, tc};
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        map[x - 1].emplace_front(y - 1);
        inDegree[y - 1]++;
    }
    std::vector<Num> ce(n);
    std::queue<int> q;
    q.emplace(0);
    auto firstRes = mapInfo[0].calculateThis({std::log(c), c});
    if (!firstRes.has_value()) {
        std::cout << -1 << std::endl;
        return 0;
    }
    ce[0] = firstRes.value();
    Num max{};
    bool hasAns = false;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (map[now].empty()) {
            hasAns = true;
            if (ce[now] > max) max = ce[now];
        }
        for (auto &v: map[now]) {
            inDegree[v]--;
            auto next = mapInfo[v].calculateThis(ce[now]);
            if (next.has_value()) {
                if (next.value() > ce[v]) {
                    ce[v] = next.value();
                    mapInfo[v].visited = true;
                }
            }
            if (inDegree[v] == 0 && mapInfo[v].visited) {
                q.emplace(v);
            }
        }
    }

    std::cout << (hasAns ? max.val : -1) << std::endl;
}
