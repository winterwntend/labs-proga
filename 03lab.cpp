
 
Search Gists
Search...
All gists
Back to GitHub
@w1lkaz
w1lkaz/gist:09585286ec45b3116468460aff9624d4 Secret
Created 36 minutes ago • Report abuse
Code
Revisions
1
Clone this repository at &lt;script src=&quot;https://gist.github.com/w1lkaz/09585286ec45b3116468460aff9624d4.js&quot;&gt;&lt;/script&gt;
<script src="https://gist.github.com/w1lkaz/09585286ec45b3116468460aff9624d4.js"></script>
kamilla
gistfile1.txt
#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;

namespace Geometry {

const double PI = 3.14159265358979323846;

// Абстрактный класс Точка
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
    
    // Чисто виртуальные методы (абстрактный класс)
    virtual void draw() const = 0;
    virtual void hide() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    
    // Методы с разным уровнем доступа
    double getX() const { return x; }       // public доступ к x
    double getY() const { return y; }       // public доступ к y
    int getId() const { return id; }        // public доступ к id
protected:
    void setX(double newX) { x = newX; }   // protected доступ
    void setY(double newY) { y = newY; }   // protected доступ
private:
    // Приватный метод для демонстрации регламентации доступа
    void privateMethod() {
        cout << "Приватный метод точки #" << id << endl;
    }
};

int Point::counter = 0;

// Класс Линия
class Line : public Point {
protected:
    double x2;
    double y2;
public:
    Line(double x1, double y1, double x2, double y2) 
        : Point(x1, y1), x2(x2), y2(y2) {
        cout << "Создана линия #" << getId() << " от (" << x << "," << y 
             << ") до (" << x2 << "," << y2 << ")" << endl;
    }
    
    void draw() const override {
        cout << "Рисуем линию #" << getId() << " от (" << x << "," << y 
             << ") до (" << x2 << "," << y2 << ")" << endl;
    }
    
    void hide() const override {
        cout << "Скрываем линию #" << getId() << " от (" << x << "," << y 
             << ") до (" << x2 << "," << y2 << ")" << endl;
    }
    
    void move(double dx, double dy) override {
        cout << "Перемещение линии #" << getId() << " на (" << dx << ", " << dy << ")" << endl;
        x += dx;
        y += dy;
        x2 += dx;
        y2 += dy;
    }
    
    void rotate(double angle) override {
        cout << "Поворот линии #" << getId() << " на " << angle << " градусов" << endl;
        double centerX = (x + x2) / 2;
        double centerY = (y + y2) / 2;
        
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        // Поворот первой точки относительно центра
        double tx = x - centerX;
        double ty = y - centerY;
        x = centerX + tx * cosA - ty * sinA;
        y = centerY + tx * sinA + ty * cosA;
        
        // Поворот второй точки относительно центра
        tx = x2 - centerX;
        ty = y2 - centerY;
        x2 = centerX + tx * cosA - ty * sinA;
        y2 = centerY + tx * sinA + ty * cosA;
    }
};

// Базовый класс для четырехугольников
class Quadrilateral : virtual public Point {
protected:
    std::vector<std::pair<double, double>> vertices;
    double angle;
public:
    Quadrilateral(double x, double y, const std::vector<std::pair<double, double>>& points) 
        : Point(x, y), angle(0) {
        for (const auto& p : points) {
            vertices.emplace_back(x + p.first, y + p.second);
        }
        cout << "Создан четырехугольник #" << getId() << endl;
    }
    
    void draw() const override {
        cout << "Рисуем четырехугольник #" << getId() << " с вершинами:";
        for (const auto& v : vertices) {
            cout << " (" << v.first << "," << v.second << ")";
        }
        cout << endl;
    }
    
    void hide() const override {
        cout << "Скрываем четырехугольник #" << getId() << endl;
    }
    
    void move(double dx, double dy) override {
        cout << "Перемещение четырехугольника #" << getId() << " на (" << dx << ", " << dy << ")" << endl;
        x += dx;
        y += dy;
        for (auto& v : vertices) {
            v.first += dx;
            v.second += dy;
        }
    }
    
    void rotate(double angle) override {
        cout << "Поворот четырехугольника #" << getId() << " на " << angle << " градусов" << endl;
        double centerX = 0, centerY = 0;
        for (const auto& v : vertices) {
            centerX += v.first;
            centerY += v.second;
        }
        centerX /= vertices.size();
        centerY /= vertices.size();
        
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        for (auto& v : vertices) {
            double tx = v.first - centerX;
            double ty = v.second - centerY;
            v.first = centerX + tx * cosA - ty * sinA;
            v.second = centerY + tx * sinA + ty * cosA;
        }
        this->angle += angle;
    }
};

// Класс Квадрат (используется для виртуального наследования)
class Square : virtual public Quadrilateral {
public:
    Square(double x, double y, double side) 
        : Point(x, y), 
          Quadrilateral(x, y, {{-side/2, -side/2}, {side/2, -side/2}, 
                              {side/2, side/2}, {-side/2, side/2}}) {
        cout << "Создан квадрат #" << getId() << " со стороной " << side << endl;
    }
    
    void draw() const override {
        cout << "Рисуем квадрат #" << getId() << " с центром (" << x << "," << y 
             << ") и стороной " << (vertices[1].first - vertices[0].first) << endl;
    }
    
    void hide() const override {
        cout << "Скрываем квадрат #" << getId() << endl;
    }
};

// Класс Прямоугольник
class Rectangle : public Quadrilateral {
public:
    Rectangle(double x, double y, double width, double height) 
        : Quadrilateral(x, y, {{-width/2, -height/2}, {width/2, -height/2}, 
                        {width/2, height/2}, {-width/2, height/2}}) {
        cout << "Создан прямоугольник #" << getId() << " " << width << "x" << height << endl;
    }
    
    void draw() const override {
        cout << "Рисуем прямоугольник #" << getId() << " " 
             << (vertices[1].first - vertices[0].first) << "x" 
             << (vertices[2].second - vertices[1].second) << endl;
    }
    
    void hide() const override {
        cout << "Скрываем прямоугольник #" << getId() << endl;
    }
};

// Класс Ромб
class Rhombus : public Quadrilateral {
public:
    Rhombus(double x, double y, double diagonal1, double diagonal2) 
        : Quadrilateral(x, y, {{0, -diagonal2/2}, {diagonal1/2, 0}, 
                        {0, diagonal2/2}, {-diagonal1/2, 0}}) {
        cout << "Создан ромб #" << getId() << " с диагоналями " 
             << diagonal1 << " и " << diagonal2 << endl;
    }
    
    void draw() const override {
        cout << "Рисуем ромб #" << getId() << " с диагоналями " 
             << (vertices[1].first - vertices[3].first) << " и " 
             << (vertices[2].second - vertices[0].second) << endl;
    }
    
    void hide() const override {
        cout << "Скрываем ромб #" << getId() << endl;
    }
};

// Класс Параллелограмм с виртуальным наследованием от Square
class Parallelogram : public Square, virtual public Quadrilateral {
private:
    double angle;
public:
    Parallelogram(double x, double y, double base, double height, double angle) 
        : Point(x, y), 
          Quadrilateral(x, y, calculateVertices(base, height, angle)),
          Square(x, y, base), 
          angle(angle) {
        cout << "Создан параллелограмм #" << getId() << " с основанием " << base 
             << ", высотой " << height << " и углом " << angle << " градусов" << endl;
    }
    
    void draw() const override {
        cout << "Рисуем параллелограмм #" << getId() << " с основанием " 
             << (vertices[1].first - vertices[0].first) 
             << " и углом " << this->angle << " градусов" << endl;
    }
    
    void hide() const override {
        cout << "Скрываем параллелограмм #" << getId() << endl;
    }
    
private:
    static std::vector<std::pair<double, double>> calculateVertices(double base, double height, double angle) {
        double rad = angle * PI / 180.0;
        double sideShift = height / tan(rad);
        
        return {
            {-base/2, -height/2},
            {base/2, -height/2},
            {base/2 + sideShift, height/2},
            {-base/2 + sideShift, height/2}
        };
    }
};

} // namespace Geometry

int main() {
    using namespace Geometry;

    cout << "\n=== Тестирование геометрических объектов ===" << endl;
    
    // Создание объектов
    Line line(0, 0, 10, 10);
    Square square(5, 5, 4);
    Rectangle rectangle(2, 3, 6, 4);
    Rhombus rhombus(7, 7, 8, 6);
    Parallelogram parallelogram(1, 1, 5, 3, 60);

    // Демонстрация методов
    cout << "\n=== Демонстрация методов ===" << endl;
    line.draw();
    line.move(5, 5);
    line.rotate(45);
    line.hide();

    square.draw();
    square.rotate(30);
    square.hide();

    rectangle.draw();
    rectangle.move(2, 3);
    rectangle.hide();

    rhombus.draw();
    rhombus.rotate(15);
    rhombus.hide();

    parallelogram.draw();
    parallelogram.move(1, 1);
    parallelogram.hide();

    // Демонстрация полиморфизма (позднего связывания)
    cout << "\n=== Демонстрация полиморфизма ===" << endl;
    Point* shapes[] = {&line, &square, &rectangle, &rhombus, &parallelogram};
    for (Point* shape : shapes) {
        shape->draw();
        shape->move(1, 1);
        shape->rotate(10);
        shape->hide();
        cout << "-----" << endl;
    }

    // Проверка виртуального наследования
    cout << "\n=== Проверка виртуального наследования ===" << endl;
    Parallelogram* p = &parallelogram;
    cout << "Координаты через Square: (" << p->Square::getX() << ", " << p->Square::getY() << ")" << endl;
    cout << "Координаты через Quadrilateral: (" << p->Quadrilateral::getX() << ", " << p->Quadrilateral::getY() << ")" << endl;

    return 0;
}
