#include "e_d.h"

// Конструктор
e_d::e_d(vector<char> key) {
    num_of_columns = stoi(getValidKey(key));
}

// Метод шифрования
string e_d::encrypt(string old_stroka)
{
	if (old_stroka.empty())
		return "";
    string stroka = getValidText(old_stroka);
    string end_stroka;
    int s = stroka.length();
    
    int n_of_c = getValid_num_of_columns(num_of_columns, stroka);
    
    int num_of_lines = ceil(double(s) / n_of_c);
    char table[num_of_lines][n_of_c] = {' '};
    int k = 0;

    for (int i = 0; i < num_of_lines; ++i) {
        for (int j = 0; j < n_of_c; ++j) {
            if (k < s) {
                table[i][j] = stroka[k++];
            }
        }
    }

    for (int i = n_of_c - 1; i >= 0; --i) {
        for (int j = 0; j < num_of_lines; ++j) {
            end_stroka += table[j][i];
        }
    }
    return end_stroka;
}

// Метод расшифрования
string e_d::decrypt(string old_stroka)
{
	if (old_stroka.empty())
		return "";
    string stroka = getValidText(old_stroka);
    int len_s = stroka.length();
    int n_k_d = len_s;
    string end_stroka;
    
    int n_of_c = getValid_num_of_columns(num_of_columns, stroka);
    
    int num_of_lines = ceil(double(len_s) / n_of_c);
    char table[num_of_lines][n_of_c];
    int string_with_spaces = num_of_lines - 1;
    int k1 = 0;
    int k2 = 0;
    
    while (n_k_d % n_of_c != 0) 
        n_k_d++;

    for (int j = n_of_c - 1; j >= 0; --j) {
        if (k1 < n_k_d - len_s) {
            table[string_with_spaces][j] = ' ';
            k1++;
        } else {
            break;
        }
    }

    for (int j = n_of_c - 1; j >= 0; --j) {
        for (int i = 0; i < num_of_lines; ++i) {
            if (k2 < len_s && table[i][j] != ' ') {
                table[i][j] = stroka[k2++];
            }
        }
    }

    for (int i = 0; i < num_of_lines; ++i) {
        for (int j = 0; j < n_of_c; ++j) {
            end_stroka += table[i][j];
        }
    }
    return end_stroka;
}

// Метод для получения валидного ключа
string e_d::getValidKey(vector<char>& key) {
    string validKey;
    string new_validKey;
    for (char c : key)
        validKey += c;

    while (true) {
        new_validKey.clear();
        for (char c : validKey) {
            if (isdigit(c))
                new_validKey += c;
        }
        if (new_validKey.empty()) {
            cout << "Ключ пустой, либо не является числом" << "\nКлюч = ";
            getline(cin, validKey);
            continue;
        } else {
            break;
        }
    }
    return new_validKey;
}

bool isSymbolAllowed(char symbol) {
    string allowedSymbols = "[]{}qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789+-*\\";
    for (char c : allowedSymbols) {
        if (symbol == c)
            return true;
    }
    return false;
}

string e_d::getValidText(string& stroka) {
    string result = "";
    for (char c : stroka) {
        if (isSymbolAllowed(c) == true) 
            result += c;
    }
    return result;
}

int e_d::getValid_num_of_columns(int n_of_c, string& stroka) {
    int len_of_stroka = stroka.length();
    if (len_of_stroka <= n_of_c)
        n_of_c = ceil(len_of_stroka / 2); // ключ равен половине длины строки
        
    if (ceil(len_of_stroka / n_of_c) > 100) // если строка во много раз превышает длину ключа
        n_of_c = ceil(len_of_stroka / 2);
    return n_of_c;
}
