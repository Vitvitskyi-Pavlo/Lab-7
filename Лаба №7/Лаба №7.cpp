#include <iostream>


using namespace std;

// Функція-шаблон для знаходження максимального значення в масиві та підрахунку його кількості
template <typename T>
void findMaxAndCount(const T array[], int size, T& maxVal, int& count) {
    if (size == 0) {
        cout << "Array is empty." << endl;
        return;
    }

    maxVal = array[0];
    count = 1;

    for (int i = 1; i < size; ++i) {
        if (array[i] > maxVal) {
            maxVal = array[i];
            count = 1;  // Скидаємо лічильник, якщо знайдено більше значення
        }
        else if (array[i] == maxVal) {
            count++;  // Збільшуємо лічильник, якщо знайдено таке ж значення
        }
    }
}

void Task1() {
    // Приклад зі звичайними числами
    int intArray[] = { 3, 7, 1, 5, 7, 3, 7, 9 };
    int intMax, intCount;
    findMaxAndCount(intArray, sizeof(intArray) / sizeof(int), intMax, intCount);
    cout << "Max value in intArray: " << intMax << ", Count: " << intCount << endl;

    // Приклад з рядками
    const char* strArray[] = { "apple", "banana", "apple", "orange", "banana" };
    const char* strMax;
    int strCount;
    findMaxAndCount(strArray, sizeof(strArray) / sizeof(const char*), strMax, strCount);
    cout << "Max value in strArray: " << strMax << ", Count: " << strCount << endl;

}

// Функція-шаблон для сортування методом Шелла
template <typename T>
void shellSort(T array[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            T temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

// Спеціалізація для типу char*
template <>
void shellSort<char*>(char* array[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            char* temp = array[i];
            int j;
            for (j = i; j >= gap && strcmp(array[j - gap], temp) > 0; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void Task2() {
    // Приклад зі звичайними числами
    int intArray[] = { 7, 2, 5, 1, 9, 3 };
    int intSize = sizeof(intArray) / sizeof(int);
    shellSort(intArray, intSize);
    cout << "Sorted intArray: ";
    for (int i = 0; i < intSize; ++i) {
        cout << intArray[i] << " ";
    }
    cout << endl;

    // Приклад з рядками
    const char* strArray[] = { "banana", "apple", "orange", "grape", "kiwi" };
    int strSize = sizeof(strArray) / sizeof(const char*);
    shellSort(strArray, strSize);
    cout << "Sorted strArray: ";
    for (int i = 0; i < strSize; ++i) {
        cout << strArray[i] << " ";
    }
    cout << endl;
}

// Реалізація параметризованного стеку
template<typename T, int maxSize>
class Stack {
private:
    T data[maxSize];
    int top; // Індекс верхнього елемента стеку

public:
    // Конструктор
    Stack() : top(-1) {}

    // Перевірка на порожність
    bool isEmpty() const {
        return top == -1;
    }

    // Перевірка на переповнення
    bool isFull() const {
        return top == maxSize - 1;
    }

    // Додавання елементу в стек
    void push(const T& value) {
        if (!isFull()) {
            data[++top] = value;
        }
        else {
            cout << "Stack is full. Cannot push " << value << endl;
        }
    }

    // Видалення елементу зі стеку
    T pop() {
        if (!isEmpty()) {
            return data[top--];
        }
        else {
            cout << "Stack is empty. Cannot pop." << endl;
            return T();
        }
    }

    // Перегляд верхнього елементу стеку
    T peek() const {
        if (!isEmpty()) {
            return data[top];
        }
        else {
            cout << "Stack is empty. Cannot peek." << endl;
            return T();
        }
    }
};

void Task3() {
    // Створення стеку цілих чисел розміром 5
    Stack<int, 5> intStack;

    // Додавання елементів у стек
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Видалення та виведення елементів зі стеку
    cout << "Popped: " << intStack.pop() << endl;
    cout << "Popped: " << intStack.pop() << endl;

    // Перегляд верхнього елементу стеку без видалення
    cout << "Peeked: " << intStack.peek() << endl;

    // Додавання ще одного елементу
    intStack.push(40);

    // Виведення елементів, поки стек не стане порожнім
    while (!intStack.isEmpty()) {
        cout << "Popped: " << intStack.pop() << endl;
    }
}

// Клас елемента списку
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Клас ітератора для списку
class Iterator {
private:
    Node* current;

public:
    Iterator(Node* node) : current(node) {}

    void operator++() {
        if (current != nullptr) {
            current = current->next;
        }
    }

    int operator*() {
        return current->data;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }
};

// Клас, що представляє список
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void append(int value) {
        if (head == nullptr) {
            head = new Node(value);
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(value);
        }
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};


void Task4() {
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);

    Iterator it = list.begin();
    Iterator end = list.end();

    cout << "List elements: ";
    while (it != end) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}


void main() {
    int TaskN;
    setlocale(LC_CTYPE, "ukr");


    do {
        cout << "\n\nВведiть свiй вибiр: ";
        cin >> TaskN;

        switch (TaskN) {
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        case 4:
            Task4();
            break;
        case 0:
            cout << "Вихiд з програми\n";
            break;
        default:
            cout << "Невiрний вибiр! Будь ласка, введiть число вiд 0 до 4.\n";
        }
    } while (TaskN != 0);


}
