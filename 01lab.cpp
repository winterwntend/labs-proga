#include <iostream>
#include <string>
using namespace std;

// Структура данных
struct Record {
    string name;
    int age;
    double score;
};

// Узел списка
struct Node {
    Record data;
    Node* next;
};

// Добавление в начало
void addToHead(Node*& head, Record r) {
    Node* newNode = new Node{r, head};
    head = newNode;
}

// Добавление в конец
void addToTail(Node*& head, Record r) {
    Node* newNode = new Node{r, nullptr};
    if (!head) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = newNode;
}

// Добавление перед указанным именем
void addBefore(Node*& head, string targetName, Record r) {
    if (!head) return;
    
    if (head->data.name == targetName) {
        addToHead(head, r);
        return;
    }
    
    Node* cur = head;
    while (cur->next && cur->next->data.name != targetName)
        cur = cur->next;
    
    if (cur->next) {
        Node* newNode = new Node{r, cur->next};
        cur->next = newNode;
    }
}

// Добавление после указанного имени
void addAfter(Node*& head, string targetName, Record r) {
    if (!head) return;
    
    Node* cur = head;
    while (cur && cur->data.name != targetName)
        cur = cur->next;
    
    if (cur) {
        Node* newNode = new Node{r, cur->next};
        cur->next = newNode;
    }
}

// Удаление по имени
void deleteByName(Node*& head, string name) {
    if (!head) return;
    if (head->data.name == name) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }
    Node* cur = head;
    while (cur->next && cur->next->data.name != name)
        cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
}

// Вывод списка
void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        cout << cur->data.name << " | " << cur->data.age << " | " << cur->data.score << endl;
        cur = cur->next;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* head = nullptr;

    // Добавляем элементы
    addToHead(head, {"Аня", 20, 89.5});
    addToTail(head, {"Вася", 22, 95.0});
    addToTail(head, {"Катя", 19, 78.0});

    cout << "Исходный список:\n";
    printList(head);

    // Добавляем перед Васей
    addBefore(head, "Вася", {"Петя", 21, 85.5});
    cout << "После добавления Пети перед Васей:\n";
    printList(head);

    // Добавляем после Кати
    addAfter(head, "Катя", {"Оля", 18, 92.0});
    cout << "После добавления Оли после Кати:\n";
    printList(head);

    cout << "Удаляем Васю:\n";    
    deleteByName(head, "Вася");
    printList(head);

    // Очистка памяти
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    return 0;
}
