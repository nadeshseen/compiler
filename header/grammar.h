#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "project_header.h"

void generate_grammar_general(string contents,map<char,production> &list_productions, vector<char> &all_non_terminals);
string import_grammar(map<char,production> &list_productions, vector<char> &all_non_terminals);
bool is_non_terminal(char ch);
bool is_string_non_terminal(string ch);

void find_all_terminals(map<char,production> list_prod, vector<char> &all_terminals, vector<char> all_non_terminals);
bool is_terminal_present(char ch, vector<char> all_terminals);

void find_first(char index, map<char,production> &list_prod);
bool add_first_to_follow(char index, map<char,production> &list_prod, vector<char> &follow_list);
void find_follow(char follow_char, map<char,production> &list_prod, vector<char> &follow_list, vector<char> all_non_terminals);

void push_char(vector<char> &arr_list,char elements);
void push_production(vector<string> &arr_list,string elements);
bool is_digit(char digit);
bool is_string_digit(string digit);


void create_augmented_grammar(map<char,production> &grammar_prod, vector<char> &all_non_terminals);
bool if_symbol_already_present(char name, map<char, production> grammar);

void find_first_of_string(string any_string, vector<char> &first_list,int k, map<char, production> augmented_grammar);

#endif // GRAMMAR_H
