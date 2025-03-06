#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Функция Radix Sort
void radixSort(std::vector<uint32_t>& arr) {
    constexpr int BITS = 8;
    constexpr int BASE = 1 << BITS;
    constexpr int MASK = BASE - 1;
    
    std::vector<uint32_t> temp(arr.size());
    for (int shift = 0; shift < 32; shift += BITS) {
        std::vector<int> count(BASE, 0);

        for (uint32_t num : arr)
            count[(num >> shift) & MASK]++;

        for (int i = 1; i < BASE; i++)
            count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--)
            temp[--count[(arr[i] >> shift) & MASK]] = arr[i];

        arr.swap(temp);
    }
}

// Генерация случайного массива с заданным максимальным значением
std::vector<uint32_t> generateRandomArray(size_t N, uint32_t max_value) {
    std::vector<uint32_t> arr(N);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<uint32_t> dist(0, max_value);
    
    for (auto& x : arr) x = dist(rng);
    return arr;
}

// Функция измерения времени выполнения
template <typename Func>
double measureTime(Func sortFunction, std::vector<uint32_t>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(arr);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    size_t N = 100000;  // Фиксированный размер массива
    std::vector<uint32_t> bit_ranges = {255, 65535, 4294967295};  // 8, 16, 32 бит

    std::cout << "Bits,RadixSort,stdSort\n";
    for (uint32_t max_value : bit_ranges) {
        std::vector<uint32_t> arr = generateRandomArray(N, max_value);

        std::vector<uint32_t> copy1 = arr;
        double radixTime = measureTime(radixSort, copy1);

        std::vector<uint32_t> copy2 = arr;
        double stdSortTime = measureTime([](std::vector<uint32_t>& v) { std::sort(v.begin(), v.end()); }, copy2);

        std::cout << max_value << "," << radixTime << "," << stdSortTime << "\n";
    }

    return 0;
}
