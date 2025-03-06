#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

// Шейкерная сортировка
void shakerSort(vector<int>& arr) {
    bool swapped;
    int left = 0, right = arr.size() - 1;
    do {
        swapped = false;
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        --right;
        for (int i = right; i > left; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        ++left;
    } while (swapped);
}

// Сортировка расческой
void combSort(vector<int>& arr) {
    int gap = arr.size();
    const double shrinkFactor = 1.3;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = max(1, int(gap / shrinkFactor));
        swapped = false;
        for (int i = 0; i + gap < arr.size(); ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// Функция для создания массива с заданной степенью перемешанности
vector<int> generateShuffledArray(int size, double shufflePercentage) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i; // Заполняем отсортированным массивом
    }
    int shuffleCount = (size * shufflePercentage) / 100; // Количество элементов для перемешивания
    for (int i = 0; i < shuffleCount; ++i) {
        swap(arr[rand() % size], arr[rand() % size]);
    }
    return arr;
}

// Функция для измерения времени сортировки в наносекундах
long long measureTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    clock_t start = clock();
    sortFunc(arr);
    clock_t end = clock();
    return static_cast<long long>(end - start) * 1'000'000'000 / CLOCKS_PER_SEC;
}

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел

    // Размеры массивов
    vector<int> sizes = {10, 100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    // Степени перемешанности
    vector<double> shufflePercentages = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Заголовок таблицы
    cout << "Size, Sortedness, Bubble (ns), Shaker (ns), Comb (ns)\n";

    // Перебор всех размеров массивов
    for (int size : sizes) {
        // Перебор всех степеней перемешанности
        for (double shuffle : shufflePercentages) {
            // Генерация массива с заданной степенью перемешанности
            vector<int> arr = generateShuffledArray(size, shuffle);

            // Копии массива для каждой сортировки
            vector<int> arrBubble = arr;
            vector<int> arrShaker = arr;
            vector<int> arrComb = arr;

            // Измерение времени для каждой сортировки
            long long timeBubble = measureTime(bubbleSort, arrBubble);
            long long timeShaker = measureTime(shakerSort, arrShaker);
            long long timeComb = measureTime(combSort, arrComb);

            // Вывод результатов в одну строку
            cout << "Size: " << size
                 << ", Sortedness: " << fixed << setprecision(2) << shuffle / 100.0
                 << ", Bubble: " << timeBubble << " ns"
                 << ", Shaker: " << timeShaker << " ns"
                 << ", Comb: " << timeComb << " ns\n";
        }
    }

    return 0;
}