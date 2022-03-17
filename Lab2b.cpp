#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> graph(n);
    std::vector<int> dis(n, 2147483647);
    std::vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (i != x - 1) graph[i].emplace(x - 1);
        if (i - 1 >= 0) graph[i].emplace(i - 1);
        if (i + 1 < n) graph[i].emplace(i + 1);
    }
    dis[0] = 0;
    std::queue<int> q;
    q.emplace(0);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto &v : graph[now]) {
            if (dis[v] > dis[now] + 1) {
                dis[v] = dis[now] + 1;
                if (!vis[v]) {
                    vis[v] = true;
                    q.emplace(v);
                }
            }
        }
        vis[now] = false;
    }
    for (auto &v : dis) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}
