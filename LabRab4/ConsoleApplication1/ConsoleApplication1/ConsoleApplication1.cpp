#include <thread> //для sleep_for()
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//класс команды
class Command //класс родитель
{
protected:
    string m_name;
    bool m_undo_flag = false; //флажок для функции отмены
public:
    Command() { m_name = "Command"; };

    // virtual значит, что функция может быть переопределена в потомках
    virtual void Activation() {};
    string GetName() { return m_name; };    //геттер
    virtual void Undo() {};                 //команда отмены
};

//классы-потомки
class SpeedUp : public Command //команда увеличения скорости (с наследованием класса команда)
{
public:
    SpeedUp() : Command() { m_name = "Speed up"; };

    //override для переопределения функций
    void Activation() override { cout << "Volume Speed Increased" << endl; }
    void Undo() override { m_undo_flag = true; }    //команда отмены
};

class SpeedDown : public Command //команда уменьшения скорости (с наследованием класса команда)
{
public:
    SpeedDown() : Command() { m_name = "Speed down"; };

    //override для переопределения функций
    void Activation() override { cout << "Volume Speed Decreased" << endl; }
    void Undo() override { m_undo_flag = true; }    //команда отмены 
};

class VolumeUp : public Command //команда увеличения громкости (с наследованием класса команда)
{
public:
    VolumeUp() : Command() { m_name = "Volume up"; };

    //override для переопределения функций
    void Activation() override { cout << "Volume Level Increased" << endl; }
    void Undo() override { m_undo_flag = true; }    //команда отмены
};

class VolumeDown : public Command //команда уменьшения громкости (с наследованием класса команда)
{
public:
    VolumeDown() : Command() { m_name = "Volume down"; };

    //override для переопределения функций
    void Activation() override { cout << "Volume Level Decreased" << endl; }
    void Undo() override { m_undo_flag = true; }    //команда отмены
};

class PressCommand : public Command //команда активации (с наследованием класса команда)
{
public:
    PressCommand() : Command() { m_name = "PressCommand"; };

    //override для переопределения функций
    void Activation() override { cout << "Command activated:" << m_name << endl; }
    void Undo() override //команда отмены
    {
        cout << "Undo: " << m_name << endl;
        m_undo_flag = true;
    }
};

//класс клавиши
class Key
{
private:
    string m_name = ""; //пустые строки
    string m_com_name = "";

    Command* m_command = nullptr; //пока что пустой указатель на объект класса Command
    bool m_undo_flag = false; //флажок для отмены

public:
    Key(string name, Command* command)
    {
        m_command = command; //присваем значения
        m_name = name;
    }

    void Press() //команда активации
    {
        m_command->Activation(); //m_command указывает на объект класса Command - функцию активации 
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавливает выполнение программы на 500 миллисекунд
    }

    void KeyUndo() //команда отмены
    {
        m_command->Undo(); //m_command указывает на объект класса Command - функцию отмены
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавливает выполнение программы на 500 миллисекунд
    }

    string GetName() { return m_name; } //геттер
};

//класс клавиатуры
class KeyBoard
{
private:
    vector <Key> m_keys{}; //векторы
    vector <Key> m_log{}; //логгер

public:
    KeyBoard() {}

    void AddKey(Key key) { m_keys.push_back(key); } //заполняем вектор
    void PressKey(string key_name)
    {
        bool flag = false;
        for (int x = 0; x < m_keys.size(); x++)
        {
            if (m_keys[x].GetName() == key_name)  // проверяем, есть ли клавиша с именем key_name в векторе m_keys
                //если да, вызываем команду активации для этой клавиши
            {
                m_keys[x].Press();
                flag = true;
                m_log.push_back(m_keys[x]); //добавляем в вектор логов эту клавишу
            }
        }
        if (flag == false) { cout << "[Unable key]" << endl; } //если нет - ошибка
    }

    void Undo() // отмена команды
    {
        Key temp = m_keys[m_keys.size() - 1]; //последний элемент вектора клавиши
        cout << "[Undo command]: " << temp.GetName() << endl; //сообщение об отмене  команды
        temp.KeyUndo(); //отмена команды
        m_log.pop_back(); //убираем последний элемент из вектора логов
    }

    void ActiveCommands() //красивый вывод в консоль
    {
        cout << "\033[38;5;122m" << endl; //перекрашиваем текст, чтоб было красиво
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавка программы на 500 миллисекунд
        //выводим активные команады
        cout << endl;
        cout << "________________________________________________________________________________________________________________________";
        cout << "Active commands: " << endl;
        for (int c = 0; c < m_log.size(); c++) //выводим из вектора логов
        {
            cout << m_log[c].GetName() << endl;
        }
        cout << endl;
        cout << "________________________________________________________________________________________________________________________";
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавка программы на 500 миллисекунд
        cout << "\033[0m" << endl;//перекрашиваем текст обратно
    }
};


int main()
{
    KeyBoard test;

    //пример 1
    SpeedUp s1; //увеличиваем скорость
    // VolumeDown s1; //уменьшаем громкость
    string example1_ = "EXP 1";
    Key example1(example1_, &s1);
    test.AddKey(example1); //добавляем клавишу


    test.PressKey("EXP 1"); //активация
    test.PressKey("EXP 1"); //повторная активация
    test.ActiveCommands();  //смотрим какие команды активны

    test.Undo(); //отмена
    test.ActiveCommands(); //смотрим какие команды активны
    test.PressKey("EXP 1");//повторная активация

    //пример 2 
    //VolumeUp s2; //увеличиваем громкость
    SpeedDown s2; //понижаем скорость
    string example2_ = "EXP 2";
    Key second(example2_, &s2);
    test.AddKey(second);//добавляем клавишу
    test.PressKey("EXP 2"); //активация
    test.ActiveCommands(); //смотрим какие команды активны