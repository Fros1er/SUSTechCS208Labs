#include <iostream>
#include <vector>
#include <cstring>

constexpr const int64_t mod = 1e9 + 7;

template<typename T>
class SquareMatrix {
    size_t _size;
    std::vector<T> _base;

public:
    explicit SquareMatrix(size_t size) : _size(size), _base(size * size, 0) {}

    SquareMatrix(SquareMatrix &&rhs) noexcept = default;

    SquareMatrix &operator=(SquareMatrix &&rhs) noexcept = default;

    T &operator()(size_t row, size_t col) {
        return _base[row * _size + col];
    }

    void clear() {
        memset(_base.data(), 0, sizeof(T) * _base.size());
    }

    [[nodiscard]]
    size_t size() const {
        return _size;
    }

    void swap(SquareMatrix<T> &other) {
        using std::swap;
        swap(_size, other._size);
        swap(_base, other._base);
    }
};

template<typename T>
SquareMatrix<T> quickPower(SquareMatrix<T> &base, int exp) {
    SquareMatrix<T> res(base.size());
    SquareMatrix<T> buffer(base.size());

    auto bufferedSquareMatMul =
            [&buffer](SquareMatrix<T> &lhs, SquareMatrix<T> &rhs) {
                for (size_t i = 0; i < lhs.size(); i++) {
                    for (size_t k = 0; k < lhs.size(); k++) {
                        const T tmp = lhs(i, k);
                        for (size_t j = 0; j < lhs.size(); j++) {
                            buffer(i, j) = (buffer(i, j) + (tmp * rhs(k, j)) % mod) % mod;
                        }
                    }
                }
            };

    for (int i = 0; i < base.size(); i++) {
        res(i, i) = 1;
    }
    while (exp) {
        if (exp & 1) {
            bufferedSquareMatMul(res, base);
            res.swap(buffer);
            buffer.clear();
        }
        bufferedSquareMatMul(base, base);
        base.swap(buffer);
        buffer.clear();
        exp >>= 1;
    }
    return std::move(res);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    SquareMatrix<int64_t> mat(m);
    for (int i = 0; i < m; i++) {
        mat(i, 0) = 1;
    }
    for (int i = 0; i < m - 1; i++) {
        mat(i, i + 1) = 1;
    }
    mat = quickPower(mat, n);
    int64_t ans = 0;
    for (int i = 0; i < m; i++) {
        ans += mat(0, i);
        ans %= mod;
    }
    std::cout << ans << std::endl;
}
