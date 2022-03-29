#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cstdint>
#include <cmath>
#include <array>

struct Num {
    int64_t sec, income;
    int pos;

    bool operator<(const Num &rhs) const {
        return sec < rhs.sec;
    }
};

struct Interval {
    int l, r;
    int64_t passedTime, sum;

};

template<typename T>
class SparseTable {
    std::vector<std::vector<T>> f;
    std::vector<int> logN;

public:
    explicit SparseTable(const std::vector<T> &src) :
            f(src.size() + 1, std::vector<T>(std::log2(src.size()) + 1)),
            logN(src.size() + 1) {
        logN[1] = 0;
        logN[2] = 1;
        for (int i = 3; i < src.size() + 1; i++) {
            logN[i] = logN[i / 2] + 1;
        }
        for (int i = 1; i <= src.size(); i++) {
            f[i][0] = src[i - 1];
        }
        for (int j = 1; j <= std::log2(src.size()); j++) {
            for (int i = 1; i + (1 << j) - 1 <= src.size(); i++)
                f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }

    T query(int l, int r) const {
        int s = logN[r - l + 1];
        return std::min(f[l + 1][s], f[r - (1 << s) + 2][s]);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int64_t m;
    std::cin >> n >> m;
    std::vector<Num> a(n);
    std::vector<int64_t> prefix(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].sec;
        a[i].pos = i;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].income;
        prefix[i + 1] = a[i].income + prefix[i];
    }

    auto cmp = [](const Interval &l, const Interval &r) {
        return l.sum < r.sum;
    };
    std::priority_queue<Interval, std::vector<Interval>, decltype(cmp)> pq(cmp);
    pq.push({0, n - 1, 0, prefix[n]});

    SparseTable<Num> st(a);

    int64_t res = 0;

//    for (auto &v: prefix) std::cout << v << " ";
//    std::cout << std::endl;

    while (!pq.empty()) {
        Interval now = pq.top();
        pq.pop();
        Num min = st.query(now.l, now.r);
        int64_t sec = min.sec - now.passedTime;
        if (sec >= m) {
            res += (m * now.sum);
            break;
        }
        res += (sec * now.sum);
        m -= sec;
        if (min.pos - 1 >= now.l) {
            pq.push({now.l, min.pos - 1, now.passedTime + sec, prefix[min.pos] - prefix[now.l]});
        }
        if (now.r >= min.pos + 1) {
            pq.push({min.pos + 1, now.r, now.passedTime + sec, prefix[now.r + 1] - prefix[min.pos + 1]});
        }
    }

    std::cout << res << std::endl;
}
