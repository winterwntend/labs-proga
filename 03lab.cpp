#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

namespace Geometry {

const double PI = 3.14159265358979323846;

// Базовый класс Point
class Point {
protected:
    double x;
    double y;
    int id;
    static int counter;
public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y), id(++counter) {
        cout << "Создана точка #" << id << " (" << x << ", " << y << ")" << endl;
    }
    
    virtual ~Point() {
        cout << "Удалена точка #" << id << endl;
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    int getId() const { return id; }
    
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
    }
};

int Point::counter = 0;

// Абстрактный класс Shape, наследующий от Point
class Shape : public Point {
public:
    Shape(double x = 0.0, double y = 0.0) : Point(x, y) {
        cout << "Создан объект Shape #" << id << endl;
    }
    
    virtual ~Shape() override {
        cout << "Удален объект Shape #" << id << endl;
    }
    
    virtual void draw() const = 0;
    virtual void hide() const = 0;
    virtual void rotate(double angle) = 0;
};

// Класс Line наследуется от Shape
class Line : public Shape {
private:
    Point* p2; // Указатель на вторую точку
public:
    Line(double x1, double y1, double x2, double y2) : Shape(x1, y1) {
        p2 = new Point(x2, y2);
        cout << "Создана линия #" << id << " между точками #" 
             << id << " и #" << p2->getId() << endl;
    }
    
    ~Line() override {
        delete p2;
        cout << "Удалена линия #" << id << endl;
    }
    
    void draw() const override {
        cout << "Рисуем линию #" << id << " от (" << x << "," << y 
             << ") до (" << p2->getX() << "," << p2->getY() << ")" << endl;
    }
    
    void hide() const override {
        cout << "Скрываем линию #" << id << endl;
    }
    
    void move(double dx, double dy) override {
        Point::move(dx, dy);
        p2->move(dx, dy);
        cout << "Перемещение линии #" << id << " на (" << dx << ", " << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        double centerX = (x + p2->getX()) / 2;
        double centerY = (y + p2->getY()) / 2;
        
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        // Поворот первой точки (наследуется от Point)
        double tx = x - centerX;
        double ty = y - centerY;
        x = centerX + tx * cosA - ty * sinA;
        y = centerY + tx * sinA + ty * cosA;
        
        // Поворот второй точки
        tx = p2->getX() - centerX;
        ty = p2->getY() - centerY;
        p2->setX(centerX + tx * cosA - ty * sinA);
        p2->setY(centerY + tx * sinA + ty * cosA);
        
        cout << "Поворот линии #" << id << " на " << angle << " градусов" << endl;
    }
    
private:
    // Методы для доступа к protected полям Point
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
};

// Класс Quadrilateral наследуется от Shape
class Quadrilateral : public Shape {
protected:
    std::vector<std::unique_ptr<Point>> vertices;
public:
    Quadrilateral(double x, double y, const std::vector<std::pair<double, double>>& points) 
        : Shape(x, y) {
        for (const auto& p : points) {
            vertices.push_back(std::make_unique<Point>(x + p.first, y + p.second));
        }
        cout << "Создан четырехугольник #" << id << " с " << vertices.size() << " вершинами" << endl;
    }
    
    void draw() const override {
        cout << "Рисуем четырехугольник #" << id << " с центром (" << x << "," << y << ") и вершинами:";
        for (const auto& v : vertices) {
            cout << " (" << v->getX() << "," << v->getY() << ")";
        }
        cout << endl;
    }
    
    void hide() const override {
        cout << "Скрываем четырехугольник #" << id << endl;
    }
    
    void move(double dx, double dy) override {
        Shape::move(dx, dy);
        for (const auto& v : vertices) {
            v->move(dx, dy);
        }
        cout << "Перемещение четырехугольника #" << id << " на (" << dx << ", " << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        double centerX = x;
        double centerY = y;
        
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

// Производные классы четырехугольников
class Square : public Quadrilateral {
public:
    Square(double x, double y, double side) 
        : Quadrilateral(x, y, {{-side/2, -side/2}, {side/2, -side/2}, 
                         {side/2, side/2}, {-side/2, side/2}}) {
        cout << "Создан квадрат #" << id << " со стороной " << side << endl;
    }
    
    void draw() const override {
        cout << "Рисуем квадрат #" << id << " с центром (" << x << "," << y 
             << ") и стороной " << (vertices[1]->getX() - vertices[0]->getX()) << endl;
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(double x, double y, double width, double height) 
        : Quadrilateral(x, y, {{-width/2, -height/2}, {width/2, -height/2}, 
                       {width/2, height/2}, {-width/2, height/2}}) {
        cout << "Создан прямоугольник #" << id << " " << width << "x" << height << endl;
    }
    
    void draw() const override {
        cout << "Рисуем прямоугольник #" << id << " " 
             << (vertices[1]->getX() - vertices[0]->getX()) << "x" 
             << (vertices[2]->getY() - vertices[1]->getY()) << endl;
    }
};

} // namespace Geometry

int main() {
    using namespace Geometry;
    using std::unique_ptr;
    using std::make_unique;

    cout << "\n=== Тестирование иерархии Shape -> Point ===" << endl;
    
    // Создание объектов через указатели
    unique_ptr<Shape> shapes[] = {
        make_unique<Point>(1, 2),
        make_unique<Line>(0, 0, 3, 3),
        make_unique<Square>(5, 5, 4),
        make_unique<Rectangle>(2, 3, 6, 4)
    };

    // Демонстрация полиморфизма
    for (const auto& shape : shapes) {
        shape->draw();
        shape->move(1, 1);
        shape->rotate(45);
        shape->hide();
        cout << "-----" << endl;
    }

    return 0;
}
