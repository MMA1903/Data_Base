#pragma once
#include "Int_cell.h"
#include "Double_cell.h"
#include "String_cell.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Data {
    static vector<vector<vector<Cell*>>> cell;
    vector<string> file_name;
    vector<string> name;
    string catalogue;
    bool catalogue_open;

public:
    Data();

    void make_Data(const string& file_name); //da

    void make_table(const string& file_name); //da

    ~Data();

    ///////////////////////////////

    void import(const string& name, const string& file_name);//da

    void showtables();//da

    void describe(const string& name);//da

    void print(const string& name);//da

    void export_table(const string& name, const string& file_name);//da

    void select(int column, const string& value, const string& table_name);//da

    void addcolumn(const string& table_name, const string& column_type);//da

    void update(const string& table_name, int search_column_n, const string& search_value, int target_column_n, const string& target_value);//da

    void delete_by_value(const string& table_name, int column_n, const string& search_value);//da

    void insert_row(const string& table_name);//da

    void innerjoin(const string& table_1, int column_n1, const string& table_2, int column_n2);

    void rename(const string& old_name, const string& new_name);//da

    void count_by_value(const string& table_name, int search_column_n, const string& search_value);//da

    void aggregate(const string& table_name, int search_column_n, const string& search_value, int target_column_n, const string& operation);//da

    ///////////////////////////////

    void save_command();

    void save_as_command(const string& file_name);

    void close_command();

    void edit_comand();

    void activate();

};

