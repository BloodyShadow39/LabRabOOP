#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <stack>

using namespace std;

// Класс для представления действия, выполняемого на клавише
class KeyboardAction {
public:
    virtual void execute() = 0;  // Виртуальный метод для выполнения действия
    virtual string getName() const = 0;  // Возвращает имя действия
    virtual ~KeyboardAction() = default;
};

// Пример конкретного действия - Печать текста
class PrintTextAction : public KeyboardAction {
private:
    string text;
public:
    PrintTextAction(const string& text) : text(text) {}

    void execute() override {
        cout << text << endl;
    }

    string getName() const override {
        return "PrintTextAction: " + text;
    }
};

// Пример действия для выхода из программы
class ExitAction : public KeyboardAction {
public:
    void execute() override {
        cout << "Выход из программы..." << endl;
        exit(0);  // Прерывание программы
    }

    string getName() const override {
        return "ExitAction";
    }
};

// Класс для управления историей действий (откат действий)
class ActionHistory {
private:
    stack<KeyboardAction*> history;  // Стек выполненных действий
    stack<KeyboardAction*> undone;   // Стек отменённых действий

public:
    ~ActionHistory() {
        // Освобождение памяти
        while (!history.empty()) {
            delete history.top();
            history.pop();
        }
        while (!undone.empty()) {
            delete undone.top();
            undone.pop();
        }
    }

    void addAction(KeyboardAction* action) {
        history.push(action);
        while (!undone.empty()) {
            // Очистить стек отменённых действий при новом действии
            delete undone.top();
            undone.pop();
        }
    }

    void undo() {
        if (!history.empty()) {
            // Переносим действие в стек отменённых
            KeyboardAction* action = history.top();
            history.pop();
            undone.push(action);
            cout << "Отмена действия: " << action->getName() << endl;
        }
        else {
            cout << "Нет действий для отмены!" << endl;
        }
    }

    void redo() {
        if (!undone.empty()) {
            // Переносим действие обратно в основной стек
            KeyboardAction* action = undone.top();
            undone.pop();
            history.push(action);
            cout << "Повторное выполнение действия: " << action->getName() << endl;
            action->execute();  // Выполняем повторно
        }
        else {
            cout << "Нет действий для повторного выполнения!" << endl;
        }
    }
};

// Класс для виртуальной клавиатуры
class Keyboard {
private:
    unordered_map<string, KeyboardAction*> keyBindings;  // Переназначенные клавиши
    ActionHistory history;  // История действий
    bool isRunning;  // Признак работы клавиатуры

public:
    Keyboard() : isRunning(true) {}

    ~Keyboard() {
        // Освобождение памяти от переназначенных действий
        for (auto& binding : keyBindings) {
            delete binding.second;
        }
    }

    // Метод для назначения действия на клавишу
    void bindKey(const string& key, KeyboardAction* action) {
        // Освобождение старого действия для клавиши
        if (keyBindings.find(key) != keyBindings.end()) {
            delete keyBindings[key];
        }
        keyBindings[key] = action;
    }

    // Метод для симуляции нажатия клавиши
    void pressKey(const string& key) {
        if (keyBindings.find(key) != keyBindings.end()) {
            cout << "Нажата клавиша: " << key << endl;
            keyBindings[key]->execute();
            history.addAction(keyBindings[key]);  // Сохраняем действие в историю
        }
        else {
            cout << "Не назначено действие для клавиши: " << key << endl;
        }
    }

    // Метод для выполнения отката
    void undoLastAction() {
        history.undo();
    }

    // Метод для выполнения повторного действия (redo)
    void redoLastAction() {
        history.redo();
    }

    // Метод для симуляции выполнения workflow
    void runWorkflow(const vector<string>& workflow) {
        for (const auto& key : workflow) {
            pressKey(key);
            // Задержка между нажатиями клавиш (симуляция реального времени)
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    // Метод для завершения работы клавиатуры
    void stop() {
        isRunning = false;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание клавиатуры
    Keyboard keyboard;

    // Создание действий
    KeyboardAction* printHello = new PrintTextAction("Hello, world!");
    KeyboardAction* printGoodbye = new PrintTextAction("Goodbye, world!");
    KeyboardAction* exitAction = new ExitAction();

    // Назначение действий клавишам
    keyboard.bindKey("A", printHello);
    keyboard.bindKey("B", printGoodbye);
    keyboard.bindKey("X", exitAction);

    // Симуляция workflow: последовательности нажатий клавиш
    vector<string> workflow = { "A", "B", "X" };
    cout << "Начало Workflow:" << endl;
    keyboard.runWorkflow(workflow);

    // Демонстрация отката действия
    cout << "Откат последнего действия:" << endl;
    keyboard.undoLastAction();

    // Демонстрация повторного выполнения действия
    cout << "Повторное выполнение последнего действия:" << endl;
    keyboard.redoLastAction();

    // Переназначение клавиш
    cout << "Переназначение клавиш:" << endl;
    keyboard.bindKey("A", new PrintTextAction("New Action for A"));
    keyboard.runWorkflow({ "A", "B", "X" });

    return 0;
}