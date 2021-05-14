#include "../../header/ll1parser.h"

void eliminate_left_recursion(char index, map<char,production> &list_prod, vector<char> &all_non_terminals){
  vector<string> beta_prod, alpha_prod;
  int recursion_flag=0;
  // cout<<"Nadesh";
  for(int i=0;i<list_prod[index].prod.size();i++){
    // cout<<i;
    if(list_prod[index].name != list_prod[index].prod[i][0])
      beta_prod.push_back(list_prod[index].prod[i]);
    else{
      alpha_prod.push_back(list_prod[index].prod[i]);
      recursion_flag=1;
    }
  }
  if(recursion_flag){
    list_prod[index].prod.clear();
    char new_index = find_add_symbol('A',list_prod, all_non_terminals); // last change
    for(int i=0; i<alpha_prod.size();i++){
      string alpha_rule = &(alpha_prod[i])[1];
      alpha_rule += list_prod[new_index].name;
      list_prod[new_index].prod.push_back(alpha_rule);
    }
    list_prod[new_index].prod.push_back("#");
    for(int j=0;j<beta_prod.size();j++){
        string beta_rule = beta_prod[j]+list_prod[new_index].name;
        list_prod[index].prod.push_back(beta_rule);
    }

  }
}

bool eliminate_left_recursion2(char index, map<char,production> &list_prod, vector<char> &all_non_terminals){

  int recursion_flag=0;
  // cout<<"Nadesh";
  for(int i=0;i<list_prod[index].prod.size();i++){
    // cout<<i;
    if(list_prod[index].name == list_prod[index].prod[i][0]){

      return true;
    }
  }

}
bool eliminate_non_immediate_left_recursion2(map<char,production> &list_prod, vector<char> &all_non_terminals){
    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0 ; j<i ; j++){
            vector<string> aj_gamma_prod,remaining_prod;
            int i_prod_size = list_prod[all_non_terminals[i]].prod.size();
            for(int k=0;k<i_prod_size;k++){
                if(all_non_terminals[j] == list_prod[all_non_terminals[i]].prod[k][0]){
                    aj_gamma_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }else{
                    remaining_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }
            }
            list_prod[all_non_terminals[i]].prod.clear();
            for(int k=0;k<aj_gamma_prod.size();k++){
                for(int l=0;l<list_prod[all_non_terminals[j]].prod.size();l++){
                    string gamma_string = aj_gamma_prod[k];
                    gamma_string.erase(0,1);
                    string delta_string = list_prod[all_non_terminals[j]].prod[l] + gamma_string;
                    list_prod[all_non_terminals[i]].prod.push_back(delta_string);
                }
            }
            for(int k=0;k<remaining_prod.size();k++){
                list_prod[all_non_terminals[i]].prod.push_back(remaining_prod[k]);
            }

        }
        int flag = eliminate_left_recursion2(all_non_terminals[i], list_prod, all_non_terminals);
        if(flag){
            return true;
        }

    }
    return false;
}
void eliminate_non_immediate_left_recursion(map<char,production> &list_prod, vector<char> &all_non_terminals){
    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0 ; j<i ; j++){
            vector<string> aj_gamma_prod,remaining_prod;
            int i_prod_size = list_prod[all_non_terminals[i]].prod.size();
            for(int k=0;k<i_prod_size;k++){
                if(all_non_terminals[j] == list_prod[all_non_terminals[i]].prod[k][0]){
                    aj_gamma_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }else{
                    remaining_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }
            }
            list_prod[all_non_terminals[i]].prod.clear();
            for(int k=0;k<aj_gamma_prod.size();k++){
                for(int l=0;l<list_prod[all_non_terminals[j]].prod.size();l++){
                    string gamma_string = aj_gamma_prod[k];
                    gamma_string.erase(0,1);
                    string delta_string = list_prod[all_non_terminals[j]].prod[l] + gamma_string;
                    list_prod[all_non_terminals[i]].prod.push_back(delta_string);
                }
            }
            for(int k=0;k<remaining_prod.size();k++){
                list_prod[all_non_terminals[i]].prod.push_back(remaining_prod[k]);
            }

        }
        eliminate_left_recursion(all_non_terminals[i], list_prod, all_non_terminals);
    }
}

void eliminate_non_immediate_left_recursion3(map<char,production> &list_prod, vector<char> &all_non_terminals){
    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0 ; j<i ; j++){
            vector<string> aj_gamma_prod,remaining_prod;
            int i_prod_size = list_prod[all_non_terminals[i]].prod.size();
            for(int k=0;k<i_prod_size;k++){
                if(all_non_terminals[j] == list_prod[all_non_terminals[i]].prod[k][0]){
                    aj_gamma_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }else{
                    remaining_prod.push_back(list_prod[all_non_terminals[i]].prod[k]);
                }
            }
            list_prod[all_non_terminals[i]].prod.clear();
            for(int k=0;k<aj_gamma_prod.size();k++){
                for(int l=0;l<list_prod[all_non_terminals[j]].prod.size();l++){
                    string gamma_string = aj_gamma_prod[k];
                    gamma_string.erase(0,1);
                    string delta_string = list_prod[all_non_terminals[j]].prod[l] + gamma_string;
                    list_prod[all_non_terminals[i]].prod.push_back(delta_string);
                }
            }
            for(int k=0;k<remaining_prod.size();k++){
                list_prod[all_non_terminals[i]].prod.push_back(remaining_prod[k]);
            }

        }
//        eliminate_left_recursion(all_non_terminals[i], list_prod, all_non_terminals);
    }
}
