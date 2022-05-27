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
    int tc;
    std::cin >> tc;
    for (int k = 0; k < tc; k++) {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;
        std::vector<std::vector<bool>> grid(n, std::vector<bool>(m));
        std::vector<Edge> edges(12 * m * n + 4 * m);
        std::vector<std::list<int>> graph(2 * n * m + 2);
        std::vector<int> depth(2 * n * m + 2);
        for (int i = 0; i < n; i++) {
            std::string line;
            std::cin >> line;
            for (int j = 0; j < m; j++) {
                grid[i][j] = line[j] == '1';
            }
        }
        int now = 0;
        for (int i = 0; i < a; i++) {
            int tmp;
            std::cin >> tmp;
            edges[now] = {2 * n * m, (tmp - 1) << 1, 1, 0};
            edges[now + 1] = {(tmp - 1) << 1, 2 * n * m, 0, 0};
            graph[2 * n * m].emplace_back(now);
            graph[(tmp - 1) << 1].emplace_back(now + 1);
            now += 2;
        }
        for (int i = 0; i < b; i++) {
            int tmp;
            std::cin >> tmp;
            edges[now + 1] = {2 * n * m + 1, (m * (n - 1) + tmp - 1) << 1, 0, 0};
            edges[now] = {(m * (n - 1) + tmp - 1) << 1, 2 * n * m + 1, 1, 0};
            graph[(m * (n - 1) + tmp - 1) << 1].emplace_back(now);
            graph[2 * n * m + 1].emplace_back(now + 1);
            now += 2;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int base = (i * m + j) << 1;
                int down = ((i + 1) * m + j) << 1;
                int right = ((i * m + j + 1) << 1) + 1;
                edges[now] = {base, base + 1, 1, 0};
                edges[now + 1] = {base + 1, base, 0, 0};
                edges[now + 2] = {base + 1, base, 1, 0};
                edges[now + 3] = {base, base + 1, 0, 0};
                graph[base].emplace_back(now);
                graph[base + 1].emplace_back(now + 1);
                graph[base + 1].emplace_back(now + 2);
                graph[base].emplace_back(now + 3);
                now += 4;
                if (i != n - 1 && grid[i][j] == 0 && grid[i + 1][j] == 0) {
                    edges[now] = {base, down, 1, 0};
                    edges[now + 1] = {down, base, 0, 0};
                    edges[now + 2] = {down, base, 1, 0};
                    edges[now + 3] = {base, down, 0, 0};
                    graph[base].emplace_back(now);
                    graph[down].emplace_back(now + 1);
                    graph[down].emplace_back(now + 2);
                    graph[base].emplace_back(now + 3);
                    now += 4;
                }
                if (j != m - 1 && grid[i][j] == 0 && grid[i][j+1] == 0) {
                    edges[now] = {base + 1, right, 1, 0};
                    edges[now + 1] = {right, base + 1, 0, 0};
                    edges[now + 2] = {right, base + 1, 1, 0};
                    edges[now + 3] = {base + 1, right, 0, 0};
                    graph[base + 1].emplace_back(now);
                    graph[right].emplace_back(now + 1);
                    graph[right].emplace_back(now + 2);
                    graph[base + 1].emplace_back(now + 3);
                    now += 4;
                }
            }
        }

        int s = 2 * n * m, t = 2 * n * m + 1;
        int64_t flow = 0;

        std::vector<std::list<int>::iterator> cur(graph.size());

        std::function<int(int64_t, int64_t)> dfs = [&t, &edges, &graph, &depth, &cur, &dfs](int64_t now,
                                                                                            int64_t minFlow) {
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
            std::vector<bool> vis(graph.size());
            std::queue<int> q;
            q.push(s);
            depth[s] = 0;
            vis[s] = true;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (auto &v: graph[x]) {
                    Edge &e = edges[v];
                    if (!vis[e.to] && e.cap > e.flow) {
                        vis[e.to] = true;
                        depth[e.to] = depth[x] + 1;
                        q.push(e.to);
                    }
                }
            }
            if (!vis[t]) break;
            for (int i = 0; i < graph.size(); i++) {
                cur[i] = graph[i].begin();
            }
            flow += dfs(s, std::numeric_limits<int>::max());
        }

        std::cout << ((flow == a) ? "Yes" : "No") << std::endl;
    }
}
