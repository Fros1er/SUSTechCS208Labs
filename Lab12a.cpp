#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <functional>
#include <limits>

struct Edge {
    int from, to;
    int64_t cap, flow;

    Edge() = default;

    Edge(int from, int to, int64_t c, int64_t f) : from(from), to(to), cap(c), flow(f) {}
};

int main() {
    int n, m, s, t;
    int64_t flow = 0;
    std::cin >> n >> m >> s >> t;
    s--;
    t--;
    std::vector<Edge> edges(m << 1);
    std::vector<std::list<int>> graph(n);
    std::vector<int> depth(n);

    for (int i = 0; i < (m << 1); i += 2) {
        int u, v, c;
        std::cin >> u >> v >> c;
        edges[i] = {u - 1, v - 1, c, 0};
        edges[i + 1] = {v - 1, u - 1, 0, 0};
        graph[u - 1].emplace_back(i);
        graph[v - 1].emplace_back(i + 1);
    }

    std::vector<std::list<int>::iterator> cur(n);

    std::function<int(int64_t , int64_t)> dfs = [&t, &edges, &graph, &depth, &cur, &dfs](int64_t now, int64_t minFlow) {
        if (now == t || minFlow == 0) return minFlow;
        int64_t flow = 0, f;
        for (auto &it = cur[now]; it != graph[now].end(); ++it) {
            Edge &e = edges[*it];
            if (depth[now] + 1 == depth[e.to] && (f = dfs(e.to, std::min(minFlow, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[*it ^ 1].flow -= f;
                flow += f;
                minFlow -= f;
                if (minFlow == 0) break;
            }
        }
        return flow;
    };

    while (true) {
        std::vector<bool> vis(n);
        std::queue<int> q;
        q.push(s);
        depth[s] = 0;
        vis[s] = true;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto &v : graph[x]) {
                Edge &e = edges[v];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    depth[e.to] = depth[x] + 1;
                    q.push(e.to);
                }
            }
        }
        if (!vis[t]) break;
        for (int i = 0; i < n; i++) {
            cur[i] = graph[i].begin();
        }
        flow += dfs(s, std::numeric_limits<int>::max());
    }

    std::cout << flow << std::endl;
}
