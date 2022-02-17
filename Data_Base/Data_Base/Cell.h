#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Cell {

public:
	virtual void print() const = 0;

	virtual double get_value() const = 0;

	virtual const string get_string_value() = 0;

	virtual const string type_value() = 0;

};
