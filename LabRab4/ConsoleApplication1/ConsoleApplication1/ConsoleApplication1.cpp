#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <thread>
#include <chrono>

using namespace std;

// Класс для виртуальной клавиатуры
class VirtualKeyboard {
public:
    // Тип для действия, связанного с клавишей
    using Action = std::function<void()>;

    // Добавление переназначаемой клавиши с действием
    void assignKey(char key, Action action) {
        keyBindings[key] = action;
    }

    // Выполнение действия для клавиши
    void pressKey(char key) {
        if (keyBindings.find(key) != keyBindings.end()) {
            keyBindings[key]();
            actionHistory.push_back([this, key]() { undoKeyPress(key); });  // Сохранить для отката
        }
        else {
            cout << "No action assigned to key '" << key << "'" << endl;
        }
    }

    // Откат последнего действия
    void undoLastAction() {
        if (!actionHistory.empty()) {
            actionHistory.back()(); // Выполняем функцию отката
            actionHistory.pop_back();
        }
        else {
            cout << "No actions to undo!" << endl;
        }
    }

    // Перезапуск Workflow (сброс действий и истории)
    void resetWorkflow() {
        actionHistory.clear();
        cout << "Workflow reset!" << endl;
    }

    // Демонстрация нажатий клавиш с задержками
    void simulateKeyPresses(const vector<char>& keys) {
        for (char key : keys) {
            pressKey(key);
            this_thread::sleep_for(chrono::milliseconds(500));  // Задержка между нажатиями
        }
    }

private:
    // Словарь для переназначения клавиш
    unordered_map<char, Action> keyBindings;

    // История выполненных действий для отката
    vector<std::function<void()>> actionHistory;

    // Откат действия для клавиши
    void undoKeyPress(char key) {
        cout << "Undo action for key: " << key << endl;
    }
};

int main() {
    VirtualKeyboard keyboard;

    // Назначаем действия для клавиш
    keyboard.assignKey('A', []() { cout << "Action for A\n"; });
    keyboard.assignKey('B', []() { cout << "Action for B\n"; });
    keyboard.assignKey('C', []() { cout << "Action for C\n"; });

    // Демонстрация работы клавиатуры с симуляцией нажатий
    vector<char> sequence = { 'A', 'B', 'C', 'A', 'B' };
    cout << "Simulating key presses:\n";
    keyboard.simulateKeyPresses(sequence);

    // Откат последнего действия
    cout << "\nUndoing last action:\n";
    keyboard.undoLastAction();

    // Сброс Workflow
    cout << "\nResetting workflow:\n";
    keyboard.resetWorkflow();

    // Переназначаем клавишу
    cout << "\nReassigning key 'A' to a new action:\n";
    keyboard.assignKey('A', []() { cout << "New action for A\n"; });

    // Перезапускаем Workflow с новыми назначениями
    sequence = { 'A', 'B', 'C' };
    cout << "Simulating key presses after reassignment:\n";
    keyboard.simulateKeyPresses(sequence);

    return 0;
}
