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

    selectionSort(arr, n);

    std::cout << "\nОтсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
};