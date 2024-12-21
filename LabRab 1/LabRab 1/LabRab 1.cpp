#include <iostream>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <locale>
#include <windows.h> // Для использования SetConsoleOutputCP

using namespace std;

// Базовый класс для численного интегрирования
class NumericalIntegration {
protected:
    int num_points;
    double step;
    double tolerance;

public:
    // Конструктор
    NumericalIntegration(int num_points = 1000, double step = 0.0, double tolerance = 1e-6)
        : num_points(num_points), step(step), tolerance(tolerance) {
        // Проверка корректности параметров
        if (num_points <= 0) {
            throw invalid_argument("Количество точек должно быть положительным целым числом.");
        }
        if (step <= 0 && step != 0.0) {
            throw invalid_argument("Шаг должен быть положительным числом или равен 0.");
        }
        if (tolerance <= 0) {
            throw invalid_argument("Точность должна быть положительным числом.");
        }
    }

    // Чисто виртуальный метод, который должен быть переопределен в производных классах
    virtual double Calc(double(*func)(double), double a, double b) = 0;
};

// Класс для метода трапеций
class TrapezoidalRule : public NumericalIntegration {
public:
    TrapezoidalRule(int num_points = 1000, double step = 0.0, double tolerance = 1e-6)
        : NumericalIntegration(num_points, step, tolerance) {}

    double Calc(double(*func)(double), double a, double b) override {
        // Если шаг не задан, то рассчитываем его
        if (step == 0.0) {
            step = (b - a) / num_points;
        }

        int n = static_cast<int>((b - a) / step);
        double h = (b - a) / n;
        double result = 0.5 * (func(a) + func(b));  // Начальные значения в краевых точках

        for (int i = 1; i < n; ++i) {
            result += func(a + i * h);
        }

        result *= h;
        return result;
    }
};

// Класс для метода Симпсона
class SimpsonRule : public NumericalIntegration {
public:
    SimpsonRule(int num_points = 1000, double step = 0.0, double tolerance = 1e-6)
        : NumericalIntegration(num_points, step, tolerance) {}

    double Calc(double(*func)(double), double a, double b) override {
        // Если шаг не задан, то рассчитываем его
        if (step == 0.0) {
            step = (b - a) / num_points;
        }

        int n = static_cast<int>((b - a) / step);

        // Метод Симпсона требует четного числа интервалов
        if (n % 2 == 1) {
            ++n;  // Увеличиваем количество интервалов до четного
        }

        double h = (b - a) / n;
        double result = func(a) + func(b);  // Начальные значения в краевых точках

        for (int i = 1; i < n; i += 2) {
            result += 4 * func(a + i * h);  // Коэффициент 4 для нечетных точек
        }

        for (int i = 2; i < n - 1; i += 2) {
            result += 2 * func(a + i * h);  // Коэффициент 2 для четных точек
        }

        result *= h / 3;
        return result;
    }
};

// Пример функции для интегрирования: f(x) = x^2
double test_function(double x) {
    return x * x;
}

int main() {
    try {
        // Параметры интегрирования
        double a = 0.0;  // Нижняя граница
        double b = 1.0;  // Верхняя граница

        // Пример: использование метода трапеций
        TrapezoidalRule trap(1000);
        double result_trap = trap.Calc(test_function, a, b);
        cout << "Метод Трапеций: " << result_trap << ", точность: " << abs(result_trap - 1.0 / 3) << endl;

        // Пример: использование метода Симпсона
        SimpsonRule simp(1000);
        double result_simp = simp.Calc(test_function, a, b);
        cout << "Метод Симпсона: " << result_simp << ", точность: " << abs(result_simp - 1.0 / 3) << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
