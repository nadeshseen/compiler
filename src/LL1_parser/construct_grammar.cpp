#include "../../header/ll1parser.h"

//int find_production(char ch, map<char,production> &list_prod){
//  for(int i=0;i<list_prod.size();i++){
//    if(ch==list_prod[i].name) return i;
//  }
//  return -1;
//}




bool is_present(char ch, vector<vector<string>> list){
  for(int i=0; i<list.size(); i++){
    if(ch==list[i][0][0]) return true;
  }
  return false;
}



int grammar(){
  ifstream in("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Grammar/grammar.txt");
  string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
//  for(int i=0;i<contents.size();i++){
//    cout<<contents[i];
//  }
  map<char,production> list_prod;
  vector<char> all_non_terminals;

  generate_grammar_general(contents,list_prod,all_non_terminals);

//  eliminate_non_immediate_left_recursion(list_prod, all_non_terminals);

  for(int i=0;i<all_non_terminals.size();i++){
    left_factoring(all_non_terminals[i], list_prod, all_non_terminals);
  }
  // Find first for all productions
  for(int j=0;j<all_non_terminals.size();j++){
    find_first(all_non_terminals[j], list_prod);
  }
  // First symbol is assumed to be Start Symbol
  list_prod[all_non_terminals[0]].follow.push_back('$');
  for(int j=0;j<all_non_terminals.size();j++){
    find_follow(list_prod[all_non_terminals[j]].name, list_prod, list_prod[all_non_terminals[j]].follow, all_non_terminals);

  }

  vector<char> all_terminals;
  find_all_terminals(list_prod,all_terminals, all_non_terminals);
  all_terminals.push_back('$');
  map<char,map<char,vector<string>>> table;
  construct_blank_table(table,list_prod,all_terminals, all_non_terminals);

  cout<<endl;
  cout<<setw(20)<<" "<<setw(25)<<"First"<<setw(20)<<"Follow"<<endl<<endl;
//  cout<<all_non_terminals.size();
  for(int i=0;i<all_non_terminals.size();i++){
    string output="";
    // cout<<list_prod[i].name;
    string change(1,list_prod[all_non_terminals[i]].name);
    output += change+" -> ";
    // cout<<output;
    for(int j=0;j<list_prod[all_non_terminals[i]].prod.size();j++){
      if(j!=list_prod[all_non_terminals[i]].prod.size()-1)
        output += list_prod[all_non_terminals[i]].prod[j] + "|";
      else
        output += list_prod[all_non_terminals[i]].prod[j];
    }
    cout<<left<<setw(20)<<output;
    output="";
    output+="{";
    for(int j=0;j<list_prod[all_non_terminals[i]].first.size();j++){
      string first_str(1, list_prod[all_non_terminals[i]].first[j]);
      if(j!=list_prod[all_non_terminals[i]].first.size()-1)
        output+= first_str+",";
      else
        output+= first_str;
    }
    output+="}";

    cout<<left<<setw(20)<<output;
  // cout<<endl;}
    output="";
    output+="{";
    for(int j=0;j<list_prod[all_non_terminals[i]].follow.size();j++){
      // cout<<"asdf";

      string follow_str(1, list_prod[all_non_terminals[i]].follow[j]);
      // cout<<follow_str;
      if(j!=list_prod[all_non_terminals[i]].follow.size()-1)
        output+= follow_str+",";
      else
        output+= follow_str;
    }
    output+="}";
    cout<<output;
    cout<<endl;
  }
  cout<<endl<<endl;
  cout<<right<<setw(40)<<"LL(1) Parsing Table"<<endl<<endl;
  cout<<setfill('-');
  int number_of_terminals = all_terminals.size();
  int column_width = 20;
  int table_width = column_width*(number_of_terminals+1);
  cout<<endl<<setw(table_width)<<""<<endl;
  cout<<setfill(' ');
  cout<<"| "<<left<<setw(10)<<"";

  for(int j=0;j<all_terminals.size();j++){
    cout<<left<<setw(column_width/2+1)<<"|"<<setw(column_width/2)<<all_terminals[j];
  }

  cout<<"|";
  cout<<setfill('-');
  cout<<endl<<setw(table_width)<<"";
  cout<<endl;

  construct_LL1_table(table,list_prod, all_non_terminals);
  int ambigous_grammar = 0;
  for(int i=0;i<all_non_terminals.size();i++){
    cout<<setfill(' ');
    cout<<"| "<<left<<setw(10)<<list_prod[all_non_terminals[i]].name;

    for(int j=0;j<all_terminals.size();j++){
      string output;
      if(table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size()>2)
        ambigous_grammar=1;
      for(int k=1;k<table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size();k++){

        if(k==table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size()-1){
          output+=list_prod[all_non_terminals[i]].name;
          output+="->";
          output+=table[list_prod[all_non_terminals[i]].name][all_terminals[j]][k];
          break;
        }
        output+=list_prod[all_non_terminals[i]].name;
        output+="->";
        output+=table[list_prod[all_non_terminals[i]].name][all_terminals[j]][k]+", ";


      }
      if(j==all_terminals.size()-1)
        cout<<"|"<<setw(column_width)<<output<<"|";
      else
        cout<<"|"<<setw(column_width)<<output;
    }
    cout<<setfill('-');

    cout<<endl<<setw(table_width)<<""<<endl;
  }

  cout<<endl<<endl;
  if(ambigous_grammar){

    return -1;
  }
  cout<<endl<<endl;

  ifstream token_file("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Lexical/token_list.txt");
  string token_string((istreambuf_iterator<char>(token_file)), istreambuf_iterator<char>());
  // cout<<token_string;
  unsigned int k=0;
  string parsing_str;
  int current_state=0;
//  while(token_string[k]){
//      if(current_state==0){
//          if(token_string[k]==':'){
//              current_state=1;
//          }else {
//              if(token_string[k]!='\n'&&token_string[k]!=' ')
//                  parsing_str+=token_string[k];
//          }
//      }else if(current_state==1){
//          if(token_string[k]==';'){
//              current_state=0;
//          }
//      }
//    k++;
//  }
  parsing_str="i+i";
  parsing_str+="$";
  // cout<<parsing;
  // string parsing_str = "i+i*i)$";
  cout<<"String to be parsed : "<<parsing_str<<endl<<endl;
  if(parse_string(parsing_str, table, list_prod[all_non_terminals[0]].name)){
    cout<<"String is accepted";
  }else{
    cout<<"String is not accepted";
  }

  cout<<endl<<endl;

  return 0;
}
