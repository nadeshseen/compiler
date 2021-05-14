#include"header/clr1_parser.h"

pair<string, string> find_symbol_prod_clr(map<char,production> augmented_grammar_prod, int prod_num, vector<char> all_non_terminals){
    int index=0;
    pair<string, string> reduce_symbol_prod;

    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0;j<augmented_grammar_prod[all_non_terminals[i]].prod.size();j++){

            if(index==prod_num){
                reduce_symbol_prod.first = all_non_terminals[i];
                reduce_symbol_prod.second = augmented_grammar_prod[all_non_terminals[i]].prod[j];
                return reduce_symbol_prod;
            }
            index++;
        }
    }
    return reduce_symbol_prod;
}

bool parse_clr_string(string parsing_string, map<char,production> augmented_grammar_prod, map<int,map<char,vector<string>>> slr_table, vector<char> all_non_terminals){
    parsing_string+="$";
    cout<<endl<<parsing_string<<endl;
    vector<string> slr_stack;
    slr_stack.push_back("0");

    int item_num = stoi(slr_stack.back());
    int k=0;
    string output;
    output="";
    for(int i=0;i<slr_stack.size();i++){
        output+=slr_stack[i];
    }
    cout<<setw(30)<<left<<output;
    output="";
    for(int i=k;i<parsing_string.size();i++){
        output+=parsing_string[i];
    }
    cout<<setw(30)<<left<<output;
    cout<<endl;
    output="";
    if(slr_table[item_num][parsing_string[k]].size()==0){
        return false;
    }
    while(slr_table[item_num][parsing_string[k]][0]!="R0"&&slr_table[item_num][parsing_string[k]].size()==1){

        if(is_string_digit(slr_stack.back())){
            if(slr_table[item_num][parsing_string[k]].size()==1){
                string move = slr_table[item_num][parsing_string[k]].front();
                if(move[0]=='S'){
                    string state = slr_table[item_num][parsing_string[k]].front();
                    state.erase(0,1);
                    slr_stack.push_back(string(1,parsing_string[k]));
                    slr_stack.push_back(state);
                    k++;
                    item_num=stoi(slr_stack.back());
                }else{
                    move.erase(0,1);
                    int num_of_prod = stoi(move);
                    pair<string, string> reduce_symbol_prod = find_symbol_prod_clr(augmented_grammar_prod, num_of_prod, all_non_terminals);
                    string reduce_symbol = reduce_symbol_prod.first;
                    string reduce_prod = reduce_symbol_prod.second;
                    int num_of_pops = reduce_prod.size()*2;
                    if(reduce_prod=="#"){
                        num_of_pops = 0;
                    }
                    int pop_i=0;
                    while(pop_i!=num_of_pops){
                        slr_stack.pop_back();
                        pop_i++;
                    }
                    slr_stack.push_back(reduce_symbol);

                    if(is_string_non_terminal(slr_stack.back())){
                        int number = stoi(slr_stack[slr_stack.size()-2]);
                        if(slr_table[number][slr_stack.back()[0]].empty()){
                            return false;
                        }
                        slr_stack.push_back(slr_table[number][slr_stack.back()[0]].front());
                        item_num = stoi(slr_stack.back());
                    }

                }
            }else{
                return false;
            }
        }
        if(slr_table[item_num][parsing_string[k]].size()==0){
            return false;
        }

        string output;
        output="";
        for(int i=0;i<slr_stack.size();i++){
            output+=slr_stack[i];
        }
        cout<<setw(30)<<left<<output;
        output="";
        for(int i=k;i<parsing_string.size();i++){
            output+=parsing_string[i];
        }
        cout<<setw(30)<<left<<output;
        cout<<endl;
        output="";
    }

    item_num = stoi(slr_stack.back());
    if(slr_table[item_num][parsing_string[k]][0]=="R0"){
        return true;
    }else{
        return false;
    }


}
