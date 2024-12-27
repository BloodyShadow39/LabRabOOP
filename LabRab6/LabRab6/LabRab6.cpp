#include <iostream>
#include <vector>
#include <string>

// Абстрактный базовый класс Control
class Control {
protected:
    int x, y; // Позиция контролла на форме
public:
    virtual void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
        std::cout << "Вызван метод setPosition у контролла " << typeid(*this).name() << " на позиции (" << x << ", " << y << ")" << std::endl;
    }

    virtual void getPosition() {
        std::cout << "Вызван метод getPosition у контролла " << typeid(*this).name() << " на позиции (" << x << ", " << y << ")" << std::endl;
    }

    virtual ~Control() = default;
};

// Конкретные контроллы

// Form (форма)
class Form : public Control {
public:
    virtual void display() {
        std::cout << "Отображение формы" << std::endl;
    }
};

// Label (метка)
class Label : public Control {
private:
    std::string text;
public:
    virtual void setText(const std::string& text) {
        this->text = text;
        std::cout << "Вызван метод setText у контролла Label: " << text << std::endl;
    }

    virtual void getText() {
        std::cout << "Вызван метод getText у контролла Label: " << text << std::endl;
    }

    virtual void display() {
        std::cout << "Отображение метки: " << text << std::endl;
    }
};

// TextBox (текстовое поле)
class TextBox : public Control {
private:
    std::string text;
public:
    virtual void setText(const std::string& text) {
        this->text = text;
        std::cout << "Вызван метод setText у контролла TextBox: " << text << std::endl;
    }

    virtual void getText() {
        std::cout << "Вызван метод getText у контролла TextBox: " << text << std::endl;
    }

    virtual void OnValueChanged() {
        std::cout << "Вызван метод OnValueChanged у контролла TextBox, новый текст: " << text << std::endl;
    }

    virtual void display() {
        std::cout << "Отображение текстового поля: " << text << std::endl;
    }
};

// ComboBox (выпадающий список)
class ComboBox : public Control {
private:
    std::vector<std::string> items;
    int selectedIndex = -1;
public:
    virtual void setItems(const std::vector<std::string>& items) {
        this->items = items;
        std::cout << "Вызван метод setItems у контролла ComboBox" << std::endl;
    }

    virtual void getItems() {
        std::cout << "Вызван метод getItems у контролла ComboBox: ";
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    virtual void setSelectedIndex(int index) {
        if (index >= 0 && index < items.size()) {
            selectedIndex = index;
            std::cout << "Вызван метод setSelectedIndex у контролла ComboBox, выбранный индекс: " << selectedIndex << std::endl;
        }
    }

    virtual int getSelectedIndex() {
        std::cout << "Вызван метод getSelectedIndex у контролла ComboBox, выбранный индекс: " << selectedIndex << std::endl;
        return selectedIndex;
    }

    virtual void display() {
        std::cout << "Отображение выпадающего списка с элементами: ";
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Button (кнопка)
class Button : public Control {
private:
    std::string text;
public:
    virtual void setText(const std::string& text) {
        this->text = text;
        std::cout << "Вызван метод setText у контролла Button: " << text << std::endl;
    }

    virtual void getText() {
        std::cout << "Вызван метод getText у контролла Button: " << text << std::endl;
    }

    virtual void Click() {
        std::cout << "Вызван метод Click у контролла Button, текст кнопки: " << text << std::endl;
    }

    virtual void display() {
        std::cout << "Отображение кнопки: " << text << std::endl;
    }
};

// Абстрактная фабрика
class AbstractFactory {
public:
    virtual Form* createForm() = 0;
    virtual Label* createLabel() = 0;
    virtual TextBox* createTextBox() = 0;
    virtual ComboBox* createComboBox() = 0;
    virtual Button* createButton() = 0;
    virtual ~AbstractFactory() = default;
};

// Конкретные фабрики

// Windows Factory
class WindowsFactory : public AbstractFactory {
public:
    Form* createForm() override {
        std::cout << "Создан контрол Form для Windows" << std::endl;
        return new Form();
    }

    Label* createLabel() override {
        std::cout << "Создан контрол Label для Windows" << std::endl;
        return new Label();
    }

    TextBox* createTextBox() override {
        std::cout << "Создан контрол TextBox для Windows" << std::endl;
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        std::cout << "Создан контрол ComboBox для Windows" << std::endl;
        return new ComboBox();
    }

    Button* createButton() override {
        std::cout << "Создан контрол Button для Windows" << std::endl;
        return new Button();
    }
};

// Linux Factory
class LinuxFactory : public AbstractFactory {
public:
    Form* createForm() override {
        std::cout << "Создан контрол Form для Linux с необычным оформлением" << std::endl;
        return new Form();
    }

    Label* createLabel() override {
        std::cout << "Создан контрол Label для Linux с уникальным шрифтом" << std::endl;
        return new Label();
    }

    TextBox* createTextBox() override {
        std::cout << "Создан контрол TextBox для Linux с поддержкой многоточия" << std::endl;
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        std::cout << "Создан контрол ComboBox для Linux с иную разметкой" << std::endl;
        return new ComboBox();
    }

    Button* createButton() override {
        std::cout << "Создан контрол Button для Linux с отличной анимацией" << std::endl;
        return new Button();
    }
};

// MacOS Factory
class MacOSFactory : public AbstractFactory {
public:
    Form* createForm() override {
        std::cout << "Создан контрол Form для MacOS с макетом по умолчанию" << std::endl;
        return new Form();
    }

    Label* createLabel() override {
        std::cout << "Создан контрол Label для MacOS с современным стилем" << std::endl;
        return new Label();
    }

    TextBox* createTextBox() override {
        std::cout << "Создан контрол TextBox для MacOS с поддержкой эмодзи" << std::endl;
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        std::cout << "Создан контрол ComboBox для MacOS с красивыми переходами" << std::endl;
        return new ComboBox();
    }

    Button* createButton() override {
        std::cout << "Создан контрол Button для MacOS с стильным дизайном" << std::endl;
        return new Button();
    }
};

// Клиентский код
int main() {
    setlocale(LC_ALL, "Russian");
    AbstractFactory* factory;

    // Выбор операционной системы
    std::string os;
    std::cout << "Выберите операционную систему (Windows/Linux/MacOS): ";
    std::cin >> os;

    // Создаем нужную фабрику
    if (os == "Windows") {
        factory = new WindowsFactory();
    }
    else if (os == "Linux") {
        factory = new LinuxFactory();
    }
    else if (os == "MacOS") {
        factory = new MacOSFactory();
    }
    else {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }

    // Создание контроллов через выбранную фабрику
    Form* form = factory->createForm();
    Label* label = factory->createLabel();
    TextBox* textBox = factory->createTextBox();
    ComboBox* comboBox = factory->createComboBox();
    Button* button = factory->createButton();

    // Размещение контроллов на форме
    form->display();
    label->display();
    textBox->display();
    comboBox->display();
    button->display();

    // Манипуляции с контроллами
    label->setText("Hello, World!");
    textBox->setText("Sample Text");
    comboBox->setItems({ "Option 1", "Option 2", "Option 3" });
    comboBox->setSelectedIndex(1);
    button->setText("Click Me");
    button->Click();

    // Завершаем работу
    delete factory;
    return 0;
}