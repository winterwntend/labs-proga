#include <iostream>
using namespace std;

// === Класс vect (вектор) ===
class vect {
private:
    int dim;        // размерность
    double* b;      // массив элементов
    int num;        // номер объекта
    static int count; // общий счётчик объектов

public:
    // Статический метод для получения количества объектов
    static int getCount() { return count; }

    // Конструктор
    vect(int d = 2) : dim(d), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i)
            b[i] = 0;
        cout << "vect(): создан вектор #" << num << endl;
    }

    // Деструктор
    ~vect() {
        delete[] b;
        cout << "~vect(): удален вектор #" << num << endl;
    }

    // Получить элемент
    double get(int i) const {
        return b[i];
    }

    // Задать элемент
    void set(int i, double val) {
        b[i] = val;
    }

    // v + v
    vect operator+(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.set(i, b[i] + v.get(i));
        cout << "operator+ (vect): #" << num << " + #" << v.num << endl;
        return res;
    }

    // v - v
    vect operator-(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.set(i, b[i] - v.get(i));
        cout << "operator- (vect): #" << num << " - #" << v.num << endl;
        return res;
    }

    // -v
    vect operator-() const {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.set(i, -b[i]);
        cout << "operator- (vect): -#" << num << endl;
        return res;
    }

    // v * v (скалярное произведение)
    double operator*(const vect& v) const {
        double res = 0;
        for (int i = 0; i < dim; ++i)
            res += b[i] * v.get(i);
        cout << "operator* (vect*vect): #" << num << " * #" << v.num << endl;
        return res;
    }

    // k * v (внешний оператор)
    friend vect operator*(double k, const vect& v);

    // v = v
    vect& operator=(const vect& v) {
        if (this == &v) return *this;
        if (dim != v.dim) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
        }
        for (int i = 0; i < dim; ++i)
            b[i] = v.get(i);
        cout << "operator= (vect): #" << num << " = #" << v.num << endl;
        return *this;
    }

    // Вывод вектора
    void print() const {
        cout << "[ ";
        for (int i = 0; i < dim; ++i)
            cout << b[i] << " ";
        cout << "]" << endl;
    }
};

int vect::count = 0;

// Реализация внешнего оператора k * v
vect operator*(double k, const vect& v) {
    vect res(v.dim);
    for (int i = 0; i < v.dim; ++i)
        res.set(i, k * v.get(i));
    cout << "operator* (double*vect): " << k << " * #" << v.num << endl;
    return res;
}

// === Класс matr (матрица) ===
class matr {
private:
    int dim;        // размерность матрицы
    double* a;      // одномерный массив под матрицу
    int num;        // номер объекта
    static int count;

public:
    static int getCount() { return count; }

    // Конструктор
    matr(int d = 2) : dim(d), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; ++i)
            a[i] = 0;
        cout << "matr(): создана матрица #" << num << endl;
    }

    // Деструктор
    ~matr() {
        delete[] a;
        cout << "~matr(): удалена матрица #" << num << endl;
    }

    // Получить элемент матрицы
    double get(int i, int j) const {
        return a[i * dim + j];
    }

    // Задать элемент матрицы
    void set(int i, int j, double val) {
        a[i * dim + j] = val;
    }

    // m + m
    matr operator+(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; ++i)
            res.a[i] = a[i] + m.a[i];
        cout << "operator+ (matr): #" << num << " + #" << m.num << endl;
        return res;
    }

    // m - m
    matr operator-(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; ++i)
            res.a[i] = a[i] - m.a[i];
        cout << "operator- (matr): #" << num << " - #" << m.num << endl;
        return res;
    }

    // -m
    matr operator-() const {
        matr res(dim);
        for (int i = 0; i < dim * dim; ++i)
            res.a[i] = -a[i];
        cout << "operator- (matr): -#" << num << endl;
        return res;
    }

    // m * m
    matr operator*(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j) {
                double sum = 0;
                for (int k = 0; k < dim; ++k)
                    sum += get(i, k) * m.get(k, j);
                res.set(i, j, sum);
            }
        cout << "operator* (matr*matr): #" << num << " * #" << m.num << endl;
        return res;
    }

    // k * m
    friend matr operator*(double k, const matr& m);

    // m = m
    matr& operator=(const matr& m) {
        if (this == &m) return *this;
        if (dim != m.dim) {
            delete[] a;
            dim = m.dim;
            a = new double[dim * dim];
        }
        for (int i = 0; i < dim * dim; ++i)
            a[i] = m.a[i];
        cout << "operator= (matr): #" << num << " = #" << m.num << endl;
        return *this;
    }

    // m * v
    vect operator*(const vect& v) const {
        vect res(v.getCount());
        for (int i = 0; i < v.getCount(); ++i)
            for (int j = 0; j < dim; ++j)
                res.set(i, res.get(i) + get(i, j) * v.get(j));
        cout << "operator* (matr*vect): #" << num << " * вектор\n";
        return res;
    }

    // Вывод матрицы
    void print() const {
        cout << "Матрица #" << num << ":" << endl;
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j)
                cout << get(i, j) << " ";
            cout << endl;
        }
    }
};

int matr::count = 0;

// Реализация внешнего оператора k * m
matr operator*(double k, const matr& m) {
    matr res(m.dim);
    for (int i = 0; i < m.dim; ++i)
        for (int j = 0; j < m.dim; ++j)
            res.set(i, j, k * m.get(i, j));
    cout << "operator* (double*matr): " << k << " * #" << m.num << endl;
    return res;
}

// === Функция main ===
int main() {
    // Создаём векторы
    vect v1(2), v2(2);
    v1.set(0, 1); v1.set(1, 2);
    v2.set(0, 3); v2.set(1, 4);

    // Создаём матрицы
    matr m1(2), m2(2);
    m1.set(0, 0, 1); m1.set(0, 1, 2);
    m1.set(1, 0, 3); m1.set(1, 1, 4);

    m2.set(0, 0, 5); m2.set(0, 1, 6);
    m2.set(1, 0, 7); m2.set(1, 1, 8);

    // Примеры операций
    cout << "\n=== Примеры операций ===\n";

    vect v3 = v1 + v2;
    cout << "v1 + v2 = "; v3.print();

    vect v4 = v1 - v2;
    cout << "v1 - v2 = "; v4.print();

    double dot = v1 * v2;
    cout << "v1 * v2 = " << dot << endl;

    vect v5 = -v1;
    cout << "-v1 = "; v5.print();

    vect v6 = 5.0 * v2;
    cout << "5.0 * v2 = "; v6.print();

    v6 = v2;
    cout << "v6 = v2 -> v6 = "; v6.print();

    matr m3 = m1 + m2;
    cout << "\nm1 + m2 =\n"; m3.print();

    matr m4 = m1 - m2;
    cout << "\nm1 - m2 =\n"; m4.print();

    matr m5 = -m1;
    cout << "\n-m1 =\n"; m5.print();

    matr m6 = m1 * m2;
    cout << "\nm1 * m2 =\n"; m6.print();

    matr m7 = 2.0 * m1;
    cout << "\n2.0 * m1 =\n"; m7.print();

    matr m8 = m1;
    cout << "\nm8 = m1 -> m8:\n"; m8.print();

    vect v7 = m1 * v1;
    cout << "\nm1 * v1 = "; v7.print();

    return 0;
}
