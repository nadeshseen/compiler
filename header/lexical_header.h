#ifndef LEXICAL_H
#define LEXICAL_H

#include <iostream>
#include <vector>

#include <iomanip>
using namespace std;
int lexical();

bool check_in(vector<string> arr,string check);
bool is_digit(char check);
bool is_hexa(char check);
bool is_octal(char check);
//operators
bool is_operator(string char_check);
bool is_arth_operator(string char_check);
bool is_assign_operator(string char_check,int size);
bool is_comparison(string str_check,int size);
bool is_inc_dec_op(string char_check);
bool is_logical(string str_check,int size);
bool is_bitwise(string str_check);
bool is_pointer_check(string str_check);


bool is_separator(string char_check);
bool is_keyword(string str_check);

//constants
bool is_constant(string str_check);
bool is_integer_constant(string str_check);
bool is_real_constant(string str_check);
bool is_string_constant(string str_check);
bool is_char_constant(string str_check);

bool is_identifier(string str_check);


vector<string> get_tokens(string s);

#endif
