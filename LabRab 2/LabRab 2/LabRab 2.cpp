#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip> // Для настройки вывода (точности)

// Класс для представления точки в 3D пространстве
class Point {
public:
    double x, y, z;

    // Конструктор
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    // Методы для получения координат
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Вывод точки
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

// Класс для представления вектора в 3D пространстве
class Vector {
public:
    double x, y, z;

    // Конструкторы
    Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    // Конструктор, который создаёт вектор из двух точек
    Vector(const Point& p1, const Point& p2) {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        z = p2.z - p1.z;
    }

    // Методы для получения координат вектора
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Метод для вычисления длины вектора
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Операция сложения векторов
    Vector operator+(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    // Операция вычитания векторов
    Vector operator-(const Vector& v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    // Операция инвертирования вектора (умножение на -1)
    Vector operator-() const {
        return Vector(-x, -y, -z);
    }

    // Операция скалярного произведения
    double dot(const Vector& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Операция векторного произведения
    Vector cross(const Vector& v) const {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Метод для вычисления угла между векторами (в радианах)
    double angleWith(const Vector& v) const {
        double dotProduct = this->dot(v);
        double lengths = this->length() * v.length();
        if (lengths == 0) return 0; // Защита от деления на ноль
        return acos(dotProduct / lengths);
    }

    // Метод для вычисления смешанного произведения
    double mixedProduct(const Vector& v1, const Vector& v2) const {
        return this->dot(v1.cross(v2));
    }

    // Проверка на коллинеарность
    bool isCollinear(const Vector& v) const {
        Vector crossProduct = this->cross(v);
        return crossProduct.length() == 0;
    }

    // Проверка на компланарность (если векторное произведение равно 0, то они компланарны)
    bool isCoplanar(const Vector& v1, const Vector& v2) const {
        return mixedProduct(v1, v2) == 0;
    }

    // Нахождение расстояния между точками
    static double distance(const Point& p1, const Point& p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
    }

    // Вывод вектора
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

// Основная программа с консольным интерфейсом
int main() {
    setlocale(LC_ALL, "Russian");
    try {
        double x1, y1, z1, x2, y2, z2;
        std::cout << "Введите координаты первой точки (x1, y1, z1): ";
        std::cin >> x1 >> y1 >> z1;
        Point p1(x1, y1, z1);

        std::cout << "Введите координаты второй точки (x2, y2, z2): ";
        std::cin >> x2 >> y2 >> z2;
        Point p2(x2, y2, z2);

        Vector v1(p1, p2);  // Вектор от p1 до p2

        // Ввод второй точки для второго вектора
        std::cout << "Введите координаты третьей точки (x3, y3, z3): ";
        std::cin >> x1 >> y1 >> z1;
        Point p3(x1, y1, z1);
        Vector v2(p2, p3);  // Вектор от p2 до p3

        // Меню операций
        int choice;
        while (true) {
            std::cout << "\nВыберите операцию:\n";
            std::cout << "1. Сложение векторов\n";
            std::cout << "2. Вычитание векторов\n";
            std::cout << "3. Инвертирование вектора\n";
            std::cout << "4. Длина вектора\n";
            std::cout << "5. Скалярное произведение\n";
            std::cout << "6. Векторное произведение\n";
            std::cout << "7. Угол между векторами\n";
            std::cout << "8. Проверка на коллинеарность\n";
            std::cout << "9. Проверка на компланарность\n";
            std::cout << "10. Расстояние между точками\n";
            std::cout << "0. Выход\n";
            std::cout << "Ваш выбор: ";
            std::cin >> choice;

            if (choice == 0) break;

            switch (choice) {
            case 1: {
                Vector result = v1 + v2;
                std::cout << "Сумма векторов: ";
                result.print();
                break;
            }
            case 2: {
                Vector result = v1 - v2;
                std::cout << "Разность векторов: ";
                result.print();
                break;
            }
            case 3: {
                Vector result = -v1;
                std::cout << "Инвертированный вектор: ";
                result.print();
                break;
            }
            case 4:
                std::cout << "Длина первого вектора: " << v1.length() << std::endl;
                std::cout << "Длина второго вектора: " << v2.length() << std::endl;
                break;
            case 5:
                std::cout << "Скалярное произведение: " << v1.dot(v2) << std::endl;
                break;
            case 6: {
                Vector result = v1.cross(v2);
                std::cout << "Векторное произведение: ";
                result.print();
                break;
            }
            case 7:
                std::cout << "Угол между векторами (в радианах): " << v1.angleWith(v2) << std::endl;
                break;
            case 8:
                if (v1.isCollinear(v2)) {
                    std::cout << "Вектора коллинеарны." << std::endl;
                }
                else {
                    std::cout << "Вектора не коллинеарны." << std::endl;
                }
                break;
            case 9:
                if (v1.isCoplanar(v1, v2)) {
                    std::cout << "Вектора компланарны." << std::endl;
                }
                else {
                    std::cout << "Вектора не компланарны." << std::endl;
                }
                break;
            case 10:
                std::cout << "Расстояние между точками: " << Vector::distance(p1, p2) << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}