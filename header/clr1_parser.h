#ifndef CLR1_PARSER_H
#define CLR1_PARSER_H

//#include"project_header.h"
#include"parser_header.h"

pair<string, string> find_symbol_prod_clr(map<char,production> augmented_grammar_prod, int prod_num, vector<char> all_non_terminals);
void initialize_clr();
bool parse_clr_string(string parsing_string, map<char,production> augmented_grammar_prod, map<int,map<char,vector<string>>> slr_table, vector<char> all_non_terminals);


#endif // CLR1_PARSER_H


