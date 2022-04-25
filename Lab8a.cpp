#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>

constexpr const double pi = 3.14159265358979323846264338;

void fft(std::vector<std::complex<double>> &a) {
    if (a.size() == 1) return;
    std::vector<std::complex<double>> odd(a.size() / 2), even(a.size() / 2);
    for (int i = 0; i < a.size(); i += 2) even[i / 2] = a[i];
    for (int i = 1; i < a.size(); i += 2) odd[i / 2] = a[i];
    fft(even);
    fft(odd);
    for (int k = 0; k < a.size() / 2; k++) {
        std::complex<double> omega = std::exp(2 * k * pi * std::complex<double>(0, 1) / static_cast<double>(a.size()));
        a[k] = even[k] + omega * odd[k];
        a[k + a.size() / 2] = even[k] - omega * odd[k];
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::complex<double>> a(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        double x;
        std::cin >> x;
        a[i] = {x, 0};
    }
    fft(a);
    for (auto &v : a) {
        std::cout << std::fixed << std::setprecision(10) << abs(v) << std::endl;
    }
}
