# Лабораторная работа №1: Асимптотическая сложность
### Цель:
проверить прямыми измерениями времени асимптотическую сложность алгоритмов по времени в зависимости от объёма данных.

## Пузырёк и его товарищи

1. Напишем алгоритм сортировки пузырьком ```BubbleSort``` и построим графики зависимости времени его работы от размера массива для случайного массива и для обратноупорядоченного массива натуральных чисел $a_n = a_{n-1} - 1$ (массив, который необходимо отсортировать полностью). Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

![](https://habrastorage.org/getpro/habr/post_images/187/5a3/929/1875a3929dd14c8ea5ff4ccc3d0db9bd.gif)

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


int main() {
  std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::ofstream f("1.csv", std::ios::out);
  f << 0 << std::endl;

  int* arr = new int[1000000];
  FillWithRandomValues(1000000, arr);
  //FillWithBackOrderedValues(1000000, arr);

  int size_step = 1000;  // шаг размера массива
  int tests_number = 1000000  // число тестов
  
  for (int size = size_step; size <= 1000000; size += size_step) {
    long double time_span = 0.0;
    for (int test = 1; test <= tests_number; ++test) {

      auto begin = std::chrono::steady_clock::now();
      //function
      auto end = std::chrono::steady_clock::now();

      time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    }
    f << time_span / tests_number << std::endl;
  }
}
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image1.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image2.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image3.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image4.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/image5.png)

Сложность алгоритма действительно $O(N^2)$. Сложность также не зависит от массива.

---
2. Напишем алгоритм сортировки перемешиванием ```ShakerSort``` и построим графики зависимости времени его работы от размера массива для случайного массива и для обратноупорядоченного массива натуральных чисел $a_n = a_{n-1} - 1$ (массив, который необходимо отсортировать полностью). Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

![](https://habrastorage.org/getpro/habr/post_images/2a9/ad7/855/2a9ad78556f13396ebc68cb4ac21e91c.gif)

```C++
void ShakerSort(int n, int* arr) {
  int control = n - 1;
	int left  = 0;
	int right = n - 1;

  while (left < right) {

    for (int i = left; i < right; ++i) {
      if (arr[i] > arr[i + 1]) {
        std::swap(arr[i], arr[i + 1]);
        control = i;
      }
    }
    right = control;

    for (int i = right; i > left; --i) {
      if (arr[i] < arr[i - 1]) {
        std::swap(arr[i], arr[i - 1]);
        control = i;
      }
    }
    left = control;
  }
}
```



P.S.
