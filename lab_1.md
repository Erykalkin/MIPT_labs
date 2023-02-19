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

\
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

\
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

k = 2 $\Rightarrow$ время работы одной операции примерно равно 2 наносекундам.

![][https://github.com/Erykalkin/MIPT_labs/blob/main/image.png]
