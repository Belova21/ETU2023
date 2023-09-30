#include <iostream>
#include <string>
using namespace std;


template<typename T>
class List
{
public:
    List();
    ~List();

    void push_back(T data);          //1
    void push_front(T data);         //2
    void pop_back();                 //3
    void pop_front();                //4
    void insert(T data, int index);  //5
    int printElementAt(int index);   //6
    void removeAt(int index);        //7
    int getSize() {return Size;}     //8
    void clear();                    //9
    void replace(int index, T data); //10
    void isEmpty();                  //11
    void reverse();                  //12
    void insertListFromIndex(List* SecList, int index); // 13
    void insertListToEnd(List* SecList);                // 14
    void insertListToBegining(List *SecList);           // 15
    bool isListIn(List *SecList);    // 16
    int findFirstIn(List *SecList);  // 17
    int findLastIn(List *SecList);   // 18
    void swap(int index1, int index2);                  // 19

    void printList();

private:

    template<typename T1>
    class Node
    {
    public: 
        Node *pNext; 
        Node *pPrev;
        T data;      
        Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr)
        {
            this -> data = data;
            this -> pNext = pNext;
            this -> pPrev = pPrev;
        }
    };
    int Size;       

    Node<T> *head; 
    Node<T> *tail;  
};


template<typename T>
List<T>::List()    
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List()  
{
    clear();
}

// Далее список функций согласно порядку лабораторной 

template<typename T>
void List<T>::push_back(T data) 
{
    if (tail == nullptr)
    {
        head = new Node<T>(data);
        tail = head;
    }
    else
    {
        Node<T> *newNode = new Node<T>(data, nullptr, tail);
        tail -> pNext = newNode;
        tail = newNode;
    }

    Size++;
}

template <typename T>
void List<T>::push_front(T data)
{
    if (head == nullptr)
    {
        head = new Node<T>(data);
        tail = head;
    }
    else
    {
        Node<T> *newNode = new Node<T>(data, head, nullptr);
        head -> pPrev = newNode;
        head = newNode;
    }

    Size++;
}

template <typename T>
void List<T>::pop_back()
{
    if (Size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        Size = 0;
        return;
    }

    Node<T> *temp = tail;

    tail = tail -> pPrev;
    tail -> pNext = nullptr;

    delete temp;
    Size--;
}

template <typename T>
void List<T>::pop_front()
{
    if (Size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        Size = 0;
        return;
    }

    Node<T> *temp = head;

    head = head -> pNext;
    head -> pPrev = nullptr;

    delete temp;
    Size--;
}

template <typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else if (index == Size)
    {
        push_back(data);
    }
    else
    {
        Node<T> *current = this -> head;
        for (int i = 0; i < index; i++)
        {
            current = current -> pNext;
        }

        Node<T> *newNode = new Node<T>(data, current, current -> pPrev);

        current-> pPrev -> pNext = newNode;
        current -> pPrev = newNode;

        Size++;
    }
}

template<typename T>
int List<T>::printElementAt(int index)
{
    if (index < 0 || index >= Size)
    {
        cout << "Такого элемента в списке не существует." << endl;
        return 0;
    }
    
    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current -> pNext;
    }

    cout << "Элемент по индексу" << index << ": " << current -> data << endl;
    return 0;
}

template <typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else if (index == Size - 1)
    {
        pop_back();
    }
    else
    {
        Node<T> *current = this -> head;
        for (int i = 0; i < index; i++)
        {
            current = current -> pNext;
        }

        Node<T> *toDelete = current;

        current -> pPrev -> pNext = current -> pNext;
        current -> pNext -> pPrev = current -> pPrev;

        delete toDelete;
        Size--;
    }
}

template <typename T>
void List<T>::clear()
{
    while (Size)
    {
        pop_front();
    }
}

template<typename T>
void List<T>::replace(int index, T data)
{
    if (index < 0 || index >= Size)
    {
        cout << "Элемента с таким индексом не существует." << endl;
        return;
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current -> pNext;
    }

    current -> data = data;
}

template<typename T>
void List<T>::isEmpty()
{
    if (Size != 0)
    {
        cout << "В списке " << Size << " элементов." << endl;
    }
    else
    {
        cout << "Список пуст." << endl;
    }
}

template<typename T>
void List<T>::reverse()
{
    if (Size <= 1)
    {
        return;
    }

    Node<T> *current = head;
    Node<T> *temp = nullptr;

    while (current != nullptr)
    {
        temp = current -> pNext;
        current -> pNext = current -> pPrev;
        current -> pPrev = temp;
        current = temp;
    }

    temp = head;
    head = tail;
    tail = temp;
}

template<typename T>
void List<T>::insertListFromIndex(List* SecList, int index)
{
    Node<T> *current = this -> head;

    for (int i = 0; i < index - 1; i++)
    {
        current = current -> pNext;
    }

    Node<T> *temp = current -> pNext;
    current -> pNext = SecList -> head;
    SecList -> head -> pPrev = current;

    Node<T> *lastNodeOfSecList = SecList->head;

    while (lastNodeOfSecList -> pNext)
    {
        lastNodeOfSecList -> pNext -> pPrev = lastNodeOfSecList; 
        lastNodeOfSecList = lastNodeOfSecList -> pNext;
    }

    lastNodeOfSecList -> pNext = temp;

    if (temp != nullptr)
    {
        temp -> pPrev = lastNodeOfSecList;
    }

    Size += SecList -> getSize();
}

template<typename T>
void List<T>::insertListToEnd(List* SecList)
{
    Node<T> *current = this -> tail;
    Node<T> *lastNodeOfSecList = SecList -> head;

    if (current != nullptr) 
    {
        current -> pNext = lastNodeOfSecList;
        lastNodeOfSecList -> pPrev = current;
    }
    else 
    {
        this -> head = lastNodeOfSecList;
    }

    this -> tail = SecList -> tail; 

    Size += SecList -> getSize();
}

template<typename T>
void List<T>::insertListToBegining(List* SecList)
{
    Node<T> *firstNodeOfSecList = SecList -> head;
    Node<T> *lastNodeOfSecList = SecList -> tail;

    if (this -> head != nullptr) 
    {
        this -> head -> pPrev = lastNodeOfSecList;
        lastNodeOfSecList -> pNext = this -> head;
    }
    
    this -> head = firstNodeOfSecList;
    Size += SecList -> getSize();
}

template<typename T>
bool List<T>::isListIn(List* SecList)
{
    if (Size < SecList -> getSize()) {
        return false;
    }

    Node<T> *base = this -> head;
    Node<T> *current = this -> head;
    Node<T> *cmpr = SecList -> head;

    do {
        if (current -> data == cmpr -> data) {
            current = current -> pNext;
            cmpr = cmpr -> pNext;
        }
        else {
            cmpr = SecList -> head;
            current = base -> pNext;
            base = base -> pNext;
        }
    } while (cmpr && current);
    
    return (cmpr == nullptr);
}

template<typename T>
int List<T>::findFirstIn(List* SecList)
{
    if (Size < SecList -> getSize()) {return -1;}

    Node<T> *base = this -> head;
    Node<T> *current = this -> head;
    Node<T> *cmpr = SecList -> head;
    int index = 0;

    do
    {
        if (current -> data == cmpr -> data)
        {
            current = current -> pNext;
            cmpr = cmpr -> pNext;
        }
        else
        {
            cmpr = SecList -> head;
            current = base -> pNext;
            base = base -> pNext;
            index++;
        }
    } while (cmpr && current);

    if (!cmpr)
    {
        return index;
    }
    else
    {
        return -1;
    }
}

template<typename T>
int List<T>::findLastIn(List* SecList)
{
    if (Size < SecList -> getSize()) { return 0; }

    Node<T> *base = this -> head;
    Node<T> *current = this -> head;
    Node<T> *cmpr = SecList -> head;
    int index = 0;
    int buf = -1;
        
    do
    {       
        if (!cmpr)
        {
            buf = index;
            cmpr = SecList -> head;
            current = base -> pNext;
            base = base -> pNext;
            index++;
        }
        else if (current -> data == cmpr -> data)
        {
            current = current -> pNext;
            cmpr = cmpr -> pNext;
        }
        else
        {
            cmpr = SecList -> head;
            current = base -> pNext;
            base = base -> pNext;
            index++;
        }   
    } while (current);

    return buf;
}

template<typename T>
void List<T>::swap(int index1, int index2) {
    if (index1 == index2) {
        return; 
    }
    
    if (index1 > index2) {
        swap(index2, index1);
        return; 
    }
    
    Node<T> *node1 = head;
    Node<T> *node2 = head;
    
    for (int i = 0; i < index1; i++) {
        node1 = node1 -> pNext;
    }
    
    for (int i = 0; i < index2; i++) {
        node2 = node2 -> pNext;
    }
    
    T temp = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = temp;

    return;
}

template<typename T>
void List<T>::printList()
{
    Node<T> *current = this -> head;
    while (current != nullptr)
    {
        cout << current -> data << " ";
        current = current -> pNext;
    }
    cout << endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    char c;
    int a;
    int index;
    List<int> lst;
    List<int> lst2;

    
    cout << "Введите количество элементов в списке: " << endl;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        lst.push_back(rand() % 10);
    }

    cout << "Созданный список: " << endl;
    lst.printList();

    do
    {
        cout << "\nВыберите действие:" << endl
            << "1 - Добавление в конец списка" << endl
            << "2 - Добавление в начало списка" << endl
            << "3 - Удаление последнего элемента" << endl
            << "4 - Удаление первого элемента" << endl
            << "5 - Добавление элемента по индексу" << endl
            << "6 - Получение элемента по индексу" << endl
            << "7 - Удаление элемента по индексу" << endl
            << "8 - Получение размера списка" << endl
            << "9 - Удаление всех элементов списка" << endl
            << "10 - Замена элемента по индексу на передаваемый элемент" << endl
            << "11 - Проверка на пустоту списка" << endl
            << "12 - Замена порядка элементов в списке на обратный" << endl
            << "13 - Вставка другого списка в список, начиная с индекса" << endl
            << "14 - Вставка другого списка в конец" << endl
            << "15 - Вставка другого списка в начало" << endl
            << "16 - Проверка на содержание другого списка в списке" << endl
            << "17 - Поиск первого вхождения другого списка в список" << endl
            << "18 - Поиск последнего вхождения списка по индексам" << endl
            << "19 - Обмен двух элементов списка по индексам" << endl;
        int number;
        do
        {
            cin >> number;
            switch (number)
            {
                case 1:
                {
                    cout << "Введите значение элемента: ";
                    cin >> a;
                    lst.push_back(a);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 2:
                {
                    cout << "Введите значение элемента: ";
                    cin >> a;
                    lst.push_front(a);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 3:
                {
                    lst.pop_back();
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 4:
                {
                    lst.pop_front();
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 5:
                {
                    cout << "Введите значение элемента: ";
                    cin >> a;
                    cout << "Введите индекс: ";
                    cin >> index;
                    lst.insert(a, index);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 6:
                {
                    cout << "Введите индекс: ";
                    cin >> index;
                    cout << lst.printElementAt(index) << endl;                    
                    break;
                }

                case 7:
                {
                    cout << "Введите индекс: ";
                    cin >> index;
                    lst.removeAt(index);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 8:
                {
                    cout << "Длина списка: " << lst.getSize() << endl;
                    break;
                }

                case 9:
                {
                    lst.clear();
                    break;
                }

                case 10:
                {
                    cout << "Введите значение элемента: ";
                    cin >> a;
                    cout << "Введите индекс: ";
                    cin >> index;
                    lst.replace(index, a);
                    cout << "Измененный список: " << endl;
                    lst.printList();

                    break;
                }

                case 11:
                {
                    lst.isEmpty();
                    break;
                }

                case 12:
                {
                    lst.reverse();
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 13:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();

                    cout << "Введите индекс: ";
                    cin >> index;
                    lst.insertListFromIndex(&lst2, index);

                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 14:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();

                    lst.insertListToEnd(&lst2);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 15:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();

                    lst.insertListToBegining(&lst2);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }

                case 16:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();
                    
                    if (lst.isListIn(&lst2))
                    {
                        cout << "Добавленный список содержится в исходном." << endl;
                    }
                    else
                    {
                        cout << "Совпадений нет." << endl;
                    }
                    break;
                }

                case 17:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();

                    cout << "Индекс первого вхождения: " << lst.findFirstIn(&lst2) << endl;

                    break;
                }

                case 18:
                {
                    cout << "Количество элементов для нового списка: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "Добавленный список:" << endl;
                    lst2.printList();

                    cout << "Индекс последнего вхождения: " << lst.findLastIn(&lst2) << endl;

                    break;
                }

                case 19:
                {
                    cout << "Введите первый индекс > ";
                    cin >> index;
                    cout << "Введите второй индекс > ";
                    cin >> a;

                    lst.swap(index, a);
                    cout << "Измененный список: " << endl;
                    lst.printList();
                    break;
                }
                default:
                    cout << "Такого пункта нет. \n> ";
                    break;
            }

        } while (number < 1 || number > 19);

        
        cout << "Продолжить работу? y/n -->";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    system("pause");
    
    return 0;
};