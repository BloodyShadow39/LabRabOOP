#pragma once
#include <iostream>
#include "contr.hpp"
using namespace std;

//класс родитель
class AbstrFactory 
{
public:
    virtual Control* CreateForm() = 0; //создание формы 
    virtual Control* CreateLabel() = 0; //создание лейбла
    virtual Control* CreateTextBox() = 0; //создание текста

    virtual ~AbstrFactory() = default; //деструктор
};

//android fabric (потомок с наследованием AbstractFabric)
class AndroidFactory : public AbstrFactory 
{
public:
    Control* CreateForm() override 
    {
        cout << "Created Form for Android" << endl;
        return new AndForm();
    }

    Control* CreateLabel() override
    {
        cout << "Created Label for Android" << endl;
        return new AndLabel();
    }

    Control* CreateTextBox() override
    {
        cout << "Created TextBox for Android" << endl;
        return new AndTextBox();
    }
};

//Windows fabric (потомок с наследованием AbstractFabric)
class WindowsFactory : public AbstrFactory
{
public:
    Control* CreateForm() override
    {
        cout << "Created Form for Windows" << endl;
        return new WinForm();
    }

    Control* CreateLabel() override
    {
        cout << "Created Label for Windows" << endl;
        return new WinLabel();
    }

    Control* CreateTextBox() override
    {
        cout << "Created TextBox for Windows" << endl;
        return new WinTextBox();
    }

};

//Linux fabric (потомок с наследованием AbstractFabric)
class LinuxFactory : public AbstrFactory
{
public:
    Control* CreateForm() override
    {
        cout << "Created Form for Linux" << endl;
        return new LinForm();
    }

    Control* CreateLabel() override
    {
        cout << "Created Label for Linux" << endl;
        return new LinLabel();
    }

    Control* CreateTextBox() override
    {
        cout << "Created TextBox for Linux" << endl;
        return new LinTextBox();
    }
};