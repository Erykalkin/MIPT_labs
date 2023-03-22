#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>


void print(int n, int* arr) {
  for (int i = 0; i < n; ++i) {
      std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
}


void FillWithRandomValues(int n, int* arr) {
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  for (int i = 0; i < n; ++i) {
      arr[i] = rnd() % 1'000'000 + 1;
  }
}


void Fill10(int n, int* arr) {
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  for (int i = 0; i < n; ++i) {
    arr[i] = std::pow(10, rnd() % 9 + 1);
  }
}


void FillWithBackOrderedValues(int n, int* arr) {
  for (int i = 0; i < n; ++i) {
    arr[i] = n - i;
  }
}


void FillWithOrderedValues(int n, int* arr) {
  for (int i = 0; i < n; ++i) {
    arr[i] = i;
  }
}


void BubbleSort(int n, int* arr) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j+1]);
      }
    }
  }
}


void ShakerSort(int n, int* arr) {
  for (int i = 0; i < n - 1; ++i) {

    if (i % 2 == 0) {
      for (int j = 0; j < n - 1; ++j) {
        if (arr[j] > arr[j + 1]) {
          std::swap(arr[j], arr[j + 1]);
        }
      }

    } else {
      for (int j = n - 1; j > 0; --j) {
        if (arr[j] < arr[j - 1]) {
          std::swap(arr[j], arr[j - 1]);
        }
      }
    }
  }
}


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
        if (arr[j] < arr[j - 1]) {
          std::swap(arr[j], arr[j - 1]);
          control = j;
        }
      }
      left = control;
    }
  }
}


void QShakerSort(int n, int* arr) {
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


int partition(int* array, int left, int right) {
  //median(array, left, right);
  std::swap(array[(left + right)/2], array[right]); //средний элемент - опорный
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


int main() {
  std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  std::ofstream f("5.csv", std::ios::out);
  f << 0 << std::endl;

  int* arr = new int[1000000];
  int arrr[1000000];
  //FillWithBackOrderedValues(1000000, arr);
  FillWithRandomValues(1000000, arr);
  //FillWithOrderedValues(1000000, arr);
  //Fill10(1000000, arr);

  int size_step = 1;
  int tests_number = 100;

  for (int size = size_step; size <= 100; size += size_step) {
    long double time_span = 0.0;
    for (int test = 1; test <= tests_number; ++test) {
      std::copy_n(arr, 1000000, arrr);
      
      auto begin = std::chrono::steady_clock::now();
      //BubbleSort(size, arrr);
      //ShakerSort(size, arrr);
      //SmartShakerSort(size, arrr);
      InsertionSort(size, arrr);
      //QShakerSort(size, arrr);
      //MergeSort(arrr, 0, size-1);
      //QuickSort(arrr, 0, size-1);
      auto end = std::chrono::steady_clock::now();

      time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    }
    f << time_span / tests_number << std::endl;
  }
}