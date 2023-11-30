#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <ctime>
#include <chrono>
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

    // Количество элементов в массиве
    int k = 20;                 
    
    // Замер времени для графиков

    //auto begin = std::chrono::steady_clock::now();
    //auto end = std::chrono::steady_clock::now();
    //auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    //std::cout << "The time: " << elapsed_ms.count() << " ms\n";

    
char c;
do
    {
        cout << "\nВыберите сортировку:" << endl
            << "1 - Сортировка выбором" << endl
            << "2 - Сортировка вставками" << endl
            << "3 - Сортировка пузырьком" << endl
            << "4 - Сортировка слиянием" << endl
            << "5 - Быстрая сортировка" << endl
            << "6 - Сортировка Шелла" << endl
            << "7 - Пирамидальная сортировка" << endl
            << "8 - TimSort" << endl
            << "9 - IntroSort" << endl;
        int number;
        
        do
        {
            cin >> number;
            switch (number)
            {
                case 1:
                {
                    int arr1[k];
                    for (int i = 0; i < k; i++){ 
                        arr1[i] = 1 + rand() % 100;
                    }

                    int n1 = sizeof(arr1) / sizeof(arr1[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n1; i++) {
                        std::cout << arr1[i] << " ";
                    }
                    
                    selectionSort(arr1, n1);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n1; i++) {
                        std::cout << arr1[i] << " ";
                    }

                    break;
                }

                case 2:
                {
                    int arr2[k];
                    for (int i = 0; i < k; i++){ 
                        arr2[i] = 1 + rand() % 100;
                    }

                    int n2 = sizeof(arr2) / sizeof(arr2[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n2; i++) {
                        std::cout << arr2[i] << " ";
                    }
                    
                    insertionSort(arr2, n2);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n2; i++) {
                        std::cout << arr2[i] << " ";
                    }
                    break;
                }

                case 3:
                {
                    int arr3[k];
                    for (int i = 0; i < k; i++){ 
                        arr3[i] = 1 + rand() % 100;
                    }

                    int n3 = sizeof(arr3) / sizeof(arr3[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n3; i++) {
                        std::cout << arr3[i] << " ";
                    }
                    
                    bubbleSort(arr3, n3);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n3; i++) {
                        std::cout << arr3[i] << " ";
                    }
                    break;
                }

                case 4:
                {
                    int arr4[k];
                    for (int i = 0; i < k; i++){ 
                        arr4[i] = 1 + rand() % 100;
                    }

                    int n4 = sizeof(arr4) / sizeof(arr4[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n4; i++) {
                        std::cout << arr4[i] << " ";
                    }
                    
                    mergeSort(arr4, 0, n4 - 1);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n4; i++) {
                        std::cout << arr4[i] << " ";
                    }
                    break;
                }

                case 5:
                {
                    int arr5[k];
                    for (int i = 0; i < k; i++){ 
                        arr5[i] = 1 + rand() % 100;
                    }

                    int n5 = sizeof(arr5) / sizeof(arr5[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n5; i++) {
                        std::cout << arr5[i] << " ";
                    }
                    
                    quickSort(arr5, 0, n5 - 1);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n5; i++) {
                        std::cout << arr5[i] << " ";
                    }
                    break;
                }

                case 6:
                {
                    int arr6[k];
                    for (int i = 0; i < k; i++){ 
                        arr6[i] = 1 + rand() % 100;
                    }

                    int n6 = sizeof(arr6) / sizeof(arr6[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n6; i++) {
                        std::cout << arr6[i] << " ";
                    }
                    
                    shellSort(arr6, n6, intervals1, length1);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n6; i++) {
                        std::cout << arr6[i] << " ";
                    }              
                    break;
                }

                case 7:
                {
                    int arr7[k];
                    for (int i = 0; i < k; i++){ 
                        arr7[i] = 1 + rand() % 100;
                    }

                    int n7 = sizeof(arr7) / sizeof(arr7[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n7; i++) {
                        std::cout << arr7[i] << " ";
                    }
                    
                    heapSort(arr7, n7);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n7; i++) {
                        std::cout << arr7[i] << " ";
                    }
                    break;
                }

                case 8:
                {
                    int arr8[k];
                    for (int i = 0; i < k; i++){ 
                        arr8[i] = 1 + rand() % 100;
                    }

                    int n8 = sizeof(arr8) / sizeof(arr8[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n8; i++) {
                        std::cout << arr8[i] << " ";
                    }
                    
                    timSort(arr8, n8);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n8; i++) {
                        std::cout << arr8[i] << " ";
                    }
                    break;
                }

                case 9:
                {
                    int arr9[k];
                    for (int i = 0; i < k; i++){ 
                        arr9[i] = 1 + rand() % 100;
                    }

                    int n9 = sizeof(arr9) / sizeof(arr9[0]);

                    std::cout << "\nИсходный массив: ";
                    for (int i = 0; i < n9; i++) {
                        std::cout << arr9[i] << " ";
                    }
                    
                    introsort(arr9, n9);

                    std::cout << "\nОтсортированный массив: ";
                    for (int i = 0; i < n9; i++) {
                        std::cout << arr9[i] << " ";
                    }
                    break;
                }
                default:
                    cout << "Такого пункта нет. \n> ";
                    break;
            }

        } while (number < 1 || number > 9);

        
        cout << "\nПродолжить работу? y/n -->";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    system("pause");
    
    return 0;
};