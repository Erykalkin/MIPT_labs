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
2. Проанализируем работу алгоритма на упорядоченном масиве натуральных чисел от 1 до n для наихудшего случая (ищем $+\infty$) и построим график зависимости времени выполнения алгоритма от размера массива

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

    int* arr = new int[1000000];
    FillWithOrderedValues(1000000, arr);
    int s = 100000000;

    for (unsigned size = 100; size <= 1000000; size += 100) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - std::chrono::steady_clock::now());
        for (unsigned test = 1; test <= 100000; ++test) {

            auto begin = std::chrono::steady_clock::now();
            BinarySearch(s, arr, 0, size - 1);
            auto end = std::chrono::steady_clock::now();

            time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        }
        f << time_span.count() / 100000 << std::endl;
    }
    return 0;
}
```

Видим, что время работы алгоритма пропорционально целой части двоичного логарифма от размера массива.

---
3. Проанализируем работу алгоритма на упорядоченном масиве натуральных чисел от 1 до n для наихудшего случая (ищем $-\infty$ или 0) и построим график зависимости времени выполнения алгоритма от размера массива

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image4.png)

Видим, что время работы алгоритма пропорционально целой части двоичного логарифма от размера массива.

В итоге имеем 2 границы, в пределах которых должны лежать точки при работе алгоритма на случайных числах, что можем проверить при поиске константы, например при ```s = 500'000``` имеем

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image5.png)

Видим, что точки до размера массива 500'000 прижаты к нижней границе, так как ```s = 500'000``` для массивов размером меньше 500'000 является $+\infty$, затем точки с некоторой переодичностью находятся в пределах верхней и нижней границ.

---
4. Проанализируем работу алгоритма на упорядоченном масиве натуральных чисел от 1 до n для случайного числа, принадлежащему массиву (число генерируется в каждом тесте) и построим график. C этого момента время задаём ```long double``` (так сказал ментор).

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

    std::ofstream l("2.csv", std::ios::out);
    l << 0 << std::endl;
    std::ofstream h("3.csv", std::ios::out);
    h << 0 << std::endl;
    std::ofstream c("4.csv", std::ios::out);
    c << 0 << std::endl;

    int* arr = new int[1000000];
    FillWithOrderedValues(1000000, arr);
    int s = 500000;

    for (unsigned size = 1000; size <= 1'000'000; size += 1000) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        long double time_span = 0.0;

        long double t_low = 0;
        long double t_high = 0;
        long double t_c = 0;


        for (int test = 1; test <= 100000; ++test) {
            s = rnd() % size + 1; // number to search

            auto begin = std::chrono::steady_clock::now();
            BinarySearch(s, arr, 0, size - 1);
            auto end = std::chrono::steady_clock::now();

            time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

            begin = std::chrono::steady_clock::now();
            BinarySearch(0, arr, 0, size - 1);
            end = std::chrono::steady_clock::now();
            t_high += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

            begin = std::chrono::steady_clock::now();
            BinarySearch(10000000, arr, 0, size - 1);
            end = std::chrono::steady_clock::now();
            t_low += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

            begin = std::chrono::steady_clock::now();
            BinarySearch(20000, arr, 0, size - 1);
            end = std::chrono::steady_clock::now();
            t_c += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        f << time_span / 100000 << std::endl;
        h << t_high / 100000 << std::endl;
        l << t_low / 100000 << std::endl;
        c << t_c / 100000 << std::endl;

    }
    return 0;
}
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_1/image6.png)

Синие точки - случайные числа;

Красные точки - верхняя граница;

Зелёные точки - нижняя граница;

Серые точки - поиск константы.

Видим, что время поиска конкретного числа (серые точки) лежит в определённых границах. Какое бы конкретное число мы не задали, серые точки будут лежать в полученных гранцах. Можем сделать вывод, что среднее время поиска случайного числа также будет лежать в этих границах, однако по какой-то причине среднее время поиска случайных чисел превосходит верхнюю границу. Причиной может быть принцип работы mt19937. Возможно причина другая, не знаю (╯°□°）╯
