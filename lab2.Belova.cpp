#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void selectionSort(int arr[], int n) {          // Сортировка выбором
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

void insertionSort(int arr[], int n) {             // Сортировка вставками
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {             // Сортировка пузырьком
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partition(int arr[], int low, int high) {           // Функция разделения
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high) {          // Быстрая сортировка
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int k = 10;
    //std::cout << "Введите количество элементов в исходном массиве:";
    //std::cin >> k;


    int arr[k];
    for (int i = 0; i < 10; i++)
        arr[i] = 1 + rand() % 100;
    
    for (int i = 0; i < 10; i++)
        cout << arr[i] << " ";


    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "\nИсходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    //selectionSort(arr, n);
    //bubbleSort(arr, n);
    //insertionSort(arr, n);
    //quickSort(arr, 0, n - 1);

    std::cout << "\nОтсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
};