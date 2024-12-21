#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip> // Для работы с форматированием вывода

using namespace std;

class Array3d {
private:
    int dim0, dim1, dim2;  // Размеры массива
    vector<double> data;   // Одномерный контейнер для хранения элементов

    // Функция для перевода трехмерных индексов в одномерный
    int getIndex(int i, int j, int k) const {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1 || k < 0 || k >= dim2) {
            throw out_of_range("Индексы выходят за пределы массива");
        }
        return i * dim1 * dim2 + j * dim2 + k;  // Математика для одномерного массива
    }

public:
    // Конструктор для создания массива заданных размеров
    Array3d(int d0, int d1, int d2) : dim0(d0), dim1(d1), dim2(d2), data(d0* d1* d2) {}

    // Индексатор для доступа к элементам массива по трехмерным индексам
    double& operator()(int i, int j, int k) {
        return data[getIndex(i, j, k)];
    }

    const double& operator()(int i, int j, int k) const {
        return data[getIndex(i, j, k)];
    }

    // Получение среза по первой координате
    vector<vector<double>> GetValues0(int i) const {
        if (i < 0 || i >= dim0) {
            throw out_of_range("Индекс i выходит за пределы массива");
        }
        vector<vector<double>> slice(dim1, vector<double>(dim2));
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                slice[j][k] = data[getIndex(i, j, k)];
            }
        }
        return slice;
    }

    // Получение среза по второй координате
    vector<vector<double>> GetValues1(int j) const {
        if (j < 0 || j >= dim1) {
            throw out_of_range("Индекс j выходит за пределы массива");
        }
        vector<vector<double>> slice(dim0, vector<double>(dim2));
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                slice[i][k] = data[getIndex(i, j, k)];
            }
        }
        return slice;
    }

    // Получение среза по третьей координате
    vector<vector<double>> GetValues2(int k) const {
        if (k < 0 || k >= dim2) {
            throw out_of_range("Индекс k выходит за пределы массива");
        }
        vector<vector<double>> slice(dim0, vector<double>(dim1));
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                slice[i][j] = data[getIndex(i, j, k)];
            }
        }
        return slice;
    }

    // Получение среза по первой и второй координатам
    vector<vector<double>> GetValues01(int i, int j) const {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1) {
            throw out_of_range("Индексы i или j выходят за пределы массива");
        }
        vector<double> slice(dim2);
        for (int k = 0; k < dim2; ++k) {
            slice[k] = data[getIndex(i, j, k)];
        }
        return { slice };
    }

    // Получение среза по первой и третьей координатам
    vector<vector<double>> GetValues02(int i, int k) const {
        if (i < 0 || i >= dim0 || k < 0 || k >= dim2) {
            throw out_of_range("Индексы i или k выходят за пределы массива");
        }
        vector<double> slice(dim1);
        for (int j = 0; j < dim1; ++j) {
            slice[j] = data[getIndex(i, j, k)];
        }
        return { slice };
    }

    // Получение среза по второй и третьей координатам
    vector<vector<double>> GetValues12(int j, int k) const {
        if (j < 0 || j >= dim1 || k < 0 || k >= dim2) {
            throw out_of_range("Индексы j или k выходят за пределы массива");
        }
        vector<double> slice(dim0);
        for (int i = 0; i < dim0; ++i) {
            slice[i] = data[getIndex(i, j, k)];
        }
        return { slice };
    }

    // Установка значений для среза по первой координате
    void SetValues0(int i, const vector<vector<double>>& values) {
        if (i < 0 || i >= dim0) {
            throw out_of_range("Индекс i выходит за пределы массива");
        }
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                data[getIndex(i, j, k)] = values[j][k];
            }
        }
    }

    // Установка значений для среза по второй координате
    void SetValues1(int j, const vector<vector<double>>& values) {
        if (j < 0 || j >= dim1) {
            throw out_of_range("Индекс j выходит за пределы массива");
        }
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                data[getIndex(i, j, k)] = values[i][k];
            }
        }
    }

    // Установка значений для среза по третьей координате
    void SetValues2(int k, const vector<vector<double>>& values) {
        if (k < 0 || k >= dim2) {
            throw out_of_range("Индекс k выходит за пределы массива");
        }
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                data[getIndex(i, j, k)] = values[i][j];
            }
        }
    }

    // Установка значений для среза по первой и второй координатам
    void SetValues01(int i, int j, const vector<double>& values) {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1) {
            throw out_of_range("Индексы i или j выходят за пределы массива");
        }
        for (int k = 0; k < dim2; ++k) {
            data[getIndex(i, j, k)] = values[k];
        }
    }

    // Установка значений для среза по первой и третьей координатам
    void SetValues02(int i, int k, const vector<double>& values) {
        if (i < 0 || i >= dim0 || k < 0 || k >= dim2) {
            throw out_of_range("Индексы i или k выходят за пределы массива");
        }
        for (int j = 0; j < dim1; ++j) {
            data[getIndex(i, j, k)] = values[j];
        }
    }

    // Установка значений для среза по второй и третьей координатам
    void SetValues12(int j, int k, const vector<double>& values) {
        if (j < 0 || j >= dim1 || k < 0 || k >= dim2) {
            throw out_of_range("Индексы j или k выходят за пределы массива");
        }
        for (int i = 0; i < dim0; ++i) {
            data[getIndex(i, j, k)] = values[i];
        }
    }

    // Метод для создания массива, заполненного нулями
    void zeros() {
        fill(data.begin(), data.end(), 0.0);
    }

    // Метод для создания массива, заполненного единицами
    void ones() {
        fill(data.begin(), data.end(), 1.0);
    }

    // Метод для заполнения массива заданным значением
    void fill(double value) {
        fill(data.begin(), data.end(), value);
    }

    // Метод для вывода массива (для отладки)
    void print() const {
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                for (int k = 0; k < dim2; ++k) {
                    cout << fixed << setprecision(2) << (*this)(i, j, k) << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
};

// Основная функция для тестирования класса
int main() {
    // Создание объекта Array3d размером 3x3x3
    Array3d array(3, 3, 3);

    // Заполнение массива нулями
    array.zeros();
    cout << "Массив после заполнения нулями:" << endl;
    array.print();

    // Заполнение массива единицами
    array.ones();
    cout << "Массив после заполнения единицами:" << endl;
    array.print();

    // Заполнение массива значением 5
    array.fill(5.0);
    cout << "Массив после заполнения значением 5:" << endl;
    array.print();

    // Установка значений среза
    vector<double> values = { 1.0, 2.0, 3.0 };
    array.SetValues01(1, 1, values);
    cout << "Массив после установки значений среза (i=1, j=1):" << endl;
    array.print();

    return 0;
}