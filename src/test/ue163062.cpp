#include"./header/ue163062.h"

bool check_follow(char symbol, map<char,production> list_prod){
    for(int i=0;i<list_prod[symbol].first.size();i++){
        for(int j=0;j<list_prod[symbol].follow.size();j++){
            if(list_prod[symbol].first[i]==list_prod[symbol].follow[j]){
//                cout<<symbol<<" "<<list_prod[symbol].first[i]<<" "<<list_prod[symbol].follow[j]<<endl;
                return true;
            }
    }
    }
    return false;
}

bool check_first_of_strings(string any_string1, string any_string2, map<char, production> grammar_prod,int i){
    vector<char> first_list1;
    vector<char> first_list2;
//    cout<<any_string1<<" "<<any_string2;
    find_first_of_string(any_string1, first_list1,0,grammar_prod);
    find_first_of_string(any_string2, first_list2,0,grammar_prod);
//    cout<<first_list1.size();
//    cout<<first_list2.size();
    for(int i=0;i<first_list1.size();i++){
        for(int j=0;j<first_list2.size();j++){

            if(first_list1[i]==first_list2[j]&&(first_list1[i]!='#'||first_list2[j]!='#')){
//                cout<<first_list1[i]<<" "<<first_list2[j];
                return true;
            }
        }
    }

    return false;
}
void ll1_test(){
    map<char,production> list_prod;
    map<char,production> list_prod_copy;
    map<char,production> list_prod_2;
    vector<char> all_non_terminals;
    string contents = import_grammar(list_prod, all_non_terminals);

    generate_grammar_general(contents,list_prod,all_non_terminals);

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
    }

    // Find first for all productions
    list_prod_2 = list_prod;
    eliminate_non_immediate_left_recursion3(list_prod_2,all_non_terminals);
    list_prod_copy = list_prod;
    for(int i=0;i<all_non_terminals.size();i++){

        if(left_factoring2(all_non_terminals[i],list_prod_copy, all_non_terminals)){
            cout<<"Not LL(1)"<<endl<<"1";
            return;
        }
        if(eliminate_non_immediate_left_recursion2(list_prod_2,all_non_terminals)){
            cout<<"Not LL(1)"<<endl<<"2";
            return;
        }
    }
    for(int j=0;j<all_non_terminals.size();j++){
      find_first(all_non_terminals[j], list_prod);
    }
    // First symbol is assumed to be Start Symbol
    list_prod[all_non_terminals[0]].follow.push_back('$');
    for(int j=0;j<all_non_terminals.size();j++){
      find_follow(list_prod[all_non_terminals[j]].name, list_prod, list_prod[all_non_terminals[j]].follow, all_non_terminals);

    }

    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0;j<list_prod[all_non_terminals[i]].prod.size();j++){
            if(list_prod[all_non_terminals[i]].prod[j]=="#"){
                if(check_follow(all_non_terminals[i], list_prod)){
                    cout<<"Not LL(1)"<<endl<<"3";
                    return;
            }
            }
        }
    }
//    int flag=grammar();
//    if(flag==-1){
//        cout<<endl<<"Not LL(1)"<<endl<<endl;
//            return;
//    }



    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0;j<list_prod[all_non_terminals[i]].prod.size()-1;j++){
            for(int k=j+1;k<list_prod[all_non_terminals[i]].prod.size();k++){
//                cout<<list_prod[all_non_terminals[i]].prod[j]<<" "<<list_prod[all_non_terminals[i]].prod[k];
                if(check_first_of_strings(list_prod[all_non_terminals[i]].prod[j],list_prod[all_non_terminals[i]].prod[k],list_prod,i)){

                    cout<<endl<<"Not LL(1)"<<"4"<<endl;
                    return;

                }

            }

        }
    }

    cout<<endl<<"This is LL(1) grammar"<<endl;
}














