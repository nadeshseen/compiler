#include "../../header/ll1parser.h"


void left_factoring(char index, map<char,production> &list_prod, vector<char> &all_non_terminals){
  vector<string> unchanged_prod;
  vector<vector<string>> changed_prod;
  for(int i=0;i<list_prod[index].prod.size();i++){
    int first=1;
    if(is_present(list_prod[index].prod[i][0], changed_prod))
     continue;
    vector<string> temp_list;
    for(int j=i+1;j<list_prod[index].prod.size();j++){
      if(list_prod[index].prod[i][0]==list_prod[index].prod[j][0]){
        if(first){
          temp_list.push_back(list_prod[index].prod[i]);
          first=0;
          temp_list.push_back(list_prod[index].prod[j]);
        }
        else{
          temp_list.push_back(list_prod[index].prod[j]);
        }
      }
    }
    if(!temp_list.empty()) changed_prod.push_back(temp_list);
  }

  for(int i=0;i<list_prod[index].prod.size();i++){
    if(!is_present(list_prod[index].prod[i][0], changed_prod))
      unchanged_prod.push_back(list_prod[index].prod[i]);
  }
  list_prod[index].prod.clear();
  for(int i=0; i<unchanged_prod.size();i++){
    list_prod[index].prod.push_back(unchanged_prod[i]);
  }

  for(int i=0;i<changed_prod.size();i++){
//      cout<<endl<<list_prod.size()<<" ";
    char new_index = find_add_symbol('A',list_prod, all_non_terminals);
//    cout<<list_prod.size()<<endl;
    string old_prod;
    int first=1;

    for(int j=0;j<changed_prod[i].size();j++){
      if(first){
        first=0;
        string first_symbol(1,changed_prod[i][j][0]);
        old_prod+=first_symbol;
        list_prod[new_index].prod.push_back(&changed_prod[i][j][1]);
      }else{
        list_prod[new_index].prod.push_back(&changed_prod[i][j][1]);
      }
    }

    old_prod+=list_prod[new_index].name;
    list_prod[index].prod.push_back(old_prod);

  }


}

bool left_factoring2(char index, map<char,production> &list_prod, vector<char> &all_non_terminals){
  vector<string> unchanged_prod;
  vector<vector<string>> changed_prod;
  for(int i=0;i<list_prod[index].prod.size();i++){
    int first=1;
    if(is_present(list_prod[index].prod[i][0], changed_prod)){
        return true;
    }
    vector<string> temp_list;
    for(int j=i+1;j<list_prod[index].prod.size();j++){
      if(list_prod[index].prod[i][0]==list_prod[index].prod[j][0]){
          return true;
        if(first){
          temp_list.push_back(list_prod[index].prod[i]);
          first=0;
          temp_list.push_back(list_prod[index].prod[j]);
        }
        else{
          temp_list.push_back(list_prod[index].prod[j]);
        }
      }
    }
    if(!temp_list.empty()) changed_prod.push_back(temp_list);
  }
  return false;





}
