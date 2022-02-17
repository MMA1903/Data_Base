#include "Data.h"



vector<vector<vector<Cell*>>>Data::cell{};

Data::Data()
{
    Data::cell;
    vector<string>file_name{};
    vector<string>name{};
    string catalogue = "";
    bool catalogue_open = false;
}

void Data::make_Data(const string& catalogue) //raboti
{
    string line = "";

    ifstream my_file(catalogue);
    this->catalogue = catalogue;
    if (my_file.is_open())
    {
        while (getline(my_file, line))
        {
            string name_ = "";
            string file_name_ = "";
            int index = 0;
            bool first = false;

            while (index <= line.size())
            {
                if (first == false)
                {
                    if (line[index] != ' ')
                    {
                        name_ = name_ + line[index];
                    }
                    else
                    {
                        first = true;
                    }
                }
                else
                {
                    file_name_ = file_name_ + line[index];
                }
                index++;
            }
            this->name.push_back(name_);
            this->file_name.push_back(file_name_);
        }
        my_file.close();
        cout << "Successfully opened : " << catalogue << endl;
        catalogue_open = true;
    }
    else
    {
        ofstream outfile(catalogue);
        cout << "You create new file " << catalogue << endl;
        my_file.close();
        catalogue_open = true;
    }

    for (int i = 0; i < file_name.size(); i++)
    {
        Data::make_table(file_name[i]);
    }
}

void Data::make_table(const string& file_name) //raboti
{
    vector<vector<string>> cell_helper;
    vector<string> column;
    vector<string> data_type;
    string line = "";
    string value = "";
    bool have_type = false;

    int br_commas = 0;

    ifstream my_file(file_name);

    while (getline(my_file, line))
    {
        br_commas = 0;
        int index = 0;

        while (index <= line.size())
        {
            if (line[index] == ',')
            {
                br_commas++;
            }
            index++;
        }

        if (have_type == false)
        {
            int i = 0;
            for (int j = 0; j < br_commas; j++)
            {
                value = "";
                while (line[i] != ',')
                {
                    value = value + line[i];
                    i++;
                }
                i++;
                data_type.push_back(value);
            }
            have_type = true;
        }

        else if (have_type == true)
        {
            int i = 0;
            for (int j = 0; j < br_commas; j++)
            {
                value = "";
                while (line[i] != ',')
                {
                    value = value + line[i];
                    i++;
                }
                i++;
                column.push_back(value);
            }
            cell_helper.push_back(column);
            column.clear();
        }
    }

    int max_row = cell_helper.size();
    int max_column = 0;

    for (int i = 0; i < cell_helper.size(); i++)
    {
        if (cell_helper[i].size() > max_column)
        {
            max_column = cell_helper[i].size();
        }
    }

    vector<vector<Cell*>> table{};
    vector<Cell*> column_str{};

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_column; j++)
        {
            column_str.push_back(new String_cell());
        }
        table.push_back(column_str);
        column_str.clear();
    }

    for (int j = 0; j < cell_helper[0].size(); j++)
    {
        if (data_type[j] == "string")
        {
            for (int n = 0; n < cell_helper.size(); n++)
            {
                delete table[n][j];

                if (cell_helper[n][j] == "NULL" || cell_helper[n][j] == " ")
                {
                    table[n][j] = new String_cell();
                }
                else
                {
                    table[n][j] = new String_cell(cell_helper[n][j]);
                }
            }
        }

        else if (data_type[j] == "double")
        {
            for (int n = 0; n < cell_helper.size(); n++)
            {
                delete table[n][j];

                if (cell_helper[n][j] == "NULL" || cell_helper[n][j] == " ")
                {
                    table[n][j] = new Double_cell();
                }
                else
                {
                    table[n][j] = new Double_cell(cell_helper[n][j]);
                }
            }
        }

        else if (data_type[j] == "int")
        {
            for (int n = 0; n < cell_helper.size(); n++)
            {
                delete table[n][j];

                if (cell_helper[n][j] == "NULL" || cell_helper[n][j] == " ")
                {
                    table[n][j] = new Int_cell();
                }
                else
                {
                    table[n][j] = new Int_cell(cell_helper[n][j]);
                }
            }
        }
    }
    Data::cell.push_back(table);
}

Data::~Data()
{
    for (int i = 0; i < Data::cell.size(); i++)
    {
        for (int j = 0; j < Data::cell[i].size(); j++)
        {
            for (int d = 0; d < Data::cell[i][j].size(); d++)
            {
                delete Data::cell[i][j][d];
            }
            Data::cell[i][j].clear();
        }
        Data::cell[i].clear();
    }
    Data::cell.clear();

    this->file_name.clear();
    this->name.clear();
    this->catalogue = "";
    this->catalogue_open = false;
}

///////////////////////////////

void Data::import(const string& name, const string& file_name)//da
{
    bool matches = false;

    for (int i = 0; i < name.size(); i++)
    {
        if (this->name[i] == name)
        {
            matches = true;
        }
        if (this->file_name[i] == file_name)
        {
            matches = true;
        }
    }

    if (matches == false && catalogue_open == true)
    {
        this->name.push_back(name);
        this->file_name.push_back(file_name);
        Data::make_table(file_name);

        ofstream my_file(catalogue);
        if (my_file.good())
        {
            for (int i = 0; i < Data::name.size(); i++)
            {
                my_file << this->name[i];
                my_file << " ";
                my_file << this->file_name[i];
                my_file << " ";
                my_file << "\n";
            }
        }
        my_file.close();
    }
    else if (catalogue_open == false)
    {
        cout << "Error : no file opened." << endl;
    }
    else
    {
        cout << "ERROR there is file with name :: " << name << " // or file name :: " << file_name << endl;
    }
}

void Data::showtables()//da
{
    for (int i = 0; i < this->name.size(); i++)
    {
        cout << this->name[i] << endl;
    }
}

void Data::describe(const string& name)//da
{
    int index = 0;
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == name)
        {
            index = i;
        }
    }
    for (int j = 0; j < Data::cell[index][0].size(); j++)
    {
        cout << Data::cell[index][0][j]->type_value() << " ";
    }
    cout << endl;
}

void Data::print(const string& name)//da
{
    int index = 0;
    string next = "";

    for (int i = 0; i < name.size(); i++)
    {
        if (this->name[i] == name)
        {
            index = i;
        }
    }
    int top = 6;

    int maxl = 0;
    for (int i = 0; i < Data::cell[index].size(); i++)
    {
        for (int j = 0; j < Data::cell[index][i].size(); j++)
        {
            if (Data::cell[index][i][j]->get_string_value().length() > maxl)
            {
                maxl = Data::cell[index][i][j]->get_string_value().length();
            }
        }
    }

    while (index != -1)
    {
        for (int j = 0; j < Data::cell[index].size(); j++)
        {
            for (int d = top - 6; d < top && d < Data::cell[index][j].size(); d++)
            {
                cout << setw(maxl);
                Data::cell[index][j][d]->print();
                cout << setw(2);
                cout << "|";
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "next , before or close :: ";
        cin >> next;
        cout << endl;
        cout << endl;

        if (next == "close")
        {
            break;
        }
        else if (next == "next")
        {
            if (Data::cell[index][0].size() <= top)
            {
                cout << " !!! no pages next !!! " << endl << endl;
            }
            else
            {
                top = top + 6;
            }
        }
        else if (next == "before")
        {
            if (top == 6)
            {
                cout << " !!! no pages before !!! " << endl << endl;
            }
            else
            {
                top = top - 6;
            }
        }
    }
}

void Data::export_table(const string& name, const string& file_name)//da
{
    int index = 0;

    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == name)
        {
            index = i;
        }
    }

    ofstream my_file(file_name);
    if (my_file.good())
    {
        for (int j = 0; j < Data::cell[index][0].size(); j++)
        {
            my_file << Data::cell[index][0][j]->type_value();
            my_file << ",";
        }
        my_file << "\n";

        for (int i = 0; i < Data::cell[index].size(); i++)
        {
            for (int j = 0; j < Data::cell[index][i].size(); j++)
            {
                my_file << Data::cell[index][i][j]->get_string_value();
                my_file << ",";
            }
            my_file << "\n";
        }
    }
    my_file.close();
}

void Data::select(int column, const string& value, const string& table_name)//da
{
    int index = 0;
    string next = "";

    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }
    int top = 6;

    int maxl = 0;
    for (int i = 0; i < Data::cell[index].size(); i++)
    {
        for (int j = 0; j < Data::cell[index][i].size(); j++)
        {
            if (Data::cell[index][i][j]->get_string_value().length() > maxl)
            {
                maxl = Data::cell[index][i][j]->get_string_value().length();
            }
        }
    }

    while (index != -1)
    {
        for (int j = 0; j < Data::cell[index].size(); j++)
        {
            if (Data::cell[index][j][column - 1]->get_string_value() == value)
            {
                for (int d = top - 6; d < top && d < Data::cell[index][j].size(); d++)
                {
                    cout << setw(maxl);
                    Data::cell[index][j][d]->print();
                    cout << setw(2);
                    cout << "|";
                    cout << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
        cout << "next , before or close :: ";
        cin >> next;
        cout << endl;
        cout << endl;

        if (next == "close")
        {
            break;
        }
        else if (next == "next")
        {
            if (Data::cell[index][0].size() <= top)
            {
                cout << " !!! no pages next !!! " << endl << endl;
            }
            else
            {
                top = top + 6;
            }
        }
        else if (next == "before")
        {
            if (top == 6)
            {
                cout << " !!! no pages before !!! " << endl << endl;
            }
            else
            {
                top = top - 6;
            }
        }
    }


}

void Data::addcolumn(const string& table_name, const string& column_type)//da
{
    int index = 0;
    string next = "";

    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }
    for (int j = 0; j < Data::cell[index].size(); j++)
    {
        if (column_type == "string")
        {
            Data::cell[index][j].push_back(new String_cell());
        }

        else if (column_type == "double")
        {
            Data::cell[index][j].push_back(new Double_cell());

        }

        else if (column_type == "int")
        {
            Data::cell[index][j].push_back(new Int_cell());
        }
    }
}

void Data::update(const string& table_name, int search_column_n, const string& search_value, int target_column_n, const string& target_value)//da
{
    int index = 0;
    string next = "";

    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }

    for (int j = 0; j < Data::cell[index].size(); j++)
    {
        if (Data::cell[index][j][search_column_n - 1]->get_string_value() == search_value)
        {
            string type = "";
            type = Data::cell[index][j][target_column_n - 1]->type_value();

            delete Data::cell[index][j][target_column_n - 1];
            if (type == "string")
            {
                Data::cell[index][j][target_column_n - 1] = new String_cell(target_value);
            }
            else if (type == "double")
            {
                Data::cell[index][j][target_column_n - 1] = new Double_cell(target_value);
            }
            else if (type == "int")
            {
                Data::cell[index][j][target_column_n - 1] = new Int_cell(target_value);
            }
        }
    }
}

void Data::delete_by_value(const string& table_name, int column_n, const string& search_value)//da
{
    int index = 0;
    string next = "";
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }

    vector<string> type{};
    int loop = Data::cell[index].size();
    for (int j = 0; j < loop; j++)
    {
        if (Data::cell[index][j][column_n - 1]->get_string_value() == search_value)
        {
            if (j != Data::cell[index].size() - 1)
            {
                for (int d = 0; d < Data::cell[index][j].size(); d++)
                {
                    type.push_back(cell[index][j][d]->type_value());
                    delete Data::cell[index][j][d];

                }
                for (int m = j; m < Data::cell[index].size() - 1; m++)
                {
                    for (int n = 0; n < Data::cell[index][m].size(); n++)
                    {
                        if (type[n] == "string")
                        {
                            Data::cell[index][m][n] = new String_cell(Data::cell[index][m + 1][n]->get_string_value());
                            delete Data::cell[index][m + 1][n];
                        }
                        else if (type[n] == "double")
                        {
                            Data::cell[index][m][n] = new Double_cell(Data::cell[index][m + 1][n]->get_string_value());
                            delete Data::cell[index][m + 1][n];
                        }
                        else if (type[n] == "int")
                        {
                            Data::cell[index][m][n] = new Int_cell(Data::cell[index][m + 1][n]->get_string_value());
                            delete Data::cell[index][m + 1][n];
                        }
                    }
                }
                Data::cell[index][Data::cell[index].size() - 1].clear();
                type.clear();
            }
            else
            {
                for (int d = 0; d < Data::cell[index][j].size(); d++)
                {
                    delete Data::cell[index][j][d];
                }
                Data::cell[index][Data::cell[index].size() - 1].clear();
            }
            loop = loop - 1;
            Data::cell[index].resize(loop);
            j = -1;
        }
    }
}

void Data::insert_row(const string& table_name)//da
{
    int index = 0;
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }

    string value = "";
    Data::cell[index].resize(Data::cell[index].size() + 1);

    for (int i = 0; i < Data::cell[index][0].size(); i++)
    {
        cout << Data::cell[index][0][i]->type_value() << "--->";
        cin >> value;
        if (Data::cell[index][0][i]->type_value() == "string")
        {
            Data::cell[index][Data::cell[index].size() - 1].push_back(new String_cell(value));
        }
        else if (Data::cell[index][0][i]->type_value() == "double")
        {
            Data::cell[index][Data::cell[index].size() - 1].push_back(new Double_cell(value));

        }
        else if (Data::cell[index][0][i]->type_value() == "int")
        {
            Data::cell[index][Data::cell[index].size() - 1].push_back(new Int_cell(value));
        }
    }
}

void Data::innerjoin(const string& table_1, int column_n1, const string& table_2, int column_n2)
{
    int index_1 = 0;
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_1)
        {
            index_1 = i;
        }
    }
    int index_2 = 0;
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_2)
        {
            index_2 = i;
        }
    }

    Data::cell.resize(Data::cell.size() + 1);
    Data::cell[Data::cell.size()].resize(Data::cell[index_1].size());

    for (int i = 0; i < Data::cell[index_1].size(); i++)
    {
        if (Data::cell[index_1][i][column_n1]->type_value() == "string")
        {
            Data::cell[Data::cell.size()][i].push_back(new String_cell(Data::cell[index_1][i][column_n1]->get_string_value()));
        }
        else if (Data::cell[index_1][i][column_n1]->type_value() == "double")
        {
            Data::cell[Data::cell.size()][i].push_back(new Double_cell(Data::cell[index_1][i][column_n1]->get_string_value()));

        }
        else if (Data::cell[index_1][i][column_n1]->type_value() == "int")
        {
            Data::cell[Data::cell.size()][i].push_back(new Int_cell(Data::cell[index_1][i][column_n1]->get_string_value()));
        }

        if (Data::cell[index_2][i][column_n2]->type_value() == "string")
        {
            Data::cell[Data::cell.size()][i].push_back(new String_cell(Data::cell[index_2][i][column_n2]->get_string_value()));
        }
        else if (Data::cell[index_2][i][column_n2]->type_value() == "double")
        {
            Data::cell[Data::cell.size()][i].push_back(new Double_cell(Data::cell[index_2][i][column_n2]->get_string_value()));

        }
        else if (Data::cell[index_2][i][column_n2]->type_value() == "int")
        {
            Data::cell[Data::cell.size()][i].push_back(new Int_cell(Data::cell[index_2][i][column_n2]->get_string_value()));
        }
    }
    string file_new_ = "new.txt";
    string new_ = "new";
    for (int j = 0; j < this->name.size(); j++)
    {
        for (int i = 0; i < this->name.size(); i++)
        {
            if (name[i] == new_)
            {
                file_new_ = 'n' + 'e' + 'w' + i + '.' + 't' + 'x' + 't';
                new_ = 'n' + 'e' + 'w' + i;

            }

        }
    }
    cout << "file_name ::" << file_new_ << endl;
    cout << "Table name ::" << new_ << endl;
    this->file_name.push_back(file_new_);
    this->name.push_back(new_);
}

void Data::rename(const string& old_name, const string& new_name)//da
{
    bool unique_name = true;
    int index = 0;
    for (int i = 0; i < name.size(); i++)
    {
        if (new_name == name[i])
        {
            unique_name = false;
        }

        if (old_name == name[i])
        {
            index = i;
        }
    }

    if (unique_name == true)
    {
        name[index] = new_name;
    }
    else
    {
        cout << "New name is not unique" << endl;
    }
}

void Data::count_by_value(const string& table_name, int search_column_n, const string& search_value)//da
{
    int br = 0;
    int index = 0;
    string next = "";
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }

    for (int i = 0; i < Data::cell[index].size(); i++)
    {
        if (Data::cell[index][i][search_column_n - 1]->get_string_value() == search_value)
        {
            br++;
        }
    }
    cout << "Counted :: " << br << endl;
}

void Data::aggregate(const string& table_name, int search_column_n, const string& search_value, int target_column_n, const string& operation)//da
{
    int index = 0;
    vector<int> target_row;
    for (int i = 0; i < this->name.size(); i++)
    {
        if (this->name[i] == table_name)
        {
            index = i;
        }
    }
    if (Data::cell[index][0][search_column_n - 1]->type_value() != "string" && Data::cell[index][0][target_column_n - 1]->type_value() != "string")
    {
        for (int j = 0; j < Data::cell[index].size(); j++)
        {
            if (Data::cell[index][j][search_column_n - 1]->get_string_value() == search_value)
            {
                target_row.push_back(j);
            }
        }

        if (operation == "sum")
        {
            double sum = 0;
            for (int d = 0; d < target_row.size(); d++)
            {
                sum = sum + Data::cell[index][target_row[d]][target_column_n - 1]->get_value();
            }
            cout << "Sum ::" << sum << endl;
        }
        else if (operation == "maximum")
        {
            double max_value = Data::cell[index][0][target_column_n - 1]->get_value();
            for (int d = 0; d < target_row.size(); d++)
            {
                if (max_value < Data::cell[index][target_row[d]][target_column_n - 1]->get_value())
                {
                    max_value = Data::cell[index][target_row[d]][target_column_n - 1]->get_value();
                }
            }
            cout << "MAX ::" << max_value << endl;
        }
        else if (operation == "minimum")
        {
            double min_value = Data::cell[index][0][target_column_n - 1]->get_value();
            for (int d = 0; d < target_row.size(); d++)
            {
                if (min_value > Data::cell[index][target_row[d]][target_column_n - 1]->get_value())
                {
                    min_value = Data::cell[index][target_row[d]][target_column_n - 1]->get_value();
                }
            }
            cout << "MIN ::" << min_value << endl;
        }
        else if (operation == "product")
        {
            for (int d = 0; d < target_row.size(); d++)
            {
                cout << target_row[d] << " :: " << Data::cell[index][target_row[d]][target_column_n - 1]->get_value() << endl;
            }
        }
    }
    else
    {
        cout << "Error :: column type string " << endl;
    }
}

///////////////////////////////

void Data::save_command()
{
    if (catalogue_open == true)
    {
        ofstream my_file(catalogue);
        if (my_file.good())
        {
            for (int i = 0; i < Data::name.size(); i++)
            {
                my_file << this->name[i];
                my_file << " ";
                my_file << this->file_name[i];
                my_file << " ";
                my_file << "\n";
            }
        }
        my_file.close();

        int index = 0;

        for (int i = 0; i < this->file_name.size(); i++)
        {
            index = i;
            ofstream my_file(this->file_name[i]);
            if (my_file.good())
            {
                for (int j = 0; j < Data::cell[index][0].size(); j++)
                {
                    my_file << Data::cell[index][0][j]->type_value();
                    my_file << ",";
                }
                my_file << "\n";

                for (int i = 0; i < Data::cell[index].size(); i++)
                {
                    for (int j = 0; j < Data::cell[index][i].size(); j++)
                    {
                        my_file << Data::cell[index][i][j]->get_string_value();
                        my_file << ",";
                    }
                    my_file << "\n";
                }
            }
            my_file.close();
        }

    }
    else if (catalogue_open == false)
    {
        cout << "Error : no file opened." << endl;
    }
}

void Data::save_as_command(const string& file_name)
{
    if (catalogue_open == true)
    {
        ofstream my_file(file_name);
        if (my_file.good())
        {
            for (int i = 0; i < Data::name.size(); i++)
            {
                my_file << this->name[i];
                my_file << " ";
                my_file << this->file_name[i];
                my_file << " ";
                my_file << "\n";
            }
        }
        my_file.close();

        int index = 0;

        for (int i = 0; i < this->file_name.size(); i++)
        {
            index = i;
            ofstream my_file(this->file_name[i]);
            if (my_file.good())
            {
                for (int j = 0; j < Data::cell[index][0].size(); j++)
                {
                    my_file << Data::cell[index][0][j]->type_value();
                    my_file << ",";
                }
                my_file << "\n";

                for (int i = 0; i < Data::cell[index].size(); i++)
                {
                    for (int j = 0; j < Data::cell[index][i].size(); j++)
                    {
                        my_file << Data::cell[index][i][j]->get_string_value();
                        my_file << ",";
                    }
                    my_file << "\n";
                }
            }
            my_file.close();
        }

    }
    else if (catalogue_open == false)
    {
        cout << "Error : no file opened." << endl;
    }
}

void Data::close_command()
{
    if (catalogue_open == true)
    {
        cout << "File \"" << this->catalogue << "\" closed." << endl;
        this->~Data();
    }
    else
    {
        cout << "Error : no file opened." << endl;
    }

}

void Data::activate()
{
    const string exit = R"(^exit$)";
    const string open = R"(^open (([^\"\s]+)|(\"([^\"]+)\"))$)";
    const string save = R"(^save$)";
    const string saveas = R"(^saveas (([^\"\s]+)|(\"([^\"]+)\"))$)";
    const string close = R"(^close$)";
    const string help = R"(^help$)";

    const string  import = R"(^import$)";
    const string  showtables = R"(^showtables$)";
    const string  describe = R"(^describe$)";
    const string  print = R"(^print$)";
    const string  export_table = R"(^export$)";
    const string  select = R"(^select$)";
    const string  addcolumn = R"(^addcolumn$)";
    const string  update = R"(^update$)";
    const string  delete_by_value = R"(^delete$)";
    const string  insert_row = R"(^insert$)";
    const string  innerjoin = R"(^innerjoin$)";
    const string  rename = R"(^rename$)";
    const string  count_by_value = R"(^count$)";
    const string  aggregate = R"(^aggregate$)";


    const sregex_iterator end;


    ///////////////////////////////

    const regex exit_pattern = regex(exit);
    const regex open_pattern = regex(open);
    const regex save_pattern = regex(save);
    const regex saveas_attern = regex(saveas);
    const regex close_pattern = regex(close);
    const regex help_pattern = regex(help);

    const regex  import_pattern = regex(import);
    const regex  showtables_pattern = regex(showtables);
    const regex  describe_pattern = regex(describe);
    const regex  print_pattern = regex(print);
    const regex  export_table_pattern = regex(export_table);
    const regex  select_pattern = regex(select);
    const regex  addcolumn_pattern = regex(addcolumn);
    const regex  update_pattern = regex(update);
    const regex  delete_by_value_pattern = regex(delete_by_value);
    const regex  insert_row_pattern = regex(insert_row);
    const regex  innerjoin_pattern = regex(innerjoin);
    const regex  rename_pattern = regex(rename);
    const regex  count_by_value_pattern = regex(count_by_value);
    const regex  aggregate_pattern = regex(aggregate);

    sregex_iterator iter;

    ///////////////////////////////

    string text;
    while (true)
    {
        cout << ">";
        getline(cin, text);

        if ((iter = sregex_iterator(text.begin(), text.end(), exit_pattern)) != end)
        {
            cout << "exiting..." << endl;
            break;
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), help_pattern)) != end)
        {
            cout << "ALL VALID COMMANDS" << endl;

            cout << "help" << endl;
            cout << "open" << endl;
            cout << "save" << endl;
            cout << "saveas" << endl;
            cout << "close" << endl;
            cout << "exit" << endl << endl;

            cout << "import" << endl;
            cout << "showtables" << endl;
            cout << "describe" << endl;
            cout << "print" << endl;
            cout << "export" << endl;
            cout << "select" << endl;
            cout << "addcolumn" << endl;
            cout << "update" << endl;
            cout << "delete" << endl;
            cout << "insert" << endl;
            cout << "innerjoin" << endl;
            cout << "rename" << endl;
            cout << "count" << endl;
            cout << "aggregate" << endl;
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), open_pattern)) != end)
        {
            string file_name = string((*iter)[2]) + string((*iter)[4]);
            this->make_Data(file_name);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), save_pattern)) != end)
        {
            this->save_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), saveas_attern)) != end)
        {
            string file_name = string((*iter)[2]) + string((*iter)[4]);
            this->save_as_command(file_name);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), close_pattern)) != end)
        {
            this->close_command();
        }

        else if ((iter = sregex_iterator(text.begin(), text.end(), import_pattern)) != end)
        {
            string a = "";
            string b = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "File name :: ";
            cin >> b;
            cout << endl;
            this->import(a, b);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), showtables_pattern)) != end)
        {
            this->showtables();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), describe_pattern)) != end)
        {
            string a = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            this->describe(a);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), print_pattern)) != end)
        {
            string a = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            this->print(a);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), export_table_pattern)) != end)
        {
            string a = "";
            string b = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "File name :: ";
            cin >> b;
            cout << endl;
            this->export_table(a, b);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), select_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            cout << "Column :: ";
            cin >> a;
            cout << endl;
            cout << "Value :: ";
            cin >> b;
            cout << endl;
            cout << "Table name :: ";
            cin >> c;
            cout << endl;
            this->select(string_to_double(a), b, c);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), addcolumn_pattern)) != end)
        {
            string a = "";
            string b = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Column type :: ";
            cin >> b;
            cout << endl;
            this->addcolumn(a, b);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), update_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            string d = "";
            string e = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Search column number :: ";
            cin >> b;
            cout << endl;
            cout << "Search value :: ";
            cin >> c;
            cout << endl;
            cout << "Target column number :: ";
            cin >> d;
            cout << endl;
            cout << "Target value :: ";
            cin >> e;
            cout << endl;
            this->update(a, string_to_double(b), c, string_to_double(d), e);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), delete_by_value_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Column number :: ";
            cin >> b;
            cout << endl;
            cout << "Search value :: ";
            cin >> c;
            cout << endl;
            this->delete_by_value(a, string_to_double(b), c);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), insert_row_pattern)) != end)
        {
            string a = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            this->insert_row(a);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), innerjoin_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            string d = "";
            cout << "First Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Search column number :: ";
            cin >> b;
            cout << endl;
            cout << "Second Table name :: ";
            cin >> c;
            cout << endl;
            cout << "Search column number :: ";
            cin >> d;
            cout << endl;
            this->innerjoin(a, string_to_double(b), c, string_to_double(d));
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), rename_pattern)) != end)
        {
            string a = "";
            string b = "";
            cout << "Old Table name :: ";
            cin >> a;
            cout << endl;
            cout << "New Table name :: ";
            cin >> b;
            cout << endl;
            this->rename(a, b);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), count_by_value_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Search column number :: ";
            cin >> b;
            cout << endl;
            cout << "Search value :: ";
            cin >> c;
            cout << endl;
            this->count_by_value(a, string_to_double(b), c);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), aggregate_pattern)) != end)
        {
            string a = "";
            string b = "";
            string c = "";
            string d = "";
            string e = "";
            cout << "Table name :: ";
            cin >> a;
            cout << endl;
            cout << "Search column number :: ";
            cin >> b;
            cout << endl;
            cout << "Search value :: ";
            cin >> c;
            cout << endl;
            cout << "Target column number :: ";
            cin >> d;
            cout << endl;
            cout << "Operation :: ";
            cin >> e;
            cout << endl;
            this->aggregate(a, string_to_double(b), c, string_to_double(d), e);
        }
        else if (text == "" || text == "\n")
        {

        }
        else
        {
            cout << "Error : invalid command syntax." << endl;
        }
        cout << endl;
    }
}
