#include "Int_cell.h"
#include "String_cell.h"


Int_cell::Int_cell()
{
    this->value = "NULL";

}

Int_cell::Int_cell(string value)
{
    this->value = value;
}

double Int_cell::get_value() const
{
    return string_to_double(this->value);
}

void Int_cell::print() const
{
    cout << this->value;
}

const string Int_cell::get_string_value()
{
    return this->value;
}

const string Int_cell::type_value()
{
    return "int";
}
