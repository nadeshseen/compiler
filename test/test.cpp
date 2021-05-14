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

void generate_grammar_general(string contents,map<char,production> &list_productions, vector<char> &all_non_terminals);
string import_grammar(map<char,production> &list_productions, vector<char> &all_non_terminals);
bool is_non_terminal(char ch);
bool is_string_non_terminal(string ch);

void find_all_terminals(map<char,production> list_prod, vector<char> &all_terminals, vector<char> all_non_terminals);
bool is_terminal_present(char ch, vector<char> all_terminals);

void find_first(char index, map<char,production> &list_prod);
bool add_first_to_follow(char index, map<char,production> &list_prod, vector<char> &follow_list);
void find_follow(char follow_char, map<char,production> &list_prod, vector<char> &follow_list, vector<char> all_non_terminals);

void push_char(vector<char> &arr_list,char elements);
void push_production(vector<string> &arr_list,string elements);
bool is_digit(char digit);
bool is_string_digit(string digit);


void create_augmented_grammar(map<char,production> &grammar_prod, vector<char> &all_non_terminals);
bool if_symbol_already_present(char name, map<char, production> grammar);

void find_first_of_string(string any_string, vector<char> &first_list,int k, map<char, production> augmented_grammar);
int grammar();

//void generate_grammar(string contents,map<char,production> &list_productions, vector<char> &all_non_terminals);
//bool is_non_terminal(char ch);
//int find_production(char ch, map<char,production> &list_prod);



bool is_present(char ch, vector<vector<string>> list);
void left_factoring(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
void eliminate_left_recursion(char index, map<char,production> &list_prod, vector<char> &all_non_terminals);
void eliminate_non_immediate_left_recursion(map<char,production> &list_prod, vector<char> &all_non_terminals);



void construct_LL1_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_non_terminals);

void construct_blank_table(map<char,map<char,vector<string>>> &table, map<char,production> list_prod, vector<char> all_terminals, vector<char> all_non_terminals);


bool parse_string(string parsing_str, map<char,map<char,vector<string>>> table, char start_symbol);


char find_add_symbol(char ch, map<char,production> &list_prod, vector<char> &all_non_terminals){

  for(auto i = list_prod.begin(); i != list_prod.end(); ++i){
    if(i->first == ch) ch++;
  }

  production temp;
  temp.name = ch;
//  cout<<endl<<list_prod.size()<<" ";
  list_prod.insert(pair<char,production>(temp.name,temp));
  all_non_terminals.push_back(ch);
//  cout<<list_prod.size()<<endl;
  return temp.name;
}
bool is_terminal_present(char ch, vector<char> all_terminals){
  for(int i=0;i<all_terminals.size();i++){
    if(all_terminals[i]==ch)
      return true;
  }
  return false;
}

void push_char(vector<char> &arr_list,char elements){
  for(int i=0;i<arr_list.size();i++){
    if(elements==arr_list[i]) return;
  }
  arr_list.push_back(elements);
}

void push_production(vector<string> &arr_list,string elements){
  for(int i=0;i<arr_list.size();i++){
    if(elements==arr_list[i]) return;
  }
  arr_list.push_back(elements);
}

bool is_non_terminal(char ch){
  if(ch>='A'&&ch<='Z')
    return true;
  return false;
}

bool is_string_digit(string line){
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}
bool is_string_non_terminal(string ch){
    if(ch.size()!=1){
        return false;
    }
  if(ch>="A"&&ch<="Z")
    return true;
  return false;
}

bool if_symbol_already_present(char name, map<char, production> grammar){
    for(auto itr=grammar.begin();itr!=grammar.end();itr++){
        if(name == itr->first){
            return true;
        }
    }
    return false;
}

void create_augmented_grammar(map<char,production> &grammar_prod, vector<char> &all_non_terminals){
    for(int itr=0;itr<all_non_terminals.size();itr++){
        if(grammar_prod[all_non_terminals[itr]].start_symbol){
            string starting_symbol;
            starting_symbol+=all_non_terminals[itr];
            char augmented_symbol = find_add_symbol('A',grammar_prod,all_non_terminals);

            all_non_terminals.insert(all_non_terminals.begin(),all_non_terminals[all_non_terminals.size()-1]);
            all_non_terminals.pop_back();
            grammar_prod[augmented_symbol].start_symbol=2;
            grammar_prod[augmented_symbol].name=augmented_symbol;

            grammar_prod[augmented_symbol].prod.push_back(starting_symbol);
            cout<<endl<<"Augmented Symbol : "<<augmented_symbol<<endl;
            break;
        }
    }

}

void find_all_terminals(map<char,production> list_prod, vector<char> &all_terminals,vector<char> all_non_terminals){
  for(int i=0;i<all_non_terminals.size();i++){
    for(int j=0;j<list_prod[all_non_terminals[i]].prod.size();j++){
      for(int k=0;k<list_prod[all_non_terminals[i]].prod[j].size();k++){
        if(!is_non_terminal(list_prod[all_non_terminals[i]].prod[j][k]))
          if(!is_terminal_present(list_prod[all_non_terminals[i]].prod[j][k],all_terminals))
            if(list_prod[all_non_terminals[i]].prod[j][k]!='#')
              all_terminals.push_back(list_prod[all_non_terminals[i]].prod[j][k]);
      }
    }
  }
}
string import_grammar(map<char,production> &list_productions, vector<char> &all_non_terminals){
    ifstream in("grammar.txt");
    string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    for(int i=0;i<contents.size();i++){
      cout<<contents[i];
    }
    return contents;
}
void generate_grammar_general(string contents,map<char,production> &list_productions, vector<char> &all_non_terminals){
//  map<char,production> list_prod;
//  map<char,production> list_productions;

  production temp_prod;
  int stage_1=1; //new line starts
  int stage_2 = 0; // symbols to be added in the non terminal which generates it.
  int start_symbol=1;
  string token;
  for(int i=0;i<contents.size();i++){
    if(stage_1){
      if(contents[i]!=' '){
        temp_prod.name=contents[i];
        all_non_terminals.push_back(temp_prod.name);

        stage_1=0;
        if(start_symbol==1){
          temp_prod.start_symbol=1;
          start_symbol=0;
        }else{
          temp_prod.start_symbol=0;
        }
      }
    }
    if(i!=contents.size()-1){
      if(contents[i]=='-'&&contents[i+1]=='>'){
        stage_2=1;
        i++;
        continue;
      }
    }
    if(stage_2){
      if(contents[i]=='\n'){
        temp_prod.prod.push_back(token);
        list_productions.insert(pair<char,production>(temp_prod.name,temp_prod));
//        list_prod.push_back(temp_prod);
        token="";
        // temp_prod.name ='';
        temp_prod.prod.clear();
        temp_prod.first.clear();
        temp_prod.follow.clear();
        stage_1=1;
        stage_2=0;
      }
      else if(contents[i]!=' '){
        if(contents[i]=='|'||contents[i]=='\n'){
          temp_prod.prod.push_back(token);
          token="";
        }
        else{
          string symb(1,contents[i]);
          token = token + symb;
        }
      }

    }
  } //for loop ends
//  return list_prod;
}



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

void find_first(char index, map<char,production> &list_prod){
    int initial_epsilon_flag = 0;

    for(int l=0;l<list_prod[index].first.size();l++){
        if(list_prod[index].first[l]=='#'){
            initial_epsilon_flag=1;
            break;
        }
    }
    if(initial_epsilon_flag){
        for(int j=0 ; j<list_prod[index].prod.size() ; j++){
            int k=0;
            int epsilon_flag=0;

            do{

                epsilon_flag=0;
                if(!is_non_terminal(list_prod[index].prod[j][k])){
                    push_char(list_prod[index].first,list_prod[index].prod[j][k]);
                }
                else
                {

                    if((list_prod[index].prod[j][k]==index)){

                        k++;
                        epsilon_flag=1;
                        continue;

                    }else{
                        find_first(list_prod[index].prod[j][k], list_prod);

                    }
                    for(int i=0;i<list_prod[list_prod[index].prod[j][k]].first.size();i++)
                    {
                        if(list_prod[list_prod[index].prod[j][k]].first[i]=='#'&& k!=list_prod[index].prod[j].size()-1){
                            epsilon_flag=1;
                            continue;
                        }

                        push_char(list_prod[index].first,list_prod[list_prod[index].prod[j][k]].first[i]);

                    }
                }
                k++;
            }while(epsilon_flag);

        }
    }else{
        for(int j=0 ; j<list_prod[index].prod.size() ; j++){
            int k=0;
            int epsilon_flag=0;
            do{
                epsilon_flag=0;
                if(!is_non_terminal(list_prod[index].prod[j][k])){
                    push_char(list_prod[index].first,list_prod[index].prod[j][k]);
                }
                else
                {
                    if((list_prod[index].prod[j][0]!=index)){
                        find_first(list_prod[index].prod[j][k], list_prod);
                    }else{
                        for(int l=0;l<list_prod[index].first.size();l++){
                            if(list_prod[index].first[l]=='#'){
                                epsilon_flag=1;
                                break;
                            }
                        }
                        if(epsilon_flag){
                            find_first(index, list_prod);
                            //                        j=0;
                            continue;
                        }else{
                            break;
                        }

                    }
                    // cout<<new_index<<" "<<list_prod[new_index].name<<" "<<list_prod[new_index].first.size()<<" "<<list_prod[index].name<<endl;

                    for(int i=0;i<list_prod[list_prod[index].prod[j][k]].first.size();i++)
                    {
                        if(list_prod[list_prod[index].prod[j][k]].first[i]=='#'&& k!=list_prod[index].prod[j].size()-1){
                            epsilon_flag=1;
                            continue;
                        }

                        push_char(list_prod[index].first,list_prod[list_prod[index].prod[j][k]].first[i]);

                    }
                }
                k++;
            }while(epsilon_flag);

        }
    }


}
void find_first_of_string(string any_string, vector<char> &first_list,int k, map<char, production> grammar_prod){
    if(k!=any_string.size()-1){
        if(!is_non_terminal(any_string[k])){
            first_list.push_back(any_string[k]);
            return;
        }
        int epsilon_flag=0;
        for(int i=0;i<grammar_prod[any_string[k]].first.size();i++){
            if(grammar_prod[any_string[k]].first[i]=='#'){
//                cout<<"Nadesh";
                epsilon_flag=1;
            }
            push_char(first_list, grammar_prod[any_string[k]].first[i]);
        }

        if(epsilon_flag){
            k=k+1;
            find_first_of_string(any_string,first_list, k, grammar_prod);
        }
    }else{
        if(!is_non_terminal(any_string[k])){
            first_list.push_back(any_string[k]);
            return;
        }
        for(int i=0;i<grammar_prod[any_string[k]].first.size();i++){
            push_char(first_list, grammar_prod[any_string[k]].first[i]);
        }

    }
}

bool is_present(char ch, vector<vector<string>> list){
  for(int i=0; i<list.size(); i++){
    if(ch==list[i][0][0]) return true;
  }
  return false;
}



int grammar(){
  ifstream in("grammar.txt");
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
  // cout<<right<<setw(40)<<"LL(1) Parsing Table"<<endl<<endl;
  // cout<<setfill('-');
  // int number_of_terminals = all_terminals.size();
  // int column_width = 20;
  // int table_width = column_width*(number_of_terminals+1);
  // cout<<endl<<setw(table_width)<<""<<endl;
  // cout<<setfill(' ');
  // cout<<"| "<<left<<setw(10)<<"";

  // for(int j=0;j<all_terminals.size();j++){
  //   cout<<left<<setw(column_width/2+1)<<"|"<<setw(column_width/2)<<all_terminals[j];
  // }

  // cout<<"|";
  // cout<<setfill('-');
  // cout<<endl<<setw(table_width)<<"";
  // cout<<endl;

  construct_LL1_table(table,list_prod, all_non_terminals);
  int ambigous_grammar = 0;
  for(int i=0;i<all_non_terminals.size();i++){
    // cout<<setfill(' ');
    // cout<<"| "<<left<<setw(10)<<list_prod[all_non_terminals[i]].name;

    for(int j=0;j<all_terminals.size();j++){
      // string output;
      if(table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size()>2)
        ambigous_grammar=1;
    //   for(int k=1;k<table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size();k++){

    //     if(k==table[list_prod[all_non_terminals[i]].name][all_terminals[j]].size()-1){
    //       output+=list_prod[all_non_terminals[i]].name;
    //       output+="->";
    //       output+=table[list_prod[all_non_terminals[i]].name][all_terminals[j]][k];
    //       break;
    //     }
    //     output+=list_prod[all_non_terminals[i]].name;
    //     output+="->";
    //     output+=table[list_prod[all_non_terminals[i]].name][all_terminals[j]][k]+", ";


    //   }
    //   if(j==all_terminals.size()-1)
    //     cout<<"|"<<setw(column_width)<<output<<"|";
    //   else
    //     cout<<"|"<<setw(column_width)<<output;
    // }
    // cout<<setfill('-');

    // cout<<endl<<setw(table_width)<<""<<endl;
  }
}

  cout<<endl<<endl;
  if(ambigous_grammar){

    return -1;
  }
  cout<<endl<<endl;

  // ifstream token_file("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Lexical/token_list.txt");
  // string token_string((istreambuf_iterator<char>(token_file)), istreambuf_iterator<char>());
  // // cout<<token_string;
  // unsigned int k=0;
  // string parsing_str;
  // int current_state=0;
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
  // cout<<"String to be parsed : "<<parsing_str<<endl<<endl;
  cout<<endl;
  parse_string(parsing_str, table, list_prod[all_non_terminals[0]].name);
  // if(parse_string(parsing_str, table, list_prod[all_non_terminals[0]].name)){
  //   cout<<"String is accepted";
  // }else{
  //   cout<<"String is not accepted";
  // }

  cout<<endl<<endl;

  return 0;
}


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
int main(){
	grammar();
	return 0;
}