#include <iostream>
#include <vector>
#include "contr.hpp"
#include "fact.hpp"


int main()
{
    //Linux
    AbstrFactory* lin_factory = nullptr;
    lin_factory = new LinuxFactory();   //создаем linux factory
    Control* lin_form = lin_factory->CreateForm(); //создаем форму
    Control* lin_label = lin_factory->CreateLabel(); //создаем лейбл
    Control* lin_textbox = lin_factory->CreateTextBox(); //создаем текст

    lin_form->SetPosition(34, 90); //задаем позиции
    lin_form->GetPosition();
    //добавляем контроль
    if (dynamic_cast<Form*>(lin_form) != nullptr)
    {
        Form* formControl = dynamic_cast<Form*>(lin_form); formControl->AddControl(lin_label);
    }

    dynamic_cast<Label*>(lin_label)->SetText("something"); //задаем текст
    dynamic_cast<Label*>(lin_label)->GetText();

    dynamic_cast<TextBox*>(lin_textbox)->OnValueChanged(); //изменяем значение

    //удаляем все
    delete lin_form;
    delete lin_label;
    delete lin_textbox;

    delete lin_factory;
}