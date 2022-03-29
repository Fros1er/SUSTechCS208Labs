#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

inline int read() {
    int x = 0, f = 1;
    int ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n = read(), m = read(), c = read(), t = read();
    std::vector<int> bunnies(n), nests(m), nestsContaining(m);
    for (int i = 0; i < n; i++) {
        bunnies[i] = read();
    }
    for (int i = 0; i < m; i++) {
        nests[i] = read();
    }
    std::sort(bunnies.begin(), bunnies.end());
    std::sort(nests.begin(), nests.end());
    int pre = 0, ans = 0;
    for (auto &bunny: bunnies) {
        for (int i = pre; i < m; i++) {
            int dis = bunny - nests[i];
            if (dis < -t)
                break;
            if (dis > t || nestsContaining[i] >= c) {
                pre = i;
                continue;
            }
            nestsContaining[i]++;
            ans++;
            break;
        }
    }
    printf("%d ", ans);
}
