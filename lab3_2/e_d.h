#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <UnitTest++/UnitTest++.h>
using namespace std;

class e_d
{
private:
    int num_of_columns;
    string getValidKey(vector<char>& key);
    string getValidText(string& stroka);
    int getValid_num_of_columns(int key, string& stroka);
public:
    e_d(vector<char> key);
    e_d() = delete;
    string encrypt(string stroka);
    string decrypt(string stroka);
};


