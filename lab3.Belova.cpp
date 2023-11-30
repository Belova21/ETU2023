#include<iostream>
#include<queue>
#include <ctime>
#include <chrono>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (leftHeight > rightHeight) {
            return (leftHeight + 1);
        } else {
            return (rightHeight + 1);
        }
    }
}

Node* GetNewNode(int data) {
    Node* newNode = new Node();
    if(!newNode) {
        cout << "Ошибка выделения памяти\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


Node* InsertNode(Node* root, int data) {
    
    if(root == NULL) {
        root = GetNewNode(data);
    }
    
    else if(data > root->data) {
        root->right = InsertNode(root->right,data);
    }
    
    else {
        root->left = InsertNode(root->left,data);
    }
    return root;
}


Node* FindMin(Node* root) {
    while(root->left != NULL) root = root->left;
    return root;
}


Node* DeleteNode(Node *root, int data) {
    if(root == NULL) {
        return root;
    } 
    else if(data < root->data) {
        root->left = DeleteNode(root->left,data);
    }
    else if (data > root->data) {
        root->right = DeleteNode(root->right,data);
    }
    
    else {
        
        if(root->left == NULL && root->right == NULL) { 
            delete root;
            root = NULL;
        }
        
        else if(root->left == NULL) {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL) {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        
        else { 
            Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->right = DeleteNode(root->right,temp->data);
        }
    }
    return root;
}


void LevelOrder(Node* root) {
    if(root == NULL) return;
    queue<Node*> Q;
    Q.push(root);  
    
    while(!Q.empty()) {
        
        Node* current = Q.front();
        cout<<current->data<<" ";
        if(current->left != NULL) Q.push(current->left);
        if(current->right != NULL) Q.push(current->right);
        
        Q.pop();
    }
}


void Preorder(struct Node* node) {
    if (node == NULL)
        return;
    cout << node->data << " ";
    Preorder(node->left);
    Preorder(node->right);
}


void Postorder(struct Node* node) {
    if (node == NULL)
        return;
    Postorder(node->left);
    Postorder(node->right);
    cout << node->data << " ";
}


void Inorder(Node* root) {
    if(root == NULL) return;
    Inorder(root->left);       
    cout << root->data << " ";  
    Inorder(root->right);      
}

int main() {
    Node* root = NULL;
    setlocale(LC_ALL, "Russian");

    std::srand(std::time(nullptr)); 

    int numElements = 10; 

    for (int i = 0; i < numElements; i++) {
        int randomNumber = std::rand() % 100;
        root = InsertNode(root, randomNumber); 
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
                    LevelOrder(root);
                    cout<<"\n";
                    break;
                }

                case 2:
                {
                    cout<<"Прямой обход: ";
                    Preorder(root);
                    cout<<"\n";
                    break;
                }

                case 3:
                {
                    cout<<"Обратный обход: ";
                    Postorder(root);
                    cout<<"\n";
                    break;
                }

                case 4:
                {
                    cout<<"Симметричный обход: ";
                    Inorder(root);
                    cout<<"\n";
                    break;
                }

                case 5:
                {
                    cout<<"Высота дерева: ";
                    cout << getHeight(root);
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