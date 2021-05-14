#include "header/grammar.h"

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
    ifstream in("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Grammar/grammar.txt");
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


