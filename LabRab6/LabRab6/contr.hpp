#pragma once
using namespace std;

//РОДИТЕЛЬСКИЙ КЛАСС
class Control 
{
protected:
    pair<int, int> m_pos;
public:
    virtual ~Control() = default; //деструктор
    //virtual для переопределения в потомках
    virtual void SetPosition(int x, int y) { m_pos = { x, y }; }; //задаем позиции
    virtual pair<int, int> GetPosition() const { return m_pos; }; //вектор-геттер позиций
};

//потомок с наследованием контрол
class Form : public Control
{
protected:
    Control* m_control = nullptr; //пустной указатель на объект класса контрол
public:
    virtual void AddControl(Control* control) { m_control = control; } //добавление
};
//потомок с наследованием контрол ВИНДОУС
class WinForm : public Form 
{
public:
    void AddControl(Control* control) override //добавление (override для переопределения функций)
    {
        Form::AddControl(control); //определяем функцию добавления
        cout << "Added control in WinForm" << endl;
    }

    void SetPosition(int x, int y) override //сеттер позиций
    {
        Control::SetPosition(x, y);
        cout << "Setted position for WinForm" << endl;
    }

    pair<int, int> GetPosition() const override //геттер позиций
    {
        cout << "Got position from WinForm" << endl;
        return Control::GetPosition();
    }
};

//потомок с наследованием контрол ЛИНУКС
class LinForm : public Form 
{
public:
    void AddControl(Control* control) override
    {
        Form::AddControl(control);
        cout << "Added control in LinForm" << endl;
    }

    void SetPosition(int x, int y) override
    {
        Control::SetPosition(x, y);
        cout << "Setted position for LinForm" << endl;
    }

    pair<int, int> GetPosition() const override
    {
        cout << "Got position from LinForm" << endl; 
        return Control::GetPosition();
    }
};

//потомок с наследованием контрол АНДРОИД
class AndForm : public Form 
{
public:
    void AddControl(Control* control) override 
    {
        Form::AddControl(control);
        cout << "Added control in AndForm" << endl;
    }

    void SetPosition(int x, int y) override
    {
        Control::SetPosition(x, y);
        cout << "Setted position for AndForm" << endl;
    }

    pair<int, int> GetPosition() const override 
    {
        cout << "Got position from AndForm" << endl;
        return Control::GetPosition();
    }
};

//ЛЕЙБЛ
//потомок с наследованием класса контрол
class Label : public Control 
{
protected:
    string m_name; //строка с текстом
public:
    virtual void SetText(const string& text) { m_name = text; } //сеттер текста
    virtual string GetText() const { return m_name; } //геттер текста
};

//потомок с наследованием лейбла ВИНДОУС
class WinLabel : public Label 
{
public:
    void SetText(const string& text) override  //сеттер текста
    {
        Label::SetText(text); //определяем сеттер текста
        cout << "Setted text for WinLabel" << endl;
    }

    void SetPosition(int x, int y) override  //сеттер
    {
        Control::SetPosition(x, y); //определяем сеттер позиций
        cout << "Setted position for WinLabel" << endl;
    }

    string GetText() const override  //геттер
    {
        cout << "Got text from WinLabel" << endl;
        return Label::GetText();
    }

    pair<int, int> GetPosition() const override //геттер
    {
        cout << "Got position from WinLabel" << endl;
        return Control::GetPosition();
    }
};

//потомок с наследованием лейбла ЛИНУКС
class LinLabel : public Label 
{
public:
    void SetText(const string& text) override 
    {
        Label::SetText(text);
        cout << "Setted text for  LinLabel" << endl;
    }

    void SetPosition(int x, int y) override 
    {
        Control::SetPosition(x, y);
        cout << "Setted position for  LinLabel" << endl;
    }

    string GetText() const override 
    {
        cout << "Got text from  LinLabel" << endl;
        return Label::GetText();
    }

    pair<int, int> GetPosition() const override 
    {
        cout << "Got position from  LinLabel" << endl;
        return Control::GetPosition();
    }
};

//потомок с наследованием лейбла АНДРОИД
class AndLabel : public Label 
{
public:
    
    void SetText(const string& text) override 
    {
        Label::SetText(text);
        cout << "Setted text for AndLabel" << endl;
    }

    void SetPosition(int x, int y) override 
    {
        Control::SetPosition(x, y);
        cout << "Setted position for AndLabel" << endl;
    }

    string GetText() const override 
    {
        cout << "Got text from AndLabel" << endl;
        return Label::GetText();
    }

    pair<int, int> GetPosition() const override {
        cout << "Got position from AndLabel" << endl;
        return Control::GetPosition();
    }
};

//ТЕКСТ
//потомок с наследованием контрол
class TextBox : public Control 
{
protected:
    string m_text; 
    bool m_changed = false;
public:
    virtual void OnValueChanged() {m_changed = !m_changed; } //изменение значения
    virtual void SetText(const string& text)   {m_text = text;} //сеттер текстбокса
    virtual string GetText() const { return m_text;} //геттер текста
};

//потомок с наследованием текстбокс ВИНДОУС
class WinTextBox : public TextBox
{
public:
    void OnValueChanged() override //изменение значения
    {
        TextBox::OnValueChanged(); //определяем функцию изменения значения
        cout << "OnValueChanged from WinTextBox" << endl;
    }

    void SetText(const string& text) override //сеттер текста
    {
        TextBox::SetText(text); //определяем сеттер текста
        cout << "Setted text for WinTextBox" << endl;
    }

    void SetPosition(int x, int y) override //сеттер позиций
    {
        Control::SetPosition(x, y); //определяем сеттер позиций
        cout << "Setted position for WinTextBox" << endl;
    }
    
    pair<int, int> GetPosition() const override //геттер позиций
    {
        cout << "Got position from WinTextBox" << endl;
        return Control::GetPosition();
    }

    string GetText() const override //геттер текста
    {
        cout << "Got text from WinTextBox" << endl;
        return TextBox::GetText();
    }
};

//потомок с наследованием текстбокс ЛИНУКС
class LinTextBox : public TextBox 
{
public:
    void OnValueChanged() override 
    {
        TextBox::OnValueChanged();
        cout << "OnValueChanged from LinTextBox" << endl;
    }

    void SetText(const string& text) override 
    {
        TextBox::SetText(text);
        cout << "Setted text for LinTextBox" << endl;
    }

    void SetPosition(int x, int y) override 
    {
        Control::SetPosition(x, y);
        cout << "Setted position for LinTextBox" << endl;
    }
    
    pair<int, int> GetPosition() const override
    {
        cout << "Got position from LinTextBox" << endl;
        return TextBox::GetPosition();
    }

    string GetText() const override
    {
        cout << "Got text from LinTextBox" << endl;
        return TextBox::GetText();
    }
};

//потомок с наследованием текстбокс АНДРОИД
class AndTextBox : public TextBox
{
public:
    void OnValueChanged() override 
    {
        TextBox::OnValueChanged();
        cout << "OnValueChanged from AndTextBox" << endl;
    }

    void SetText(const string& text) override 
    {
        TextBox::SetText(text);
        cout << "Setted text for AndTextBox" << endl;
    }

    void SetPosition(int x, int y) override 
    {
        Control::SetPosition(x, y);
        cout << "Setted position for AndTextBox" << endl;
    }
    
    pair<int, int> GetPosition() const override 
    {
        cout << "Got position from AndTextBox" << endl;
        return TextBox::GetPosition();
    }

    string GetText() const override
    {
        cout << "Got text from AndTextBox" << endl;
        return TextBox::GetText();
    }
};