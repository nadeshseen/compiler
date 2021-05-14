#include "../../header/ll1parser.h"

bool add_first_to_follow(char index, map<char,production> &list_prod, vector<char> &follow_list){
  int flag=0;
  for(int i=0;i<list_prod[index].first.size();i++){
    if(list_prod[index].first[i]!='#'){
      push_char(follow_list,list_prod[index].first[i]);
    }
    if(list_prod[index].first[i]=='#'){
      flag=1;
    }

  }
  if (flag==1) return true;

  return false;
}

void find_follow(char follow_char, map<char,production> &list_prod, vector<char> &follow_list, vector<char> all_non_terminals){
  // return;
  for(int  i=0;i<all_non_terminals.size();i++){
    for(int j=0;j<list_prod[all_non_terminals[i]].prod.size();j++){
      int count_flag=0;
      for(int k=0;k<list_prod[all_non_terminals[i]].prod[j].size();k++){

        int n=list_prod[all_non_terminals[i]].prod[j].size();
        if(k!=n-1){
          if(list_prod[all_non_terminals[i]].prod[j][k]==follow_char||count_flag==1){
            count_flag=0;
            if(!is_non_terminal(list_prod[all_non_terminals[i]].prod[j][k+1])){
              push_char(follow_list,list_prod[all_non_terminals[i]].prod[j][k+1]);
            }
            else{
//              int index = find_production(list_prod[all_non_terminals[i]].prod[j][k+1],list_prod);
              bool has_epsilon = add_first_to_follow(list_prod[all_non_terminals[i]].prod[j][k+1], list_prod, follow_list);
              if(has_epsilon&&k+1==n-1){
                // cout<<list_prod[all_non_terminals[i]].name<<" "<<follow_char<<endl;
                if(list_prod[all_non_terminals[i]].prod[j][k]!=list_prod[all_non_terminals[i]].name){

                  if(!list_prod[all_non_terminals[i]].follow.empty()){
                    for(int l=0;l<list_prod[all_non_terminals[i]].follow.size();l++)
                      push_char(follow_list,list_prod[all_non_terminals[i]].follow[l]);
                    }else{

                    find_follow(list_prod[all_non_terminals[i]].name, list_prod, follow_list, all_non_terminals);
                  }
                }
              }
              else if(has_epsilon){
                count_flag=1;
                // continue;
              }

            }
          }
        }
        else{
          if((list_prod[all_non_terminals[i]].prod[j][k]==follow_char&&follow_char!=list_prod[all_non_terminals[i]].name)){
            if(!list_prod[all_non_terminals[i]].follow.empty()){
              for(int l=0;l<list_prod[all_non_terminals[i]].follow.size();l++)
                push_char(follow_list,list_prod[all_non_terminals[i]].follow[l]);
              }else{
              // cout<<list_prod[all_non_terminals[i]].name<<" "<<follow_char<<endl;
              find_follow(list_prod[all_non_terminals[i]].name, list_prod, follow_list, all_non_terminals);
            }
              // cout<<i<<" "<<j<<" "<<k<<" "<<endl;
              // return;
            }
        }

      }
    }
  }
}
