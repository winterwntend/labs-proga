#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

// === Класс "Студент" (только свойства) ===
class Student {
public:
    string name;
    int age;
    string group;

    // Печать студента
    void print() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Группа: " << group << endl;
    }
};

// === Функции программы ===

// 1. Ввод студента с клавиатуры
Student inputStudent() {
    Student s;
    cout << "Введите имя: ";
    cin >> s.name;
    cout << "Введите возраст: ";
    cin >> s.age;
    cout << "Введите группу: ";
    cin >> ws; // пропустить пробелы
    getline(cin, s.group);
    return s;
}

// 2. Сохранение в строку формата "имя возраст группа"
string studentToString(const Student& s) {
    return s.name + " " + to_string(s.age) + " " + s.group;
}

// 3. Чтение строки и преобразование в объект
Student stringToStudent(const string& line) {
    Student s;
    stringstream ss(line);
    ss >> s.name >> s.age;
    getline(ss >> ws, s.group); // пропускаем пробелы и читаем остальное как группу
    return s;
}

// 4. Запись всех студентов в файл
void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    for (const auto& s : students) {
        file << studentToString(s) << endl;
    }
    file.close();
    cout << "Данные сохранены в файл.\n";
}

// 5. Чтение всех студентов из файла
vector<Student> loadFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            students.push_back(stringToStudent(line));
    }
    file.close();
    cout << "Данные загружены из файла.\n";
    return students;
}

// 6. Обновление студента по индексу
void updateStudent(vector<Student>& students, int index) {
    if (index >= 0 && index < students.size()) {
        students[index] = inputStudent();
        cout << "Студент обновлен.\n";
    } else {
        cout << "Неверный индекс.\n";
    }
}

// 7. Удаление студента по индексу
void deleteStudent(vector<Student>& students, int index) {
    if (index >= 0 && index < students.size()) {
        students.erase(students.begin() + index);
        cout << "Студент удален.\n";
    } else {
        cout << "Неверный индекс.\n";
    }
}

// 8. Вывод списка студентов
void printAllStudents(const vector<Student>& students) {
    for (size_t i = 0; i < students.size(); ++i) {
        cout << "[" << i << "] ";
        students[i].print();
    }
}

// === Основная функция ===
int main() {
    setlocale(LC_ALL, "Russian");
    vector<Student> students;
    string filename = "students.txt";
    int choice;

    do {
        cout << "\n=== Меню ===\n";
        cout << "1. Ввести студента\n";
        cout << "2. Сохранить в файл\n";
        cout << "3. Загрузить из файла\n";
        cout << "4. Обновить студента\n";
        cout << "5. Удалить студента\n";
        cout << "6. Показать всех студентов\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student s = inputStudent();
                students.push_back(s);
                break;
            }
            case 2:
                saveToFile(students, filename);
                break;
            case 3:
                students = loadFromFile(filename);
                break;
            case 4: {
                int index;
                cout << "Введите индекс для обновления: ";
                cin >> index;
                updateStudent(students, index);
                break;
            }
            case 5: {
                int index;
                cout << "Введите индекс для удаления: ";
                cin >> index;
                deleteStudent(students, index);
                break;
            }
            case 6:
                printAllStudents(students);
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);

    return 0;
}
