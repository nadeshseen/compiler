#ifndef PARSER_H
#define PARSER_H

#include"grammar.h"

void draw_table(map<int,map<char,vector<string>>> slr_table, vector<map<char,production>> items, vector<char> all_symbols);
bool duplicate_entries(map<int,map<char,vector<string>>> slr_table);
bool if_symbol_already_exist_in_table(char name,int item_num, map<int,map<char,vector<string>>> slr_table);
bool if_item_already_exist_in_table(int item_num, map<int,map<char,vector<string>>> slr_table);
void store_in_table(string goto_this_item, int index, char this_column, map<int,map<char,vector<string>>> &slr_table);
pair<int, int> find_production_number(char prod_symbol, string prod, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals);
vector<pair<int, string>> find_complete_production(map<char,production> item_grammar, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals);
int is_same_grammar(map<char,production> grammar_prod, vector<map<char,production>> items);

#endif
