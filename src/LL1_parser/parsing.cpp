#include "../../header/ll1parser.h"

bool parse_string(string parsing_str, map<char,map<char,vector<string>>> table, char start_symbol){
  // int k = parse_string.size();
  int k=0;
  vector<char> stack_tokens;
  stack_tokens.push_back('$');
  stack_tokens.push_back(start_symbol);
  while(stack_tokens.size()>1){
      cout<<stack_tokens[1]<<endl; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ye pehli line hai
    // cout<<k<<" "<<parsing_str[k]<<" "<<stack_tokens.back()<<endl;
    if(is_non_terminal(stack_tokens.back())){
      //Change the first entry in the LL(1) table
      if(table[stack_tokens.back()][parsing_str[k]].size()==2){
        string token = table[stack_tokens.back()][parsing_str[k]][1];

        stack_tokens.pop_back();
        if(token!="#"){
          for(int i = token.size()-1;i>=0;i--){
            stack_tokens.push_back(token[i]);
          }
        }

      }
      else
        return false;
    }else{
      // if(stack_tokens.back()!='#') //Algorithm is modified
        if(parsing_str[k]==stack_tokens.back()){
//            cout<<parsing_str[k]<<endl;
            stack_tokens.pop_back();
            k++;
        }else{
            return false;
        }

    }

  }
  cout<<parsing_str[k-1]<<endl;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ye dusri line hai
  if(parsing_str[k]==stack_tokens.back())
    return true;
  else
    return false;
}
