![header](https://capsule-render.vercel.app/api?type=waving&color=gradient&height=256&section=header&text=Лабораторная%20работа%20№2&fontSize=60&animation=fadeIn&fontAlignY=38&desc=Сортировки&descAlignY=60&descAlign=70&descSize=30)

## Цель:
проверить прямыми измерениями времени асимптотическую сложность алгоритмов по времени в зависимости от объёма данных.

В работе исследуются 3 медленных и 3 быстрых сортировки. Для каждого алгоритма строим графики зависимости времени его работы от размера массива для обратноупорядоченного массива натуральных чисел $a_n = a_{n-1} - 1$ (массив, который необходимо отсортировать полностью == НАИХУДШИЙ СЛУЧАЙ), случайного массива (СРЕДНИЙ СЛУЧАЙ) и для упорядоченного массива (массив сортировать не нужно == НАИЛУЧШИЙ СЛУЧАЙ). Для наихудших случаев исследуем время работы некоторых алгоритмов, используя флаги оптимизации. В конце исследуем время работы 6 алгоритмов на маленьких массивах.

## Пузырёк и его товарищи (Stupid)

### BubbleSort
Напишем алгоритм сортировки пузырьком ```BubbleSort```. Массивы от 10 до 10'000 с шагом 10. 10 тестов на массив.

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
  for (int i = 1; i < n; ++i) {
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

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Bubble.png)

Линеаризируем графики
$$t = C \cdot N^k$$

$$\ln{t} = \ln{C} + k \cdot \ln{N}$$

![сравнение линеаризованных](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Bubble-L.png)

$$C \approx 2.4\ \text{нс}$$

$$k \approx 2$$

Сложность алгоритма действительно $O(N^2)$.

Оптимизация

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Bubble-O.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Bubble-L.png)

---
### ShakerSort
Напишем алгоритм сортировки перемешиванием ```ShakerSort```. Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

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

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Shaker.png)

Линеаризируем графики
$$t = C \cdot N^k$$

$$\ln{t} = \ln{C} + k \cdot \ln{N}$$

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Shaker-L.png)

$$C \approx 2.0\ \text{нс}$$

$$k \approx 2$$

Сложность алгоритма действительно $O(N^2)$.

Оптимизируем алгоритм ```ShakerSort```: он передвигает большие числа вправо, а меньшие влево, создавая в начале и в конце массива упорядоченные подпоследовательности, которые нет смысла рассматривать при каждом проходе алгоритма. Напишем новый алгоритм сортировки перемешиванием ```SmartShakerSort```. Массивы от 10 до 1'000 с шагом 10. 10 тестов на массив.

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

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/SmartShaker.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/SmartShaker-L.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/SmartShaker-O.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/SmartShaker-O-L.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Shaker-vs.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Shaker-vs-L.png)

---
### InsertionSort
Напишем алгоритм сортировки вставками ```InsertionSort```. Массивы от 10 до 10'000' с шагом 10. 10 тестов на массив.

```C++
void InsertionSort(int n, int* arr) {
  int j;
  int key;
  for (int i = 1; i < n; ++i) {
    j = i - 1;
    key = arr[i];
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Insertion.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Insertion-L.png)

---
## Быстрые сортировки

### MergeSort

"Напишем" алгоритм сортировки перемешиванием ```MergeSort```. Массивы от 1000 до 10'000'000 с шагом 1000. 10 тестов на массив.

```C++
void merge(int* array, int left, int mid, int right) {
  auto subArrayOne = mid - left + 1;
  auto subArrayTwo = right - mid;

  auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = array[mid + 1 + j];

  auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
  int indexOfMergedArray = left;

  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    }
    else {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }

  while (indexOfSubArrayOne < subArrayOne) {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }

  while (indexOfSubArrayTwo < subArrayTwo) {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
  delete[] leftArray;
  delete[] rightArray;
}
  
void MergeSort(int* array, int begin, int end) {
  if (begin >= end) {
    return;
  }
  
  auto mid = begin + (end - begin) / 2;
  MergeSort(array, begin, mid);
  MergeSort(array, mid + 1, end);
  merge(array, begin, mid, end);
}
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Merge.png)

Линеаризируем графики

$$\frac{t}{n \ln{n}} = C$$

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/Merge-L.png)

Видим, что с какого-то момента точки дейтсвительно принимают постоянное значение.

---
### QuickSort

НАПИШЕМ алгоритм сортировки перемешиванием ```MergeSort```. Массивы от 10 до 10'000 с шагом 10. 10 тестов на массив.

```С++
int partition(int* array, int left, int right) {
  median(array, left, right); //или ниже
  //std::swap(array[(left + right)/2], array[right]); //средний элемент - опорный
  int wall = left;
 
  for (int i = left; i < right; ++i) {
    if (array[i] < array[right]) {
      std::swap(array[i], array[wall]);
      ++wall;
    }
  }
  std::swap(array[wall], array[right]);
  return wall;
}


void QuickSort(int* array, int left, int right) {
  if (left < right) {
    int pivot = partition(array, left, right);
    QuickSort(array, left, pivot - 1);
    QuickSort(array, pivot + 1, right);
  }
}
```

Pivot можно выбирать двумя способами. Первый - случайный элемент. Я выбираю элемент в середине, так как это оптимальное значение для упорядоченного и обратноупорядоченного значений, случайному массиву на это всё равно.

Умные люди доказали, что при разбиении массива на маленькие подмассивы и нахождении медианы их медиан, алгоритм ```QuickSort``` для любого случая будет работать за $N \log{N}$. Напишем вспомогательную функцию нахождения медианы медиан.

```С++
void median(int* array, int left, int right) {
  int subRight;
  int median5;
  int mid;
  if (right - left < 5) {
    MergeSort(array, left, right);
    std::swap(array[(left + right) / 2], array[right]);
  } else {
    for (int i = left; i < right; i += 5) {
      subRight = i + 4;
      if (subRight > right) {
        subRight = right;
      }
      MergeSort(array, i, subRight);
      median5 = (i + subRight) / 2;
      std::swap(array[median5], array[left + (i - left) / 5]);
    }
    MergeSort(array, left, left + (right - left + 1) / 5);
    std::swap(array[(right - left) / 10 + left], array[right]);
  }
}
```

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickM.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickM-L.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickR.png)
![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickR-L.png)

Видим, что алгоритм, использующий медиану медиан работает медленне.
Оказывается, что умные люди не говорили, что он должен работать быстрее, они подразумевали, что так алгоритм всегда будет выполняться за $N \log{N}$.

Также заметим, что обратноупорядоченный массив для этого алгоритма является одним из лучших случаев.

А теперь посмотрим, какое преимущество давало бы использование медианы медиан, если бы на нахождение этой медианы не тратилось много времени. Для этого внутри функции медианы будем засекать время её работы, а затем вычитать это время из времени работы всего алгоритма.

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickRvsM.png)

Учитывая то, что алгоритм с медианой бесполезен, проведём оптимизацию обычного алгоритма

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/QuickR-O.png)


---
### ALL
Зависимости для всех алгоритмов нанесём на один график. Так как из-за алгоритмов с квадратичной асимптотикой, быстрые алгоритмы едва различимы, для них проведём отдельное сравнение.

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/ALL.png)

![](https://github.com/Erykalkin/MIPT_labs/blob/main/lab_2/FAST.png)



[![Typing SVG](https://readme-typing-svg.herokuapp.com?color=%2336BCF7&lines=Спасибо+за+внимание!)](https://git.io/typing-svg)
