#include <iostream>
#include <vector>

using std::cout;
using std::endl;

namespace LinearAlgebra {

class Matrix;

class Vector {
    int size;
    std::vector<double> data;
    int id;
    static int counter;

public:
    explicit Vector(int n = 1) : size(n), data(n, 0.0), id(++counter) {
        cout << "Создан вектор №" << id << " размерности " << size << endl;
    }

    Vector(const Vector& other) : size(other.size), data(other.data), id(++counter) {
        cout << "Создана копия вектора №" << other.id << " как вектор №" << id << endl;
    }

    ~Vector() {
        cout << "Удален вектор №" << id << endl;
    }

    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            size = rhs.size;
            data = rhs.data;
        }
        cout << "Вектор №" << id << " = вектору №" << rhs.id << endl;
        return *this;
    }

    Vector operator+(const Vector& rhs) const {
        cout << "Вектор №" << id << " + вектор №" << rhs.id << endl;
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] + rhs.data[i];
        }
        return result;
    }

    Vector operator-(const Vector& rhs) const {
        cout << "Вектор №" << id << " - вектор №" << rhs.id << endl;
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] - rhs.data[i];
        }
        return result;
    }

    Vector operator-() const {
        cout << "-вектор №" << id << endl;
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = -data[i];
        }
        return result;
    }

    double operator*(const Vector& rhs) const {
        cout << "Вектор №" << id << " * вектор №" << rhs.id << " (скалярное)" << endl;
        double product = 0.0;
        for (int i = 0; i < size; ++i) {
            product += data[i] * rhs.data[i];
        }
        return product;
    }

    friend Vector operator*(double scalar, const Vector& vec);
    friend Vector operator*(const Matrix& mat, const Vector& vec);

    void set(int index, double value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    void print() const {
        cout << "Вектор №" << id << ": [";
        for (int i = 0; i < size; ++i) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

int Vector::counter = 0;

class Matrix {
    int dimension;
    std::vector<double> elements;
    int id;
    static int counter;

public:
    explicit Matrix(int n = 1) : dimension(n), elements(n*n, 0.0), id(++counter) {
        cout << "Создана матрица №" << id << " размерности " << dimension << "x" << dimension << endl;
    }

    Matrix(const Matrix& other) : dimension(other.dimension), elements(other.elements), id(++counter) {
        cout << "Создана копия матрицы №" << other.id << " как матрица №" << id << endl;
    }

    ~Matrix() {
        cout << "Удалена матрица №" << id << endl;
    }

    Matrix& operator=(const Matrix& rhs) {
        if (this != &rhs) {
            dimension = rhs.dimension;
            elements = rhs.elements;
        }
        cout << "Матрица №" << id << " = матрице №" << rhs.id << endl;
        return *this;
    }

    Matrix operator+(const Matrix& rhs) const {
        cout << "Матрица №" << id << " + матрица №" << rhs.id << endl;
        Matrix result(dimension);
        for (int i = 0; i < dimension*dimension; ++i) {
            result.elements[i] = elements[i] + rhs.elements[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& rhs) const {
        cout << "Матрица №" << id << " - матрица №" << rhs.id << endl;
        Matrix result(dimension);
        for (int i = 0; i < dimension*dimension; ++i) {
            result.elements[i] = elements[i] - rhs.elements[i];
        }
        return result;
    }

    Matrix operator-() const {
        cout << "-матрица №" << id << endl;
        Matrix result(dimension);
        for (int i = 0; i < dimension*dimension; ++i) {
            result.elements[i] = -elements[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& rhs) const {
        cout << "Матрица №" << id << " * матрица №" << rhs.id << endl;
        Matrix result(dimension);
        
        // Используем двойные указатели
        const double* pThis = elements.data();
        const double* pRhs = rhs.elements.data();
        double* pRes = result.elements.data();
        
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                double sum = 0.0;
                const double* pRow = pThis + i * dimension;
                const double* pCol = pRhs + j;
                
                for (int k = 0; k < dimension; ++k) {
                    sum += (*pRow) * (*pCol);
                    pRow++;
                    pCol += dimension;
                }
                
                *pRes++ = sum;
            }
        }
        
        return result;
    }

    friend Matrix operator*(double scalar, const Matrix& mat);
    friend Vector operator*(const Matrix& mat, const Vector& vec);

    void set(int row, int col, double value) {
        if (row >= 0 && row < dimension && col >= 0 && col < dimension) {
            elements[row*dimension + col] = value;
        }
    }

    void print() const {
        cout << "Матрица №" << id << ":" << endl;
        for (int i = 0; i < dimension; ++i) {
            cout << "[";
            for (int j = 0; j < dimension; ++j) {
                cout << elements[i*dimension + j];
                if (j < dimension - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
};

int Matrix::counter = 0;

Vector operator*(double scalar, const Vector& vec) {
    cout << scalar << " * вектор №" << vec.id << endl;
    Vector result(vec.size);
    for (int i = 0; i < vec.size; ++i) {
        result.data[i] = scalar * vec.data[i];
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& mat) {
    cout << scalar << " * матрица №" << mat.id << endl;
    Matrix result(mat.dimension);
    for (int i = 0; i < mat.dimension*mat.dimension; ++i) {
        result.elements[i] = scalar * mat.elements[i];
    }
    return result;
}

Vector operator*(const Matrix& mat, const Vector& vec) {
    cout << "Матрица №" << mat.id << " * вектор №" << vec.id << endl;
    Vector result(mat.dimension);
    
    // Используем двойные указатели
    const double* pMat = mat.elements.data();
    const double* pVec = vec.data.data();
    double* pRes = result.data.data();
    
    for (int i = 0; i < mat.dimension; ++i) {
        double sum = 0.0;
        const double* pRow = pMat + i * mat.dimension;
        const double* pElem = pVec;
        
        for (int j = 0; j < mat.dimension; ++j) {
            sum += (*pRow++) * (*pElem++);
        }
        
        *pRes++ = sum;
    }
    
    return result;
}

} // namespace LinearAlgebra

int main() {
    using namespace LinearAlgebra;

    cout << "\n=== Работа с векторами ===" << endl;
    Vector v1(3), v2(3), v3(3);
    
    v1.set(0, 1.0); v1.set(1, 2.0); v1.set(2, 3.0);
    v2.set(0, 4.0); v2.set(1, 5.0); v2.set(2, 6.0);
    
    v1.print();
    v2.print();
    
    v3 = v1 + v2;
    v3.print();
    
    v3 = v1 - v2;
    v3.print();
    
    v3 = -v1;
    v3.print();
    
    double dot = v1 * v2;
    cout << "Скалярное произведение: " << dot << endl;
    
    v3 = 2.5 * v1;
    v3.print();

    cout << "\n=== Работа с матрицами ===" << endl;
    Matrix m1(2), m2(2), m3(2);
    
    m1.set(0, 0, 1.0); m1.set(0, 1, 2.0);
    m1.set(1, 0, 3.0); m1.set(1, 1, 4.0);
    
    m2.set(0, 0, 5.0); m2.set(0, 1, 6.0);
    m2.set(1, 0, 7.0); m2.set(1, 1, 8.0);
    
    m1.print();
    m2.print();
    
    m3 = m1 + m2;
    m3.print();
    
    m3 = m1 - m2;
    m3.print();
    
    m3 = -m1;
    m3.print();
    
    m3 = m1 * m2;
    m3.print();
    
    m3 = 0.5 * m1;
    m3.print();

    cout << "\n=== Умножение матрицы на вектор ===" << endl;
    Vector v4(2);
    v4.set(0, 1.0); v4.set(1, 2.0);
    
    v4.print();
    m1.print();
    
    Vector v5 = m1 * v4;
    v5.print();

    return 0;
}
