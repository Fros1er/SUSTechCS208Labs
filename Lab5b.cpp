#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <queue>

struct edge {
    int to;
    int64_t w;
    int num;
};

int main() {
    int n, m, p;
    std::cin >> n >> m;
    std::vector<std::forward_list<edge>> graph(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        int64_t w;
        std::cin >> x >> y >> w;
        graph[x - 1].emplace_front(edge{y - 1, w, i});
        graph[y - 1].emplace_front(edge{x - 1, w, i});
    }
    std::cin >> p;
    std::vector<int> result(m);
    for (int i = 0; i < p; i++) {
        int start, end;
        std::cin >> start >> end;
        start--;
        end--;

        std::vector<int64_t> dis(n, 12145217483647);
        std::vector<std::list<std::pair<int, int>>> shortestFrom(n);
        auto cmp = [](const std::pair<int, int64_t> &a, const std::pair<int, int64_t> &b) {
            return a.second > b.second;
        };
        std::priority_queue<std::pair<int, int64_t>, std::vector<std::pair<int, int64_t>>, decltype(cmp)> pq(
                cmp);
        pq.emplace(start, 0);
        dis[start] = 0;
        while (!pq.empty()) {
            auto[dist, now] = pq.top();
            pq.pop();
            if (dis[dist] < now)
                continue;
            for (auto &v: graph[dist]) {
                int next = v.to;
                int64_t d = dis[dist] + v.w;
                if (d < dis[next]) {
                    dis[next] = d;
                    pq.emplace(next, d);
                    shortestFrom[next].clear();
                    shortestFrom[next].emplace_back(dist, v.num);
                } else if (d == dis[next]) {
                    shortestFrom[next].emplace_back(dist, v.num);
                }
            }
        }

        std::queue<int> q;
        std::vector<bool> searched(n, false);
        q.emplace(end);
        searched[end] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();

            for (auto &v: shortestFrom[now]) {
                result[v.second]++;
                int next = v.first;
                if (!searched[next]) {
                    searched[next] = true;
                    q.emplace(next);
                }
            }
        }
    }
    for (auto &v: result) {
        std::cout << v << std::endl;
    }
}
