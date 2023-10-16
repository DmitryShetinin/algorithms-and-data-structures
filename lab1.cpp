#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stack>


using namespace std;


template <typename T>
class MyStack
{
public:
    struct Node
    {
        T Data{};
        Node* next{};
        Node* prev{};

        Node(T data) {
            Data = data; 
        }
    };

  

protected:
    Node* head = NULL;
    Node* tail = NULL;
    int size = 0;

    bool isAllowed(int index) {
        if (index > size || index < 0) {
            std::cout << "Недопустимый индекс!" << std::endl;
            return true;
        }

        return false;
    }


public:
    Node* toIndex(int index) {
        
        if (isAllowed(index)) {
            return new Node(-1); 
        }

        int midle = (size / 2) + 1;

        if (index > midle) {
            index = size - index - 1 ; 
            Node* temp = tail;
            while (index--) {
                temp = temp->prev;
            }
            return temp;
        }

        Node* temp = head;
        while (index--) {
            temp = temp->next;
        }
        return temp;
    }

    void push_front(T data) {
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;

        if (tail == NULL)
            tail = ptr;
        head = ptr;
        size++;
    }

    void showList()const {

        Node* temp = head;
        int i = 0;
        while (temp) {
            std::cout << "["<< i++ << "]" << temp->Data << std::endl;
            temp = temp->next;
        }
    }

    void removeAt(int index = 0) {

        if (isAllowed(index)) {      
            return;
        }

        Node* temp = toIndex(index);
        if (temp == NULL) return; 

        if (index == 0) {
            head = toIndex(index + 1);
            size--;
            return;
        }

        temp->prev->next = temp->next;
        size--;
    }

    bool isEmpty() {
        if (size == 0) return true; 
        return false;
    }

    T top() {
        if (size == 0) {
            return 0;
        }
        if (head == nullptr) return 0; 
        return head->Data;
    }

};

template <typename T>
class DoubleLinkedList : public MyStack<T>
{
    using ParentClass = MyStack<T>;
public:
    using Node = typename ParentClass::Node;
    using ParentClass::tail;
    using ParentClass::head;
    using ParentClass::size;
    using ParentClass::toIndex;

public:
    void push_back(T data) {
        Node* ptr = new Node(data);
        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;

        tail = ptr;
        size++;
    }
    void insertAt(T data, int index) {
        Node* tempNode = new Node(data); 
        tempNode->next = toIndex(index);
        toIndex(index - 1)->next = tempNode;
        size++;
    }

    T get(int index) {
        return toIndex(index)->Data;
    }
    T operator [](int index) {
        return toIndex(index)->Data;
    }
    int getSize()const {
        return size;
    }
    friend std::ostream& operator<<(std::ostream& output, DoubleLinkedList<T>& list) {
        for (const T& value : list) {
            output << value;
        }
        return output;
    };
    friend std::istream& operator>>(std::istream& input, DoubleLinkedList<T>& n) {
        T value;
        while (input >> value) {
            n.push_back(value);
        }
        return input;

    };

    class Iterator
    {
    private:
        Node* current{};

    public:
        Iterator(Node* current) : current(current) {}

        T& operator*() const {
            return current->Data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }

        Iterator& operator--()const {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int)const {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    Iterator begin() const {
        return Iterator(head);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }
};
 

template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void insertAt(int index, T value) {
        if (index < 0 || index > size) {
            std::cout << "Недопустимый индекс!" << std::endl;
            return;
        }

        if (size == capacity) {
            resize();
        }

        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;
        size++;
    }

    void remove(T value) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            removeAt(index);
        }
        else {
            std::cout << "Элемент не найден!" << std::endl;
        }
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Недопустимый индекс!" << std::endl;
            return;
        }

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    void append(T value) {
        if (size == capacity) {
            resize();
        }

        arr[size] = value;
        size++;
    }

    T get(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Недопустимый индекс!" << std::endl;
            return T();
        }

        return arr[index];
    }

    int getCapacity() {
        return capacity;
    }

private:
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }
};




bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}
double evaluateExpression(const std::string& expression) {
    MyStack<double> values;
    MyStack<char> operators;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (isdigit(expression[i])) {
            double value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values.push_front(value);
            i--;
        }
        else if (expression[i] == '(') {
            operators.push_front(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                double b = values.top();
                values.removeAt();
                double a = values.top();
                values.removeAt();
                char op = operators.top();
                operators.removeAt();
                values.push_front(applyOperator(a, b, op));
            }
            operators.removeAt();
        }
        else if (isOperator(expression[i])) {
            while (!operators.isEmpty() && precedence(operators.top()) >= precedence(expression[i])) {
                double b = values.top();
                values.removeAt();
                double a = values.top();
                values.removeAt();
                char op = operators.top();
                operators.removeAt();
                values.push_front(applyOperator(a, b, op));
            }
            operators.push_front(expression[i]);
        }
    }

    while (!operators.isEmpty()) {
        double b = values.top();
        values.removeAt();
        double a = values.top();
        values.removeAt();
        char op = operators.top();
        operators.removeAt();
        values.push_front(applyOperator(a, b, op));
    }

    return values.top();
}

std::string infixToPostfix(std::string expression) {
    expression.erase(std::remove_if(expression.begin(), expression.end(), [](char c) { return std::isspace(c); }), expression.end());

    std::string postfix;
    std::stack<char> operators;

    for (char c : expression) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove the '('
        }
        else {
            while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}


int main()
{
    
  /*  std::string expression;
    std::cout << "Enter an expression in Reverse Polish Notation: ";
    std::getline(std::cin, expression);

    double result = evaluateExpression(expression);
    std::cout << "Postfix expression: " << infixToPostfix(expression) << std::endl;
    std::cout << "Result: " << result << std::endl;*/

    DoubleLinkedList<int> ms; 

    ms.push_front(1);
    ms.push_back(12); 
    ms.removeAt(12); 

    return 0;
    
    

}