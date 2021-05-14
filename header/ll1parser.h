#ifndef LL1_PARSER_H
#define LL1_PARSER_H

//#include"project_header.h"
#include "grammar.h"

using namespace std;


int grammar();

//void generate_grammar(string contents,map<char,production> &list_productions, vector<char> &all_non_terminals);
//bool is_non_terminal(char ch);
//int find_production(char ch, map<char,production> &list_prod);



bool is_present(char ch, vector<vector<string>> list);
void left_factoring(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
void eliminate_left_recursion(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
void eliminate_non_immediate_left_recursion(map<char,production> &list_prod, vector<char> &all_non_terminals);



void construct_LL1_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_non_terminals);

void construct_blank_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_terminals, vector<char> all_non_terminals);


bool parse_string(string parsing_str, map<char,map<char,vector<string>>> table, char start_symbol);



bool left_factoring2(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
bool eliminate_non_immediate_left_recursion2(map<char,production> &list_prod, vector<char> &all_non_terminals);
bool eliminate_left_recursion2(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
void eliminate_non_immediate_left_recursion3(map<char,production> &list_prod, vector<char> &all_non_terminals);
#endif
