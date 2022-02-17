#include "String_cell.h"


String_cell::String_cell()
{
    this->value = "NULL";
}

String_cell::String_cell(string value)
{
    this->value = value;
}

double String_cell::get_value() const
{
    return string_to_double(this->value);
}

void String_cell::print() const
{
    cout << this->value;
}

const string String_cell::get_string_value()
{
    return this->value;
}

const string String_cell::type_value()
{
    return "string";
}

double string_to_double(const string& str)
{
    bool is_string = false;
    int br_dots = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) == '.')
        {
            br_dots++;
        }
        if ((('0' <= str.at(i) && str.at(i) <= '9') || str.at(i) == '.' || str.at(i) == '+' || str.at(i) == '-') && br_dots <= 1)
        {

        }
        else
        {
            is_string = true;
            break;
        }
    }

    if (is_string == true)
    {
        return 0;
    }
    else
    {
        return stod(str);
    }

}
