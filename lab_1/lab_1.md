# Лабораторная работа №1: Асимптотическая сложность
### Цель:
проверить прямыми измерениями времени асимптотическую сложность алгоритмов по времени в зависимости от объёма данных.

## Поиск перебором
1. Напишем алгоритм поиска перебором ```Search```

```C++
void Search(int s, int n, int* arr) {
    int i = 0;
    while (i < n && arr[i] != s) {
        ++i;
    }
}
```

---
2. Проанализируем работу алгоритма для наихудшего случая

Полный код:
```C++
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


void FillWithRandomValues(int n, int* arr) {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i){
        arr[i] = rnd() % 1'000'000 + 1;
    }
}


void Search(int s, int n, int* arr) {
    int i = 0;
    while (i < n && arr[i] != s) {
        ++i;
    }
}


int main() {
    std::ofstream f("1.csv", std::ios::out);
    f << 0 << std::endl; // np считает первый элемент столбца его заголовком
    for (unsigned size = 1000; size <= 1'000'000; size += 1000) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now());
        for (unsigned test = 1; test <= 100; ++test) {
            srand(time(NULL));

            int s = 100000000; // number to search
            int* arr = new int[size];

            FillWithRandomValues(size, arr);

            auto begin = std::chrono::steady_clock::now();
            Search(s, size, arr);
            auto end = std::chrono::steady_clock::now();

            time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            delete(arr);
        }
        f << time_span.count() / 100 << std::endl;
    }
    return 0;
}
```

---
3. Построим график зависимости времени выполнения алгоритма от размера массива

```python
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.figure(dpi=1000)

df = pd.read_csv('\\\wsl.localhost\\Ubuntu-20.04\\home\erykalkin\\C++\\1.csv').to_numpy()
y = df[:, 0]
x = np.arange(1000, 1000001, 1000)

k, b = np.polyfit(x, y, 1)
x_fit = np.array([0, 1000000])
y_fit = x_fit * k + b

plt.plot(x_fit, y_fit, color='r')
plt.scatter(x, y, s=1)

print(k, b)
plt.show()
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image.png)

Видим, что точки действительно ложатся на прямую, сложность алгоритма O(N)

k = 2 $\Rightarrow$ время работы одной операции примерно равно 2 наносекундам.

---
4. Проанализируем работу алгоритма для случайных чисел

Код:
```C++
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


void FillWithRandomValues(int n, int* arr) {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i){
        arr[i] = rnd() % 1'000'000 + 1;
    }
}


void Search(int s, int n, int* arr) {
    int i = 0;
    while (i < n && arr[i] != s) {
        ++i;
    }
}


int main() {
    std::ofstream f("1.csv", std::ios::out);
    f << 0 << std::endl; // np считает первый элемент столбца его заголовком
    for (unsigned size = 1000; size <= 1'000'000; size += 1000) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now());
        for (unsigned test = 1; test <= 100; ++test) {
            srand(time(NULL));

            int s = rnd() % 1'000'000 + 1; // number to search
            int* arr = new int[size];

            FillWithRandomValues(size, arr);

            auto begin = std::chrono::steady_clock::now();
            Search(s, size, arr);
            auto end = std::chrono::steady_clock::now();

            time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            delete(arr);
        }
        f << time_span.count() / 100 << std::endl;
    }
    return 0;
}
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image1.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image2.png)

k = 1.3, в среднем алгоритм поиска перебором для случайного числа работает быстрее, чем в предыдущем случае, сложность алгоритма по-прежнему можно ограничить O(N).

Видим, что через точки можно провести 2 прямые: прямая от 0 до 200'000 и прямая от 200'000 до 1'000'000. Для относительно небольших размеров массива алгоритм выполняется дольше, так как высока вероятность того, что случайно сгенерированное число не будет лежать в массиве, поэтому перебор пройдёт по всему массиву, что займёт больше времени. Построив прямую через точки массивов небольших размеров получаем k = 1.8. Для массивов больших размеров видим разброс: вероятность того, что случайное число лежит в массиве большого размера, больше, разброс времени выполнения алгоритма от среднего случая до наихудшего случая увеличивается. Для уменьшения разброса необходимо проводить большее число тестов для массива одного размера.

## Бинарный поиск
1. Напишем алгоритм бинарного поиска ```BinarySearch```

```C++
void BinarySearch(int s, int* arr, int begin, int end) {
    while (end - begin > 1) {
        int m = (begin + end) / 2;
        if (arr[m] < s) {
            begin = m;
        } else {
            end = m;
        }
    }
}
```

---
2. Проанализируем работу алгоритма на упорядоченном масиве натуральных чисел от 1 до n для наихудшего случая

Полный код:
```C++
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


void FillWithOrderedValues(int n, int* arr) {
    for (int i = 1; i <= n; ++i){
        arr[i] = i;
    }
}


void BinarySearch(int s, int* arr, int begin, int end) {
    while (end - begin > 1) {
        int m = (begin + end) / 2;
        if (arr[m] < s) {
            begin = m;
        } else {
            end = m;
        }
    }
}


int main() {
    std::ofstream f("1.csv", std::ios::out);
    f << 0 << std::endl; // np считает первый элемент столбца его заголовком
    for (unsigned size = 800000; size <= 1'000'000; size += 1000) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now());
        for (unsigned test = 1; test <= 1000; ++test) {
            srand(time(NULL));

            int s = 100000000; // number to search
            int* arr = new int[size];

            FillWithOrderedValues(size, arr);

            auto begin = std::chrono::steady_clock::now();
            BinarySearch(s, arr, 0, size - 1);
            auto end = std::chrono::steady_clock::now();

            time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            delete(arr);
        }
        f << time_span.count() / 1000 << std::endl;
    }
    return 0;
}
```
