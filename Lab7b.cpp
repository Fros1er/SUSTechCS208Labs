#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct node {
    T sum, maxInterval, maxPre, maxPost;
    int start, end;

    node() = default;

    node(const T &val, int start, int end) : sum(val), maxInterval(val), maxPre(val), maxPost(val), start(start), end(end) {}

    node(const node &left, const node &right, int start, int end) :
            sum(left.sum + right.sum),
            maxInterval(std::max(std::max(left.maxInterval, right.maxInterval), left.maxPost + right.maxPre)),
            maxPre(std::max(left.maxPre, left.sum + right.maxPre)),
            maxPost(std::max(right.maxPost, right.sum + left.maxPost)),
            start(start), end(end) {}
};

template<typename T>
class SegTree {
    std::vector<node<T>> tree;

public:
    explicit SegTree(const std::vector<T> &v) : tree(v.size() << 2) {
        build(v, 1, v.size());
    }

    void build(const std::vector<T> &v, int start, int end, int now = 1) {
        if (start == end) {
            tree[now] = node<T>(v[start - 1], start, end);
            return;
        }
        int mid = start + ((end - start) >> 1);
        int left = now << 1, right = (now << 1) | 1;

        build(v, start, mid, left);
        build(v, mid + 1, end, right);

        tree[now] = node<T>(tree[left], tree[right], start, end);
    }

    node<T> get(int start, int end, int now = 1) {
        if (start <= tree[now].start && tree[now].end <= end) return tree[now];

        int mid = tree[now].start + ((tree[now].end - tree[now].start) >> 1);
        int left = now << 1, right = (now << 1) | 1;

        if (end <= mid) return get(start, end, left);
        if (start > mid) return get(start, end, right);
        node<T> t1 = get(start, mid, left);
        node<T> t2 = get(mid + 1, end, right);
        return node<T>(t1, t2, start, end);
    }
};

int main() {
    int n, q;
    std::cin >> n;
    std::vector<int64_t> v(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        v[i] = x;
    }
    SegTree<int64_t> tree(v);
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        std::cout << tree.get(l, r).maxInterval << std::endl;
    }
}