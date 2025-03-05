#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Функция Radix Sort (поразрядная сортировка)
void radixSort(std::vector<uint32_t>& arr) {
    constexpr int BITS = 8;  // Обрабатываем по 8 бит за проход (байт)
    constexpr int BASE = 1 << BITS;  // 256 значений
    constexpr int MASK = BASE - 1;
    
    std::vector<uint32_t> temp(arr.size());
    for (int shift = 0; shift < 32; shift += BITS) {
        std::vector<int> count(BASE, 0);

        // Подсчитываем количество элементов для каждой корзины
        for (uint32_t num : arr) {
            count[(num >> shift) & MASK]++;
        }

        // Преобразуем в префиксные суммы для определения позиций элементов
        for (int i = 1; i < BASE; i++) {
            count[i] += count[i - 1];
        }

        // Размещение элементов в правильные позиции
        for (int i = arr.size() - 1; i >= 0; i--) {
            uint32_t num = arr[i];
            temp[--count[(num >> shift) & MASK]] = num;
        }

        // Копируем отсортированные данные обратно
        arr.swap(temp);
    }
}

// Функция генерации частично перемешанного массива
std::vector<uint32_t> generatePartiallySortedArray(size_t N, double disorder) {
    std::vector<uint32_t> arr(N);
    for (size_t i = 0; i < N; ++i)
        arr[i] = i;

    std::mt19937 rng(std::random_device{}());
    int swaps = N * disorder;

    for (int i = 0; i < swaps; ++i) {
        int a = rng() % N;
        int b = rng() % N;
        std::swap(arr[a], arr[b]);
    }

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
    std::vector<double> disorder_levels = {0.2, 0.4, 0.6, 0.8, 1.0};

    std::cout << "Disorder,RadixSort,stdSort\n";
    for (double disorder : disorder_levels) {
        std::vector<uint32_t> arr = generatePartiallySortedArray(N, disorder);

        std::vector<uint32_t> copy1 = arr;
        double radixTime = measureTime(radixSort, copy1);

        std::vector<uint32_t> copy2 = arr;
        double stdSortTime = measureTime([](std::vector<uint32_t>& v) { std::sort(v.begin(), v.end()); }, copy2);

        std::cout << disorder << "," << radixTime << "," << stdSortTime << "\n";
    }

    return 0;
}