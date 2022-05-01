// Thanks https://oi-wiki.org/ds/persistent-seg/
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

struct Node {
    int sum = 0;
    size_t left = 0, right = 0;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::vector<int> sorted(a);
    std::sort(sorted.begin() + 1, sorted.end());
    auto last = std::unique(sorted.begin() + 1, sorted.end());
    sorted.erase(last, sorted.end());
    std::unordered_map<int, int> sorted_reverse_kv(sorted.size() - 1);
    for (int i = 1; i < sorted.size(); i++) {
        sorted_reverse_kv[sorted[i]] = i;
    }
    std::vector<size_t> roots(n + 1);
    std::vector<Node> nodes(1);

    std::function<size_t(size_t, size_t)> build = [&nodes, &build](size_t l, size_t r) {
        size_t root = nodes.size();
        nodes.push_back({});
        if (l != r) {
            size_t mid = (l + r) / 2;
            nodes[root].left = build(l, mid);
            nodes[root].right = build(mid + 1, r);
        }
        return root;
    };

    std::function<size_t(int, size_t, size_t, size_t)> update =
            [&nodes, &update](int val, size_t l, size_t r, size_t root) {
                size_t now = nodes.size();
                nodes.push_back({nodes[root].sum + 1, nodes[root].left, nodes[root].right});
                if (l != r) {
                    size_t mid = (l + r) / 2;
                    if (val <= mid)
                        nodes[now].left = update(val, l, mid, nodes[now].left);
                    else
                        nodes[now].right = update(val, mid + 1, r, nodes[now].right);
                }
                return now;
            };

    roots[0] = build(1, sorted.size() - 1);
    for (int i = 1; i <= n; ++i)
        roots[i] = update(sorted_reverse_kv[a[i]], 1, sorted.size() - 1, roots[i - 1]);

    std::function<size_t(size_t, size_t, size_t, size_t, int)> query =
            [&nodes, &query](size_t u, size_t v, size_t l, size_t r, int k) {
                if (l == r) return l;
                size_t mid = (l + r) / 2;
                int x = nodes[nodes[v].left].sum - nodes[nodes[u].left].sum;
                if (k <= x)
                    return query(nodes[u].left, nodes[v].left, l, mid, k);
                else
                    return query(nodes[u].right, nodes[v].right, mid + 1, r, k - x);
            };

    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        std::cout << sorted[query(roots[l - 1], roots[r], 1, sorted.size() - 1, (r - l + 2) / 2)] << std::endl;
    }
    return 0;
}
