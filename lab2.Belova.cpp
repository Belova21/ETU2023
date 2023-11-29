#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <ctime>
using namespace std;

void selectionSort(int arr[], int n) {                          // Сортировка выбором
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

void insertionSort(int arr[], int n) {                          // Сортировка вставками
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

void bubbleSort(int arr[], int n) {                             // Сортировка пузырьком
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(int arr[], int left, int mid, int right) {           // Объединение отсортированных подмассивов
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {                // Сортировка слиянием
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int low, int high) {                   // Функция разделения
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

void quickSort(int arr[], int low, int high) {                  // Быстрая сортировка
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void shellSort(int arr[], int n, int intervals[], int length) { // Сортировка Шелла
    for (int k = 0; k < length; k++) {
        int interval = intervals[k];

        for (int i = interval; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= interval && arr[j - interval] > temp) {
                arr[j] = arr[j - interval];
                j -= interval;
            }
            arr[j] = temp;
        }
    }
}


void buildHeap(int arr[], int n, int i) {                       // Пирамида на основе массива
    int largest = i;         
    int leftChild = 2 * i + 1;     
    int rightChild = 2 * i + 2;    

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        buildHeap(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {                               // Пирамидальная сортировка
    for (int i = n / 2 - 1; i >= 0; i--)
        buildHeap(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);   
        buildHeap(arr, i, 0);
    }
}

const int RUN = 32;

void insertionSort2(int arr[], int left, int right) {           // Сортировка вставками для Timsort
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
 
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
 
        arr[j + 1] = key;
    }
}

void timSort(int arr[], int n) {                                // Timsort
    for (int i = 0; i < n; i += RUN)
        insertionSort2(arr, i, std::min((i + RUN - 1), (n - 1)));
 
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
 
            merge(arr, left, mid, right);
        }
    }
}

const int INSERTION_SORT_THRESHOLD = 16;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < n && arr[left] > arr[largest])
        largest = left;
 
    if (right < n && arr[right] > arr[largest])
        largest = right;
 
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
 
void heapSort2(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
void introsortUtil(int arr[], int left, int right, int depthLimit) {
    if (right - left <= INSERTION_SORT_THRESHOLD) {
        insertionSort2(arr, left, right);
        return;
    }
 
    if (depthLimit == 0) {
        heapSort2(arr, right - left + 1);
        return;
    }
 
    int pivot = partition(arr, left, right);
    introsortUtil(arr, left, pivot - 1, depthLimit - 1);
    introsortUtil(arr, pivot + 1, right, depthLimit - 1);
}
 
void introsort(int arr[], int n) {
    int depthLimit = 2 * log2(n);
    introsortUtil(arr, 0, n - 1, depthLimit);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Последовательности интервалов для сортировки Шелла
    int intervals1[] = {5, 3, 1};
    int length1 = sizeof(intervals1) / sizeof(intervals1[0]);

    int intervals2[] = {8, 4, 2, 1};
    int length2 = sizeof(intervals2) / sizeof(intervals2[0]);

    int intervals3[] = {2, 1};
    int length3 = sizeof(intervals3) / sizeof(intervals3[0]);

    // Заполнение массива
    srand(time(0));

    int k = 10;
    //std::cout << "Введите количество элементов в исходном массиве:";
    //std::cin >> k;

    int arr[k];                       
    for (int i = 0; i < 10; i++)
        arr[i] = 1 + rand() % 100;
    


    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "\nИсходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    clock_t t0{}, t1{};

    t0 = clock();

// отсортировать 
    selectionSort(arr, n);

    t1 = clock();

   
    double b = (t1 - t0) / CLOCKS_PER_SEC;
    std::cout << b;

    std::cout << "Hello";
    
    //selectionSort(arr, n);
    //bubbleSort(arr, n);
    //insertionSort(arr, n);
    //quickSort(arr, 0, n - 1);
    //mergeSort(arr, 0, n - 1);
    //shellSort(arr, n, intervals1, length1); 
    //shellSort(arr, n, intervals2, length2);
    //shellSort(arr, n, intervals3, length3);
    //heapSort(arr, n);
    //timSort(arr, n);
    //introsort(arr, n);

    std::cout << "\nОтсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
};