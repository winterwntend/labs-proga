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

    cout << "Список:\n";
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
