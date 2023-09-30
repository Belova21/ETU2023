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

// ����� ������ ������� �������� ������� ������������ 

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
        cout << "������ �������� � ������ �� ����������." << endl;
        return 0;
    }
    
    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current -> pNext;
    }

    cout << "������� �� �������" << index << ": " << current -> data << endl;
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
        cout << "�������� � ����� �������� �� ����������." << endl;
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
        cout << "� ������ " << Size << " ���������." << endl;
    }
    else
    {
        cout << "������ ����." << endl;
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

    
    cout << "������� ���������� ��������� � ������: " << endl;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        lst.push_back(rand() % 10);
    }

    cout << "��������� ������: " << endl;
    lst.printList();

    do
    {
        cout << "\n�������� ��������:" << endl
            << "1 - ���������� � ����� ������" << endl
            << "2 - ���������� � ������ ������" << endl
            << "3 - �������� ���������� ��������" << endl
            << "4 - �������� ������� ��������" << endl
            << "5 - ���������� �������� �� �������" << endl
            << "6 - ��������� �������� �� �������" << endl
            << "7 - �������� �������� �� �������" << endl
            << "8 - ��������� ������� ������" << endl
            << "9 - �������� ���� ��������� ������" << endl
            << "10 - ������ �������� �� ������� �� ������������ �������" << endl
            << "11 - �������� �� ������� ������" << endl
            << "12 - ������ ������� ��������� � ������ �� ��������" << endl
            << "13 - ������� ������� ������ � ������, ������� � �������" << endl
            << "14 - ������� ������� ������ � �����" << endl
            << "15 - ������� ������� ������ � ������" << endl
            << "16 - �������� �� ���������� ������� ������ � ������" << endl
            << "17 - ����� ������� ��������� ������� ������ � ������" << endl
            << "18 - ����� ���������� ��������� ������ �� ��������" << endl
            << "19 - ����� ���� ��������� ������ �� ��������" << endl;
        int number;
        do
        {
            cin >> number;
            switch (number)
            {
                case 1:
                {
                    cout << "������� �������� ��������: ";
                    cin >> a;
                    lst.push_back(a);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 2:
                {
                    cout << "������� �������� ��������: ";
                    cin >> a;
                    lst.push_front(a);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 3:
                {
                    lst.pop_back();
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 4:
                {
                    lst.pop_front();
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 5:
                {
                    cout << "������� �������� ��������: ";
                    cin >> a;
                    cout << "������� ������: ";
                    cin >> index;
                    lst.insert(a, index);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 6:
                {
                    cout << "������� ������: ";
                    cin >> index;
                    cout << lst.printElementAt(index) << endl;                    
                    break;
                }

                case 7:
                {
                    cout << "������� ������: ";
                    cin >> index;
                    lst.removeAt(index);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 8:
                {
                    cout << "����� ������: " << lst.getSize() << endl;
                    break;
                }

                case 9:
                {
                    lst.clear();
                    break;
                }

                case 10:
                {
                    cout << "������� �������� ��������: ";
                    cin >> a;
                    cout << "������� ������: ";
                    cin >> index;
                    lst.replace(index, a);
                    cout << "���������� ������: " << endl;
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
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 13:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();

                    cout << "������� ������: ";
                    cin >> index;
                    lst.insertListFromIndex(&lst2, index);

                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 14:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();

                    lst.insertListToEnd(&lst2);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 15:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();

                    lst.insertListToBegining(&lst2);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }

                case 16:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();
                    
                    if (lst.isListIn(&lst2))
                    {
                        cout << "����������� ������ ���������� � ��������." << endl;
                    }
                    else
                    {
                        cout << "���������� ���." << endl;
                    }
                    break;
                }

                case 17:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();

                    cout << "������ ������� ���������: " << lst.findFirstIn(&lst2) << endl;

                    break;
                }

                case 18:
                {
                    cout << "���������� ��������� ��� ������ ������: ";
                    cin >> n;
                    
                    for (int i = 0; i < n; i++)
                    {
                        lst2.push_back(rand() % 10);
                    }

                    cout << "����������� ������:" << endl;
                    lst2.printList();

                    cout << "������ ���������� ���������: " << lst.findLastIn(&lst2) << endl;

                    break;
                }

                case 19:
                {
                    cout << "������� ������ ������ > ";
                    cin >> index;
                    cout << "������� ������ ������ > ";
                    cin >> a;

                    lst.swap(index, a);
                    cout << "���������� ������: " << endl;
                    lst.printList();
                    break;
                }
                default:
                    cout << "������ ������ ���. \n> ";
                    break;
            }

        } while (number < 1 || number > 19);

        
        cout << "���������� ������? y/n -->";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    system("pause");
    
    return 0;
};