#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

namespace Geometry {

const double PI = 3.14159265358979323846;

// Базовый абстрактный класс Shape
class Shape {
protected:
    int id;
    static int counter;
public:
    Shape() : id(++counter) {
        cout << "Создан объект Shape #" << id << endl;
    }
    
    virtual ~Shape() {
        cout << "Удален объект Shape #" << id << endl;
    }
    
    virtual void draw() const = 0;
    virtual void hide() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    
    int getId() const { return id; }
};

int Shape::counter = 0;

// Класс Point наследуется от Shape
class Point : public Shape {
protected:
    double x;
    double y;
public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {
        cout << "Создана точка #" << id << " (" << x << ", " << y << ")" << endl;
    }
    
    ~Point() override {
        cout << "Удалена точка #" << id << endl;
    }
    
    void draw() const override {
        cout << "Рисуем точку #" << id << " (" << x << ", " << y << ")" << endl;
    }
    
    void hide() const override {
        cout << "Скрываем точку #" << id << endl;
    }
    
    void move(double dx, double dy) override {
        x += dx;
        y += dy;
        cout << "Перемещение точки #" << id << " на (" << dx << ", " << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        cout << "Точка #" << id << " не может быть повернута (метод не выполняет действий)" << endl;
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    
protected:
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
};

// Класс Line наследуется от Shape
class Line : public Shape {
private:
    Point* p1;
    Point* p2;
public:
    Line(double x1, double y1, double x2, double y2) {
        p1 = new Point(x1, y1);
        p2 = new Point(x2, y2);
        cout << "Создана линия #" << id << " между точками #" 
             << p1->getId() << " и #" << p2->getId() << endl;
    }
    
    ~Line() override {
        delete p1;
        delete p2;
        cout << "Удалена линия #" << id << endl;
    }
    
    void draw() const override {
        cout << "Рисуем линию #" << id << " от (" << p1->getX() << "," << p1->getY() 
             << ") до (" << p2->getX() << "," << p2->getY() << ")" << endl;
    }
    
    void hide() const override {
        cout << "Скрываем линию #" << id << endl;
    }
    
    void move(double dx, double dy) override {
        p1->move(dx, dy);
        p2->move(dx, dy);
        cout << "Перемещение линии #" << id << " на (" << dx << ", " << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        double centerX = (p1->getX() + p2->getX()) / 2;
        double centerY = (p1->getY() + p2->getY()) / 2;
        
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        // Поворот первой точки
        double tx = p1->getX() - centerX;
        double ty = p1->getY() - centerY;
        p1->setX(centerX + tx * cosA - ty * sinA);
        p1->setY(centerY + tx * sinA + ty * cosA);
        
        // Поворот второй точки
        tx = p2->getX() - centerX;
        ty = p2->getY() - centerY;
        p2->setX(centerX + tx * cosA - ty * sinA);
        p2->setY(centerY + tx * sinA + ty * cosA);
        
        cout << "Поворот линии #" << id << " на " << angle << " градусов" << endl;
    }
};

// Класс Quadrilateral наследуется от Shape
class Quadrilateral : public Shape {
protected:
    std::vector<std::unique_ptr<Point>> vertices;
public:
    Quadrilateral(const std::vector<std::pair<double, double>>& points) {
        for (const auto& p : points) {
            vertices.push_back(std::make_unique<Point>(p.first, p.second));
        }
        cout << "Создан четырехугольник #" << id << " с " << vertices.size() << " вершинами" << endl;
    }
    
    void draw() const override {
        cout << "Рисуем четырехугольник #" << id << " с вершинами:";
        for (const auto& v : vertices) {
            cout << " (" << v->getX() << "," << v->getY() << ")";
        }
        cout << endl;
    }
    
    void hide() const override {
        cout << "Скрываем четырехугольник #" << id << endl;
    }
    
    void move(double dx, double dy) override {
        for (const auto& v : vertices) {
            v->move(dx, dy);
        }
        cout << "Перемещение четырехугольника #" << id << " на (" << dx << ", " << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        double centerX = 0, centerY = 0;
        for (const auto& v : vertices) {
            centerX += v->getX();
            centerY += v->getY();
        }
        centerX /= vertices.size();
        centerY /= vertices.size();
        
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        for (const auto& v : vertices) {
            double tx = v->getX() - centerX;
            double ty = v->getY() - centerY;
            v->setX(centerX + tx * cosA - ty * sinA);
            v->setY(centerY + tx * sinA + ty * cosA);
        }
        
        cout << "Поворот четырехугольника #" << id << " на " << angle << " градусов" << endl;
    }
};

// Классы-наследники Quadrilateral
class Square : public Quadrilateral {
public:
    Square(double side) : Quadrilateral({
        {0, 0}, {side, 0}, {side, side}, {0, side}
    }) {
        cout << "Создан квадрат #" << id << " со стороной " << side << endl;
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(double width, double height) : Quadrilateral({
        {0, 0}, {width, 0}, {width, height}, {0, height}
    }) {
        cout << "Создан прямоугольник #" << id << " " << width << "x" << height << endl;
    }
};

class Rhombus : public Quadrilateral {
public:
    Rhombus(double diagonal1, double diagonal2) : Quadrilateral({
        {0, -diagonal2/2}, {diagonal1/2, 0}, 
        {0, diagonal2/2}, {-diagonal1/2, 0}
    }) {
        cout << "Создан ромб #" << id << " с диагоналями " << diagonal1 << " и " << diagonal2 << endl;
    }
};

} // namespace Geometry

int main() {
    using namespace Geometry;
    using std::unique_ptr;
    using std::make_unique;

    cout << "\n=== Тестирование с указателями ===" << endl;
    
    // Создание объектов через указатели
    unique_ptr<Shape> shapes[] = {
        make_unique<Point>(1, 2),
        make_unique<Line>(0, 0, 3, 3),
        make_unique<Square>(5),
        make_unique<Rectangle>(4, 6),
        make_unique<Rhombus>(8, 6)
    };

    // Демонстрация полиморфизма
    for (const auto& shape : shapes) {
        shape->draw();
        shape->move(1, 1);
        shape->rotate(45);
        shape->hide();
        cout << "-----" << endl;
    }

    // Создание составной фигуры
    cout << "\n=== Составная фигура ===" << endl;
    unique_ptr<Shape> composite[] = {
        make_unique<Line>(0, 0, 10, 10),
        make_unique<Square>(3),
        make_unique<Point>(5, 5)
    };

    for (const auto& shape : composite) {
        shape->draw();
    }

    return 0;
}
