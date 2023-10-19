#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <cmath>
#include <cctype>
 



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
            std::cout << "Index is not available!" << std::endl;
            return true;
        }

        return false;
    }


public:
    Node* toIndex(int index) {
        
        if (isAllowed(index)) {
            return nullptr; 
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

        if (!isEmpty()) {
            return head->Data;
        }
        throw std::out_of_range("Stack is empty");
    }

    int getSize()const {
        return size;
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

    bool AllowedIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index is not available!" << std::endl;
            return false;
        }

        return true;
    }


public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }


    int getSize() {
        return size; 
    }

    void insertAt(int index, T value) {
        if (AllowedIndex(index)) return;

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
            std::cout << "Element is not found!" << std::endl;
        }
    }

    void removeAt(int index) {
        if (AllowedIndex(index)) return;

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
        
        if(AllowedIndex(index)) return;
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



class InvalidInput : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

class SyntaxError : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};



struct Operator {
    enum class Associativity {
        Left = 0,
        Right = 1
    };

    const std::string name;
    unsigned int priority = 0;
    Associativity assoc = Associativity::Left;
    double(*func)(double, double);

    Operator(const std::string& name,
        unsigned int priority,
        double(*func)(double, double),
        Associativity assoc = Associativity::Left):
        name(name),
        priority(priority),
        func(func) {}
};

struct Function {
    const std::string name;
    size_t argc = 1;
    double(*func)(std::vector<double>&);

    Function(const std::string& name, size_t argc, double (*func)(std::vector<double>& args)) :
        name(name),
        func(func),
        argc(argc) {}
};

struct Token {
    enum class Type {
        Number = 0,
        Operator,
        Function,
        LeftBrace,
        RightBrace,
        ArgsSep
    };

    union UValue {
        double number = 0;
        Operator* oper;
        Function* func;
    } value;

    Type type = Type::Number;

    Token() = default;
    Token(Type type) {
        this->type = type;
    };
    Token(double number) {
        value.number = number;
        type = Type::Number;
    };
    Token(Operator* oper) {
        value.oper = oper;
        type = Type::Operator;
    };
    Token(Function* func) {
        value.func = func;
        type = Type::Function;
    }

    Token(char brace) {
        if (brace == '(') {
            type = Type::LeftBrace;
        }
        else if (brace == ')') {
            type = Type::RightBrace;
        }
        else {
            throw InvalidInput("Excepted brace");
        }
    }

};

std::ostream& operator<<(std::ostream& stream, Token token);

using OperatorMap = typename std::unordered_map<char, Operator*>;
using FunctionMap = typename std::unordered_map<std::string, Function*>;

const OperatorMap operators({
        {'+', new Operator("+", 100, [](double a, double b) { return a + b; })},
        {'-', new Operator("-", 100, [](double a, double b) { return a - b; })},
        {'*', new Operator("*", 200, [](double a, double b) { return a * b; })},
        {'/', new Operator("/", 200, [](double a, double b) { return a / b; })},
        {'^', new Operator("^", 300, [](double a, double b) {
            return std::pow(a, b);
            }, Operator::Associativity::Right)}
    });

const FunctionMap functions({
        {"sin", new Function("sin", 1, [](std::vector<double>& args) {
            return std::sin(args[0]);
        })},
        {"cos", new Function("cos", 1, [](std::vector<double>& args) {
            return std::cos(args[0]);
        })},
        {"pow", new Function("pow", 2, [](std::vector<double>& args) {
            return std::pow(args[0], args[1]);
        })}
    });

const std::unordered_set<char> whitespaces({
        ' ', '\n', '\t'
    });

enum class MinusState {
    UNARY = 0,
    BINARY = 1
};

string constructNumber(string::const_iterator& it, string::const_iterator end) {
    string value;
    bool dotExists = false;
    while (it != end && (isdigit(*it) || *it == '.')) {
        value += *it;
        if (*it == '.') {
            if (dotExists) {
                throw InvalidInput("Invalid number in input");
            }
            else {
                dotExists = true;
            }
        }
        it++;
    }
    if (value.empty()) {
        throw InvalidInput("Excepted a number, but nothing found");
    }
    return value;
}
string constructName(string::const_iterator& it, string::const_iterator end) {
    string value;
    while (it != end && isalpha(*it)) {
        value += *it;
        it++;
    }
    if (value.empty()) {
        throw InvalidInput("Excepted a name, nothing found");
    }
    return value;
}

std::vector<Token> tokenize(const std::string& expression) {
    vector<Token> tokens;

    OperatorMap::const_iterator operatorIt;
    FunctionMap::const_iterator functionIt;
    auto it = expression.cbegin();

    MinusState minusState = MinusState::UNARY;

    while (it != expression.cend()) {
        if (whitespaces.find(*it) != whitespaces.cend()) {
            // handle whitespace characters
        }
        else if (isdigit(*it) || *it == '.') {  // handle number
            if (!tokens.empty() && (tokens.back().type != Token::Type::Operator &&
                tokens.back().type != Token::Type::LeftBrace &&
                tokens.back().type != Token::Type::ArgsSep)) {
                throw SyntaxError("Missing '(' or ',' or operator  before number");
            }
            string numberStr = constructNumber(it, expression.cend());
            double number = stod(numberStr);
            tokens.emplace(tokens.end(), number);
            minusState = MinusState::BINARY;
            continue;
        }
        else if ((operatorIt = operators.find(*it)) != operators.cend()) {  // handle operator
            Operator* oper = operatorIt->second;
            if (minusState == MinusState::UNARY && oper->name == "-") {  // handle unary minus
                tokens.emplace(tokens.end(), 0.0);
            }
            else {  // check binary operators
                if (!tokens.empty() && (tokens.back().type != Token::Type::Number &&
                    tokens.back().type != Token::Type::RightBrace)) {
                    throw SyntaxError("Missing ')' or number before binary operator");
                }
            }
            tokens.emplace(tokens.end(), oper);
        }
        else if (*it == '(') {
            if (!tokens.empty() && (tokens.back().type != Token::Type::Operator &&
                tokens.back().type != Token::Type::Function &&
                tokens.back().type != Token::Type::LeftBrace &&
                tokens.back().type != Token::Type::ArgsSep)) {
                throw SyntaxError("Missing '(' or ',' or operator or function before '('");
            }
            tokens.emplace(tokens.end(), *it);
            minusState = MinusState::UNARY;
        }
        else if (*it == ')') {
            if (!tokens.empty() && (tokens.back().type != Token::Type::Number &&
                tokens.back().type != Token::Type::RightBrace)) {
                throw SyntaxError("Missing ')' or number before ')'");
            }
            tokens.emplace(tokens.end(), *it);
            minusState = MinusState::BINARY;
        }
        else if (*it == ',') {
            if (tokens.empty() ||
                !tokens.empty() && (tokens.back().type != Token::Type::Number &&
                    tokens.back().type != Token::Type::RightBrace)) {
                throw SyntaxError("Missing ')' or number before ','");
            }
            tokens.emplace(tokens.end(), Token::Type::ArgsSep);
            minusState = MinusState::UNARY;
        }
        else if (isalpha(*it)) {  // handle function name
            if (!tokens.empty() && (tokens.back().type != Token::Type::Operator &&
                tokens.back().type != Token::Type::LeftBrace &&
                tokens.back().type != Token::Type::ArgsSep)) {
                throw SyntaxError("Missing operator before function");
            }
            string name = constructName(it, expression.cend());
            functionIt = functions.find(name);
            if (functionIt != functions.cend()) {
                tokens.emplace(tokens.end(), functionIt->second);
            }
            else {
                throw InvalidInput("Function not exists: " + name);
            }
            minusState = MinusState::BINARY;
            continue;
        }
        else {  // if no one case success
            throw InvalidInput("Invalid char: " + string(1, *it));
        }
        ++it;
    }

    return tokens;
}
std::vector<Token> shuntingYard(const std::vector<Token>& input) {
    MyStack<Token> stack;
    vector<Token> output;

    for (auto&& token : input) {
        if (token.type == Token::Type::Number) {
            output.push_back(token);
        }
        else if (token.type == Token::Type::Function) {
            stack.push_front(token);
        }
        else if (token.type == Token::Type::ArgsSep) {
            Token top;
            bool argsCheck = false;
            while (!stack.isEmpty()) {
                top = stack.top();
                if (top.type == Token::Type::LeftBrace) {
                    argsCheck = true;
                    break;
                }
                output.push_back(top);
                stack.removeAt();
            }
            if (!argsCheck) {
                throw SyntaxError("Missing argument separator ',' or left brace '(' in expression");
            }
        }
        else if (token.type == Token::Type::Operator) {
            Operator* cur = token.value.oper;
            while (!stack.isEmpty()) {
                Token top = stack.top();
                if (top.type == Token::Type::Operator) {
                    Operator* op = top.value.oper;
                    if (op->priority > cur->priority ||
                        (op->priority == cur->priority && cur->assoc == Operator::Associativity::Left)) {
                        output.push_back(top);
                        stack.removeAt();
                    }
                    else {
                        break;
                    }
                }
                else if (top.type == Token::Type::Function) {
                    output.push_back(top);
                    stack.removeAt();
                }
                else {
                    break;
                }
            }
            stack.push_front(token);
        }
        else if (token.type == Token::Type::LeftBrace) {
            stack.push_front(token);
        }
        else if (token.type == Token::Type::RightBrace) {
            bool bracesCheck = false;
            while (!stack.isEmpty()) {
                Token top = stack.top();
                stack.removeAt();
                if (top.type == Token::Type::LeftBrace) {
                    bracesCheck = true;
                    break;
                }
                output.push_back(top);
            }
            if (!bracesCheck) {
                throw SyntaxError("Missing left brace '(' in expression");
            }
        }
    }

    while (!stack.isEmpty()) {
        Token top = stack.top();
        stack.removeAt();
        if (top.type == Token::Type::LeftBrace) {
            throw SyntaxError("Missing right brace ')' in expression");
        }
        output.push_back(top);
    }

    return output;

}

std::ostream& operator<<(std::ostream& stream, Token token) {
    if (token.type == Token::Type::Number) {
        stream << token.value.number;
    }
    else if (token.type == Token::Type::LeftBrace) {
        stream << "(";
    }
    else if (token.type == Token::Type::RightBrace) {
        stream << ")";
    }
    else if (token.type == Token::Type::Operator) {
        stream << token.value.oper->name;
    }
    else if (token.type == Token::Type::Function) {
        stream << token.value.func->name;
    }
    else if (token.type == Token::Type::ArgsSep) {
        stream << ',';
    }
    return stream;
}

double eval(const std::vector<Token>& rpnExpression) {
    MyStack<double> stack;
    for (auto&& token : rpnExpression) {
        if (token.type == Token::Type::Number) {
            stack.push_front(token.value.number);
        }
        else if (token.type == Token::Type::Operator) {
            if (stack.getSize() < 2) {
                throw SyntaxError("Not enough operands for operator: " + token.value.oper->name);
            }
            double b = stack.top();
            stack.removeAt();
            double a = stack.top();
            stack.removeAt();
            stack.push_front(token.value.oper->func(a, b));
        }
        else if (token.type == Token::Type::Function) {
            size_t argc = token.value.func->argc;
            if (stack.getSize() < argc) {
                throw SyntaxError("Not enough arguments for function: " + token.value.func->name);
            }
            vector<double> args;
            for (size_t i = 0; i < argc; i++) {
                args.insert(args.begin(), stack.top());
                stack.removeAt();
            }
            stack.push_front(token.value.func->func(args));
        }
        else {
            throw SyntaxError("In RPN met not allowed token: " + std::to_string(static_cast<int>(token.type)));
        }
    }
    if (stack.getSize() > 1) {
        throw SyntaxError("Calculation finished with stack size greater than 1");
    }
    return stack.top();
}
double eval(const std::string& expression) {
        
    auto tokens = tokenize(expression);
    auto rpn = shuntingYard(tokens);
    double result = eval(rpn);
    return result;
        
}







int main()
{
    std::string line;
    std::getline(std::cin, line);
    auto tokens = tokenize(line);


    std::cout << std::endl;

    try {

        auto rpn = shuntingYard(tokens);
        std::cout << "Reverse Polish Notation:" << std::endl;
        for (auto token : rpn) {
            std::cout << token << " ";
        }
        std::cout << std::endl;

        double result = eval(rpn);

        std::cout << "Result: " << result << std::endl;


    }
    catch (exception e) {
        cout << e.what() << endl;
        return 0;
    }


    return 0;



   /* DoubleLinkedList<int> ms; 

    ms.push_front(1);
    ms.push_back(12); 
    ms.removeAt(12); */

 
    
    

}