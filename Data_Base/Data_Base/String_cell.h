#pragma once

#include "Cell.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class String_cell : public Cell
{
    string value;
public:
    String_cell();

    String_cell(string value);

    double get_value() const;

    void print() const;

    const string get_string_value();

    const string type_value();

};

double string_to_double(const string& str);
