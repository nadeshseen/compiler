#ifndef SLR1_PARSER_H
#define SLR1_PARSER_H

//#include"project_header.h"
#include "parser_header.h"



bool if_symbol_already_exist_slr_table(char name,int item_num, map<int,map<char,vector<string>>> slr_table);
bool if_item_already_exist_slr_table(int item_num, map<int,map<char,vector<string>>> slr_table);

void reduce_moves(map<int,map<char,vector<string>>> &slr_table, vector<map<char,production>> items, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals);
void find_closure(char closure_symbol, map<char,production> grammar_prod, map<char, production> &item_grammar);
map<char, production> generate_item0(map<char,production> grammar_prod, vector<char> all_non_terminals);

void store_in_table(string goto_this_item, int index, char this_column, map<int,map<char,vector<string>>> &slr_table);

void goto_function(map<char, production> item_grammar, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals, int index, map<int,map<char,vector<string>>> &slr_table);

void generate_lr0_items(map<int,map<char,vector<string>>> &slr_table, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals);

void initializing_slr();
//void create_augmented_grammar(map<char,production> &grammar_prod, vector<char> &all_non_terminals);


bool parse_slr_string(string parsing_string, map<char,production> augmented_grammar_prod, map<int,map<char,vector<string>>> slr_table, vector<char> all_non_terminals);
pair<string, string> find_symbol_prod(map<char,production> augmented_grammar_prod, int prod_num, vector<char> all_non_terminals);

#endif // SLR1_PARSER_H


