#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include <chrono>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void breadthFirst(Node* root) {
    if (root == nullptr)
        return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        std::cout << node->key << " ";
        q.pop();

        if (node->left != nullptr)
            q.push(node->left);

        if (node->right != nullptr)
            q.push(node->right);
    }
}

void preOrder(Node* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->key << " ";
    }
}

void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        std::cout << root->key << " ";
        inOrder(root->right);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* root = nullptr;
    
    std::srand(std::time(nullptr)); 

    int numElements = 10; 

    for (int i = 0; i < numElements; i++) {
        int randomNumber = std::rand() % 100;
        root = insert(root, randomNumber); 
    }

char c;
do
    {
        std::cout << "\nВыберите сортировку:" << std::endl
            << "1 - Обход в ширину" << std::endl
            << "2 - Прямой обход" << std::endl
            << "3 - Обратный обход" << std::endl
            << "4 - Симметричный обход" << std::endl
            << "5 - Высота дерева" << std::endl;
        int number;
        
        do
        {
            std::cin >> number;
            switch (number)
            {
                case 1:
                {
                    std::cout << "Обход в ширину: ";
                    breadthFirst(root);
                    std::cout << "\n";
                    break;
                }

                case 2:
                {
                    std::cout << "Прямой обход: ";
                    preOrder(root);
                    std::cout << "\n";
                    break;
                }

                case 3:
                {
                    std::cout << "Обратный обход: ";
                    postOrder(root);
                    std::cout << "\n";
                    break;
                }

                case 4:
                {
                    std::cout << "Симметричный обход: ";
                    inOrder(root);
                    std::cout << "\n";
                    break;
                }

                case 5:
                {
                    std::cout << "Высота дерева: ";
                    std::cout << height(root);
                    std::cout << "\n";
                    break;
                }
            default:
                std::cout << "Такого пункта нет. \n> ";
                break;
            }
        } while (number < 1 || number > 5);
        
        std::cout << "\nПродолжить работу? y/n -->";
        std::cin >> c;
    } while (c == 'y' || c == 'Y');

    system("pause");
    
    return 0;
}

