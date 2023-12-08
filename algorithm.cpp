#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class BinNode {
public:
    int data;
    int height;
    BinNode* left;
    BinNode* right;
    BinNode(int data) {
        this->data = data;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

BinNode* insert_node(BinNode* root, int data) {
    if (root == nullptr) {
        return new BinNode(data);
    }
    if (data < root->data) {
        root->left = insert_node(root->left, data);
    }
    else {
        root->right = insert_node(root->right, data);
    }
    return root;
}

void inorder_traversal(BinNode* node, vector<int>& result) {
    if (node) {
        inorder_traversal(node->left, result);
        result.push_back(node->data);
        inorder_traversal(node->right, result);
    }
}

vector<int> sorted_nodes(BinNode* root) {
    vector<int> result;
    inorder_traversal(root, result);
    return result;
}

void print_inorder(BinNode* node) {
    if (node == nullptr) {
        return;
    }
    print_inorder(node->left);
    cout << node->data << " ";
    print_inorder(node->right);
}

BinNode* construct_tree(string expression) {
    stack<BinNode*> stack;
    BinNode* root = nullptr;
    for (char c : expression) {
        if (c == '(') {
            BinNode* new_node = new BinNode(NULL);
            if (root == nullptr) {
                root = new_node;
            }
            else {
                BinNode* top = stack.top();
                if (top->left == nullptr) {
                    top->left = new_node;
                }
                else {
                    top->right = new_node;
                }
            }
            stack.push(new_node);
        }
        else if (c == ')') {
            stack.pop();
        }
        else {
            if (isdigit(c)) {
                if (stack.top()->data == NULL) {
                    stack.top()->data = c - '0';
                }
                else {
                    stack.top()->data = stack.top()->data * 10 + (c - '0');
                }
            }
        }
    }
    return root;
}

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

class AVLTree {
public:
    Node* root;
    AVLTree() {
        this->root = nullptr;
    }
    Node* BintoAVL(vector<int> arr) {
        if (arr.empty()) {
            return nullptr;
        }
        int mid = arr.size() / 2;
        Node* root = new Node(arr[mid]);
        root->left = BintoAVL(vector<int>(arr.begin(), arr.begin() + mid));
        root->right = BintoAVL(vector<int>(arr.begin() + mid + 1, arr.end()));
        root->height = 1 + max(height(root->left), height(root->right));
        return root;
    }
    bool search(int key) {
        return _search(this->root, key);
    }
    bool _search(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return _search(node->left, key);
        }
        else {
            return _search(node->right, key);
        }
    }
    void insert(int key) {
        if (this->root == nullptr) {
            this->root = new Node(key);
        }
        else {
            _insert(key, this->root);
        }
    }
    void _insert(int key, Node* node) {
        if (key < node->key) {
            if (node->left) {
                _insert(key, node->left);
            }
            else {
                node->left = new Node(key);
            }
        }
        else {
            if (node->right) {
                _insert(key, node->right);
            }
            else {
                node->right = new Node(key);
            }
        }
        node->height = 1 + max(height(node->left), height(node->right));
        _balance(node);
    }
    void deleteNode(int key) {
        this->root = _delete(key, this->root);
    }
    Node* _delete(int key, Node* node) {
        if (node == nullptr) {
            return node;
        }
        else if (key < node->key) {
            node->left = _delete(key, node->left);
        }
        else if (key > node->key) {
            node->right = _delete(key, node->right);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                node = nullptr;
            }
            else if (node->left == nullptr) {
                node = node->right;
            }
            else if (node->right == nullptr) {
                node = node->left;
            }
            else {
                Node* min_node = find_min(node->right);
                node->key = min_node->key;
                node->right = _delete(min_node->key, node->right);
            }
        }
        if (node == nullptr) {
            return node;
        }
        node->height = 1 + max(height(node->left), height(node->right));
        _balance(node);
        return node;
    }
    void _balance(Node* node) {
        int balance_factor = height(node->left) - height(node->right);
        if (balance_factor > 1) {
            if (height(node->left->left) >= height(node->left->right)) {
                node = rotate_right(node);
            }
            else {
                node->left = rotate_left(node->left);
                node = rotate_right(node);
            }
        }
        else if (balance_factor < -1) {
            if (height(node->right->right) >= height(node->right->left)) {
                node = rotate_left(node);
            }
            else {
                node->right = rotate_right(node->right);
                node = rotate_left(node);
            }
        }
    }
    Node* rotate_right(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;
        y->right = z;
        z->left = T3;
        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }
    Node* rotate_left(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;
        y->left = z;
        z->right = T2;
        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    Node* find_min(Node* node) {
        if (node->left) {
            return find_min(node->left);
        }
        return node;
    }
    void width_first_traversal() {
        if (this->root == nullptr) {
            return;
        }
        queue<Node*> queue;
        queue.push(this->root);
        while (!queue.empty()) {
            Node* node = queue.front();
            queue.pop();
            cout << node->key << " ";
            if (node->left) {
                queue.push(node->left);
            }
            if (node->right) {
                queue.push(node->right);
            }
        }
    }
    void depth_first_preorder() {
        stack<Node*> stack;
        stack.push(this->root);
        while (!stack.empty()) {
            Node* node = stack.top();
            stack.pop();
            cout << node->key << " ";
            if (node->right) {
                stack.push(node->right);
            }
            if (node->left) {
                stack.push(node->left);
            }
        }
    }
    void depth_first_inorder(Node* root) {
        stack<Node*> stack;
        Node* current = root;
        bool done = false;
        while (!done) {
            if (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            else {
                if (!stack.empty()) {
                    current = stack.top();
                    stack.pop();
                    cout << current->key << " ";
                    current = current->right;
                }
                else {
                    done = true;
                }
            }
        }
    }
    void depth_first_postorder() {
        stack<Node*> stack1;
        stack<Node*> stack2;
        stack1.push(this->root);
        while (!stack1.empty()) {
            Node* node = stack1.top();
            stack1.pop();
            stack2.push(node);
            if (node->left) {
                stack1.push(node->left);
            }
            if (node->right) {
                stack1.push(node->right);
            }
        }
        while (!stack2.empty()) {
            Node* node = stack2.top();
            stack2.pop();
            cout << node->key << " ";
        }
    }
};

int main() {
    BinNode* b_root = new BinNode(8);
    insert_node(b_root, 1);
    insert_node(b_root, 3);
    insert_node(b_root, 6);
    insert_node(b_root, 2);
    cout << "Binary tree:" << endl;
    print_inorder(b_root);
    cout << endl;

    string expression = "(8 (9 (5)) (1))";
    BinNode* tree = construct_tree(expression);
    cout << "Expression:" << endl;
    print_inorder(tree);
    cout << endl;

    AVLTree avl_from_bin;
    avl_from_bin.root = avl_from_bin.BintoAVL(sorted_nodes(b_root));
    cout << "AVL from Binary:" << endl;
    avl_from_bin.depth_first_preorder();
    cout << endl;

    AVLTree avl_tree;
    avl_tree.insert(9);
    avl_tree.insert(5);
    avl_tree.insert(10);
    avl_tree.insert(6);
    avl_tree.insert(11);
    avl_tree.insert(2);
    cout << "Original AVL Tree:" << endl;
    avl_tree.depth_first_preorder();
    cout << endl;

    avl_tree.deleteNode(10);
    cout << "AVL Tree after deleting node 10:" << endl;
    avl_tree.depth_first_preorder();
    cout << endl;

    cout << "AVL Tree width traversal:" << endl;
    avl_tree.width_first_traversal();
    cout << endl;

    cout << "AVL Tree depth preorder traversal:" << endl;
    avl_tree.depth_first_preorder();
    cout << endl;

    cout << "AVL Tree depth inorder traversal:" << endl;
    avl_tree.depth_first_inorder(avl_tree.root);
    cout << endl;

    cout << "AVL Tree depth postorder traversal:" << endl;
    avl_tree.depth_first_postorder();
    cout << endl;

    return 0;
}


