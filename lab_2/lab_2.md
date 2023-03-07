![header](https://capsule-render.vercel.app/api?type=waving&color=gradient&height=256&section=header&text=Лабораторная%20работа%20№2&fontSize=60&animation=fadeIn&fontAlignY=38&desc=Сортировки&descAlignY=60&descAlign=70&descSize=30)

## Цель:
проверить прямыми измерениями времени асимптотическую сложность алгоритмов по времени в зависимости от объёма данных.

## Пузырёк и его товарищи

### BubbleSort
Напишем алгоритм сортировки пузырьком ```BubbleSort``` и построим графики зависимости времени его работы от размера массива для обратноупорядоченного массива натуральных чисел $a_n = a_{n-1} - 1$ (массив, который необходимо отсортировать полностью == НАИХУДШИЙ СЛУЧАЙ), случайного массива (СРЕДНИЙ СЛУЧАЙ) и для упорядоченного массива (массив сортировать не нужно == НАИЛУЧШИЙ СЛУЧАЙ). Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

![](https://habrastorage.org/getpro/habr/post_images/187/5a3/929/1875a3929dd14c8ea5ff4ccc3d0db9bd.gif)
Тут немножко оптимизированный вариант, я так не делаю

```C++
void BubbleSort(int n, int* arr) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        arr[j], arr[j+1] = arr[j+1], arr[j];
      }
    }
  }
}
```

Код для измерения времени впоследующем будет почти везде одинаковый:

```C++
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>


void FillWithRandomValues(int n, int* arr) {
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  for (int i = 0; i < n; ++i) {
      arr[i] = rnd() % 1'000'000 + 1;
  }
}


void FillWithBackOrderedValues(int n, int* arr) {
  for (int i = 0; i < n; ++i) {
    arr[i] = n - i;
  }
}


void FillWithOrderedValues(int n, int* arr) {
  for (int i = 1; i <= n; ++i) {
    arr[i] = i;
  }
}


int main() {
  std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::ofstream f("1.csv", std::ios::out);
  f << 0 << std::endl;

  int* arr = new int[1000000];
	int arrr[1000000];
  FillWithBackOrderedValues(1000000, arr);    //Наихудший случай
  //FillWithRandomValues(1000000, arr);    //Средний случай
  //FillWithOrderedValues(1000000, arr);    //Наилучший случай

  int size_step = 1000;  // шаг размера массива
  int tests_number = 1000000  // число тестов
  
  for (int size = size_step; size <= 1000000; size += size_step) {
    long double time_span = 0.0;
    for (int test = 1; test <= tests_number; ++test) {
			std::copy_n(arr, 1000000, arrr);

      auto begin = std::chrono::steady_clock::now();
      //function
      auto end = std::chrono::steady_clock::now();

      time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    }
    f << time_span / tests_number << std::endl;
  }
}
```

![худший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image1.png)
![средний](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image2.png)
![лучший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image3.png)

Линеаризируем графики
$$t = C \cdot N^k$$

$$\ln{t} = \ln{C} + k \cdot \ln{N}$$

![сравнение линеаризованных](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image4.png)

$$C \approx 2.4\ \text{нс}$$

$$k \approx 2$$

Сложность алгоритма действительно $O(N^2)$. Сложность также не зависит от наполнения массива.

---
### ShakerSort
Напишем алгоритм сортировки перемешиванием ```ShakerSort``` и построим графики зависимости времени его работы от размера массива для обратноупорядоченного массива натуральных чисел $a_n = a_{n-1} - 1$ (массив, который необходимо отсортировать полностью == НАИХУДШИЙ СЛУЧАЙ), случайного массива (СРЕДНИЙ СЛУЧАЙ) и для упорядоченного массива (массив сортировать не нужно == НАИЛУЧШИЙ СЛУЧАЙ). Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

![](https://habrastorage.org/getpro/habr/post_images/2a9/ad7/855/2a9ad78556f13396ebc68cb4ac21e91c.gif)
Эта картинка скорее про оптимизированный вариант сортировки перемешиванием :)

```C++
void ShakerSort(int n, int* arr) {
  for (int i = 0; i < n - 1; ++i) {
    if (i % 2 == 0) {
      for (int j = 0; j < n - 1; ++j) {
        if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j+1]);
        }
      }
    } else {
      for (int j = n - 1; j > 1; --j) {
        if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j+1]);
        }
      }
    }
  }
}
```

![худший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image5.png)
![средний](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image6.png)
![лучший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image7.png)

Линеаризируем графики
$$t = C \cdot N^k$$

$$\ln{t} = \ln{C} + k \cdot \ln{N}$$

![сравнение линеаризованных](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image8.png)

$$C \approx 2.0\ \text{нс}$$

$$k \approx 2$$

Сложность алгоритма действительно $O(N^2)$. Сложность также не зависит от наполнения массива.


---
## Пузырек, но быстрее

В этом пункте при компиляции будем добавлять флаги -O0, -O1, -O2 и -O3. Оптимизацию будем использовать на алгоритме ```BubbleSort```. Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив. Не забываем, что для этой сортировки не существует худшего и лучшего случая.

Построим линеаризированные графики зависимости времени работы алгоритма от размера массива
$$t = C \cdot N^k$$

$$\ln{t} = \ln{C} + k \cdot \ln{N}$$

![все](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image9.png)

Видим, что флаги -O1, -O2 и -O3 одинаково ускоряют работу программы в 3.8 раз В ДАННОМ СЛУЧАЕ. Флаг -O0 означает отсутствие оптимизации.


---
## Быстрые сортировки

### SmartShakerSort

Оптимизируем алгоритм ```ShakerSort```: он передвигает большие числа вправо, а меньшие влево, создавая в начале и в конце массива упорядоченные подпоследовательности, которые нет смысла рассматривать при каждом проходе алгоритма. Напишем новый алгоритм сортировки перемешиванием ```SmartShakerSort``` и построим графики зависимости времени его работы от размера массива для 3 случаев. Предполагаю, что сложность полученного алгоритма в худшем случае $O(N \ln N)$. Массивы от 1000 до 1'000'000' с шагом 1000. 10 тестов на массив.

```C++
void SmartShakerSort(int n, int* arr) {
  int control = n - 1;
	int left  = 0;
	int right = n - 1;

  for (int i = 0; i < n - 1; ++i) {

    if (i % 2 == 0) {
      for (int j = left; j < right; ++j) {
        if (arr[j] > arr[j + 1]) {
          std::swap(arr[j], arr[j + 1]);
          control = j;
        }
      }
      right = control;

    } else {
      for (int j = right; j > left; j--) {
        std::cout << j << ' ' << left << '\n';
        if (arr[j] < arr[j - 1]) {
          std::swap(arr[j], arr[j - 1]);
          control = j;
        }
      }
      left = control;
    }
  }
}
```

![худший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image9.png)
![средний](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image10.png)
![лучший](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image11.png)
![сравнение линеаризованных](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image12.png)

---
3. 


[![Typing SVG](https://readme-typing-svg.herokuapp.com?color=%2336BCF7&lines=Спасибо+за+внимание!)](https://git.io/typing-svg)
