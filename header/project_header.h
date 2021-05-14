#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include <map>
#include <typeinfo>
#include<algorithm>

using namespace std;
class production{
  public:
    char name;
    vector<string> prod;
    vector<char> first, follow;
    int start_symbol;
    vector<char> k_lookahead;
    vector<string> lookahead_of_these_strings;
    int is_closed; //0 means not in queue, 1 means in the queue and 2 means processed
    map<char,int> goto_item;
    production(){
        is_closed=0;
    }
};
char find_add_symbol(char ch, map<char,production> &list_prod, vector<char> &all_non_terminals);

#endif // PROJECT_HEADER_H
