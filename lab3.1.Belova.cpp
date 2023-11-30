#include <iostream>
#include <queue>
#include <ctime>
#include <chrono>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *parent, *left, *right;

    Node(int val) {
        data = val;
        color = RED;
        parent = left = right = nullptr;
    }
};


class RedBlackTree {
private:
    Node *root;

    int getHeight(Node *node) {
        if (node == nullptr)
            return -1;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void rotateLeft(Node *node) {
        Node *child = node->right;
        node->right = child->left;
        
        if (child->left != nullptr)
            child->left->parent = node;
        
        child->parent = node->parent;
        
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        
        child->left = node;
        node->parent = child;
    }

    void rotateRight(Node *node) {
        Node *child = node->left;
        node->left = child->right;
        
        if (child->right != nullptr)
            child->right->parent = node;
        
        child->parent = node->parent;
        
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;
        
        child->right = node;
        node->parent = child;
    }

    void fixInsertion(Node *node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node *uncle = node->parent->parent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node *uncle = node->parent->parent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void fixDeletion(Node *node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }

    node->color = BLACK;
}

    void transplant(Node *dest, Node *src) {
        if (dest->parent == nullptr)
            root = src;
        else if (dest == dest->parent->left)
            dest->parent->left = src;
        else
            dest->parent->right = src;

        if (src != nullptr)
            src->parent = dest->parent;
    }

    Node* findMinimum(Node *node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    
    void inorderTraversal(Node *node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node *node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node *node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }

    void levelOrderTraversal() {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();

            cout << curr->data << " ";
            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    int getHeight() {
        return getHeight(root);
    }

    void insert(int data) {
        Node *newNode = new Node(data);
        Node *current = root;
        Node *parent = nullptr;
        
        while (current != nullptr) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        
        newNode->parent = parent;
        
        if (parent == nullptr)
            root = newNode;
        else if (data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
        
        fixInsertion(newNode);
    }

    void remove(int data) {
        Node *node = root;
        
        while (node != nullptr) {
            if (data == node->data)
                break;
            else if (data < node->data)
                node = node->left;
            else
                node = node->right;
        }
        
        if (node == nullptr)
            return;
        
        Node *toDelete, *child;
        Color originalColor;

        if (node->left == nullptr) {
            toDelete = node;
            child = node->right;
            transplant(node, child);
        } else if (node->right == nullptr) {
            toDelete = node;
            child = node->left;
            transplant(node, child);
        } else {
            Node *min = findMinimum(node->right);
            originalColor = min->color;
            toDelete = min;
            child = min->right;
            
            if (min->parent == node)
                child->parent = min;
            else {
                transplant(min, min->right);
                min->right = node->right;
                min->right->parent = min;
            }
            
            transplant(node, min);
            min->left = node->left;
            min->left->parent = min;
            min->color = node->color;
        }
        
        if (originalColor == BLACK)
            fixDeletion(child);

        delete toDelete;
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    void preorder() {
        preorderTraversal(root);
        cout << endl;
    }

    void postorder() {
        postorderTraversal(root);
        cout << endl;
    }

    void levelOrder() {
        levelOrderTraversal();
        cout << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    
    RedBlackTree rbTree;

    std::srand(std::time(nullptr)); 


    int numElements = 10; 

    for (int i = 0; i < numElements; i++) {
        int randomNumber = std::rand() % 100;
        rbTree.insert(randomNumber); 
    }

    char c;
do
    {
        cout << "\nВыберите сортировку:" << endl
            << "1 - Обход в ширину" << endl
            << "2 - Прямой обход" << endl
            << "3 - Обратный обход" << endl
            << "4 - Симметричный обход" << endl
            << "5 - Высота дерева" << endl;
        int number;
        
        do
        {
            cin >> number;
            switch (number)
            {
                case 1:
                {
                    cout<<"Обход в ширину: ";
                    rbTree.levelOrder();
                    cout<<"\n";
                    break;
                }

                case 2:
                {
                    cout<<"Прямой обход: ";
                    rbTree.preorder();
                    cout<<"\n";
                    break;
                }

                case 3:
                {
                    cout<<"Обратный обход: ";
                    rbTree.postorder();
                    cout<<"\n";
                    break;
                }

                case 4:
                {
                    cout<<"Симметричный обход: ";
                    rbTree.inorder();
                    cout<<"\n";
                    break;
                }

                case 5:
                {
                    cout<<"Высота дерева: ";
                    cout << rbTree.getHeight();
                    cout<<"\n";
                    break;
                }
            default:
                cout << "Такого пункта нет. \n> ";
                break;
            }
        } while (number < 1 || number > 5);
        
        cout << "\nПродолжить работу? y/n -->";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    system("pause");

    return 0;
}