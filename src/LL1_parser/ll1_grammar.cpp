#include "../../header/ll1parser.h"


void construct_blank_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_terminals, vector<char> all_non_terminals){
  for(int i=0;i<all_non_terminals.size();i++){
    map<char, vector<string>> column;
    for(int j=0;j<all_terminals.size();j++){
      vector<string> cell;
      cell.push_back(" ");
      column.insert(pair<char,vector<string>>(all_terminals[j],cell));
    }
    table.insert(pair<char,map<char,vector<string>>>(list_prod[all_non_terminals[i]].name,column));
  }
}

void construct_LL1_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_non_terminals){
  for(int i=0;i<all_non_terminals.size();i++){
    for(int j=0;j<list_prod[all_non_terminals[i]].prod.size();j++){
      if(!is_non_terminal(list_prod[all_non_terminals[i]].prod[j][0])){
        if(list_prod[all_non_terminals[i]].prod[j][0]=='#'){
          for(int k=0;k<list_prod[all_non_terminals[i]].follow.size();k++){
            table[list_prod[all_non_terminals[i]].name][list_prod[all_non_terminals[i]].follow[k]].push_back(list_prod[all_non_terminals[i]].prod[j]);
          }
        }else{
            push_production(table[list_prod[all_non_terminals[i]].name][list_prod[all_non_terminals[i]].prod[j][0]], list_prod[all_non_terminals[i]].prod[j]);
//          table[list_prod[all_non_terminals[i]].name][list_prod[all_non_terminals[i]].prod[j][0]].push_back(list_prod[all_non_terminals[i]].prod[j]);
        }
      }else{

          int prod_index = 0;
          bool epsilon_flag = true;
          bool last_epsilon = false;
          while (epsilon_flag) {
              epsilon_flag=false;

              char first_symbol = list_prod[all_non_terminals[i]].prod[j][prod_index];
              for(int k=0;k<list_prod[first_symbol].first.size();k++){
                  if(list_prod[first_symbol].first[k]=='#'){
                      epsilon_flag=true;
                      if(prod_index==list_prod[all_non_terminals[i]].prod[j].size()-1){
                          last_epsilon=true;
                      }
                  }
                  else {
                      push_production(table[list_prod[all_non_terminals[i]].name][list_prod[first_symbol].first[k]], list_prod[all_non_terminals[i]].prod[j]);
//                      table[list_prod[all_non_terminals[i]].name][list_prod[first_symbol].first[k]].push_back(list_prod[all_non_terminals[i]].prod[j]);
                  }

              }

              prod_index++;
          }

          if(last_epsilon){
              for(int k=0;k<list_prod[all_non_terminals[i]].follow.size();k++){
                  push_production(table[all_non_terminals[i]][list_prod[all_non_terminals[i]].follow[k]], list_prod[all_non_terminals[i]].prod[j]);
//                table[all_non_terminals[i]][list_prod[all_non_terminals[i]].follow[k]].push_back(list_prod[all_non_terminals[i]].prod[j]);
              }
          }

      }
    }
  }
}
