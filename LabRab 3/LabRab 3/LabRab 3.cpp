#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class Array3d {
private:
    std::vector<double> data;  // Один массив для хранения данных
    int dim0, dim1, dim2;      // Размерности массива

    // Преобразование трёхмерных индексов в одномерный
    int getIndex(int i, int j, int k) const {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1 || k < 0 || k >= dim2) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return (i * dim1 * dim2) + (j * dim2) + k;
    }

public:
    // Конструктор для создания массива с заданными размерами
    Array3d(int dim0, int dim1, int dim2)
        : dim0(dim0), dim1(dim1), dim2(dim2), data(dim0* dim1* dim2, 0.0) {}

    // Индексатор для доступа к элементам массива
    double& operator()(int i, int j, int k) {
        return data[getIndex(i, j, k)];
    }

    // Получить значение среза по первой координате
    std::vector<std::vector<double>> GetValues0(int i) {
        if (i < 0 || i >= dim0) throw std::out_of_range("Индекс по первой координате вне диапазона");
        std::vector<std::vector<double>> slice(dim1, std::vector<double>(dim2));
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                slice[j][k] = (*this)(i, j, k);
            }
        }
        return slice;
    }

    // Получить значение среза по второй координате
    std::vector<std::vector<double>> GetValues1(int j) {
        if (j < 0 || j >= dim1) throw std::out_of_range("Индекс по второй координате вне диапазона");
        std::vector<std::vector<double>> slice(dim0, std::vector<double>(dim2));
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                slice[i][k] = (*this)(i, j, k);
            }
        }
        return slice;
    }

    // Получить значение среза по третьей координате
    std::vector<std::vector<double>> GetValues2(int k) {
        if (k < 0 || k >= dim2) throw std::out_of_range("Индекс по третьей координате вне диапазона");
        std::vector<std::vector<double>> slice(dim0, std::vector<double>(dim1));
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                slice[i][j] = (*this)(i, j, k);
            }
        }
        return slice;
    }

    // Срез по первой и второй координате
    std::vector<std::vector<double>> GetValues01(int i, int j) {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1)
            throw std::out_of_range("Индекс по первой или второй координате вне диапазона");
        std::vector<double> slice(dim2);
        for (int k = 0; k < dim2; ++k) {
            slice[k] = (*this)(i, j, k);
        }
        return { slice };
    }

    // Срез по первой и третьей координате
    std::vector<std::vector<double>> GetValues02(int i, int k) {
        if (i < 0 || i >= dim0 || k < 0 || k >= dim2)
            throw std::out_of_range("Индекс по первой или третьей координате вне диапазона");
        std::vector<double> slice(dim1);
        for (int j = 0; j < dim1; ++j) {
            slice[j] = (*this)(i, j, k);
        }
        return { slice };
    }

    // Срез по второй и третьей координате
    std::vector<std::vector<double>> GetValues12(int j, int k) {
        if (j < 0 || j >= dim1 || k < 0 || k >= dim2)
            throw std::out_of_range("Индекс по второй или третьей координате вне диапазона");
        std::vector<double> slice(dim0);
        for (int i = 0; i < dim0; ++i) {
            slice[i] = (*this)(i, j, k);
        }
        return { slice };
    }

    // Установка значений для среза по первой координате
    void SetValues0(int i, const std::vector<std::vector<double>>& slice) {
        if (i < 0 || i >= dim0) throw std::out_of_range("Индекс по первой координате вне диапазона");
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                (*this)(i, j, k) = slice[j][k];
            }
        }
    }

    // Установка значений для среза по второй координате
    void SetValues1(int j, const std::vector<std::vector<double>>& slice) {
        if (j < 0 || j >= dim1) throw std::out_of_range("Индекс по второй координате вне диапазона");
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                (*this)(i, j, k) = slice[i][k];
            }
        }
    }

    // Установка значений для среза по третьей координате
    void SetValues2(int k, const std::vector<std::vector<double>>& slice) {
        if (k < 0 || k >= dim2) throw std::out_of_range("Индекс по третьей координате вне диапазона");
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                (*this)(i, j, k) = slice[i][j];
            }
        }
    }

    // Установка значений для среза по первой и второй координате
    void SetValues01(int i, int j, const std::vector<double>& slice) {
        if (i < 0 || i >= dim0 || j < 0 || j >= dim1)
            throw std::out_of_range("Индекс по первой или второй координате вне диапазона");
        for (int k = 0; k < dim2; ++k) {
            (*this)(i, j, k) = slice[k];
        }
    }

    // Установка значений для среза по первой и третьей координате
    void SetValues02(int i, int k, const std::vector<double>& slice) {
        if (i < 0 || i >= dim0 || k < 0 || k >= dim2)
            throw std::out_of_range("Индекс по первой или третьей координате вне диапазона");
        for (int j = 0; j < dim1; ++j) {
            (*this)(i, j, k) = slice[j];
        }
    }

    // Установка значений для среза по второй и третьей координате
    void SetValues12(int j, int k, const std::vector<double>& slice) {
        if (j < 0 || j >= dim1 || k < 0 || k >= dim2)
            throw std::out_of_range("Индекс по второй или третьей координате вне диапазона");
        for (int i = 0; i < dim0; ++i) {
            (*this)(i, j, k) = slice[i];
        }
    }

    // Методы для заполнения массива значениями
    void fill(double value) {
        std::fill(data.begin(), data.end(), value);
    }

    void fillWithOnes() {
        fill(1.0);
    }

    void fillWithZeros() {
        fill(0.0);
    }

    // Вывод массива
    void print() const {
        for (int i = 0; i < dim0; ++i) {
            std::cout << "Срез по первой координате " << i << ":\n";
            for (int j = 0; j < dim1; ++j) {
                for (int k = 0; k < dim2; ++k) {
                    std::cout << (*this)(i, j, k) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Array3d arr(3, 3, 3);

    // Заполним массив единицами
    arr.fillWithOnes();

    arr.print();

    // Доступ через индексатор
    arr(1, 1, 1) = 5.0;
    std::cout << "После изменения элемента (1, 1, 1):\n";
    arr.print();

    // Получение срезов
    auto slice = arr.GetValues0(1);
    std::cout << "Срез по первой координате (i=1):\n";
    for (const auto& row : slice) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}