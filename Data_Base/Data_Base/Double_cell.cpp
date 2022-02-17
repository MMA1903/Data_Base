#include "Double_cell.h"
#include "String_cell.h"

Double_cell::Double_cell()
{
    this->value = "NULL";

}

Double_cell::Double_cell(string value)
{
    this->value = value;
}

double Double_cell::get_value() const
{
    return string_to_double(this->value);
}

void Double_cell::print() const
{
    cout << this->value;
}

const string Double_cell::get_string_value()
{
    return this->value;
}

const string Double_cell::type_value()
{
    return "double";
}
