#include "./header/parser_header.h"


int is_same_grammar(map<char,production> grammar_prod, vector<map<char,production>> items){
    int is_same_flag=1;

    for(int i=0;i<items.size();i++){
        is_same_flag=1;
            for(auto itr=items[i].begin();itr!=items[i].end();itr++){
                if(items[i][itr->first].prod.size()==grammar_prod[itr->first].prod.size()){
                    for(int k=0;k<items[i][itr->first].prod.size();k++){
                        if(items[i][itr->first].prod[k]!=grammar_prod[itr->first].prod[k]) {
                            is_same_flag=0;
                            break;
                        }
                    }
                }else {
                    is_same_flag=0;
                }
            }
            if(is_same_flag){
                return i;
            }
    }
    return -1;

}

void draw_table(map<int,map<char,vector<string>>> slr_table, vector<map<char,production>> items, vector<char> all_symbols){

    cout<<setw(10)<<left<<" ";
    for(int j=0;j<all_symbols.size();j++){
        cout<<setw(10)<<left<<all_symbols[j];
    }
    cout<<endl;
    for(int i=0;i<items.size();i++){
        cout<<setw(10)<<left<<i;
        for(int j=0;j<all_symbols.size();j++){
            string output;

            for(int k=0;k<slr_table[i][all_symbols[j]].size();k++){
//                cout<<slr_table[i][all_symbols[j]].size()<<" "<<i<<" "<<all_symbols[j]<<endl;
                if(k==slr_table[i][all_symbols[j]].size()-1){
                    output+=slr_table[i][all_symbols[j]][k];
                }else{
                    output+=slr_table[i][all_symbols[j]][k]+",";
                }
//                cout<<slr_table[i][all_symbols[j]][k];
            }
            cout<<setw(10)<<left<<output;
        }
        cout<<endl;
    }
}

bool duplicate_entries(map<int,map<char,vector<string>>> slr_table){
    for(auto int_itr:slr_table){
        for(auto char_itr:slr_table[int_itr.first]){
            if(slr_table[int_itr.first][char_itr.first].size()>1)
                return true;
        }
    }
    return false;
}

bool if_symbol_already_exist_in_table(char name,int item_num, map<int,map<char,vector<string>>> slr_table){

        for(auto itr=slr_table[item_num].begin();itr!=slr_table[item_num].end();itr++){
            if(itr->first==name){
                return true;
            }
        }

    return false;
}
bool if_item_already_exist_in_table(int item_num, map<int,map<char,vector<string>>> slr_table){
    for(auto itr=slr_table.begin();itr!=slr_table.end();itr++){
        if(item_num == itr->first){
            return true;
        }
    }
    return false;
}
pair<int, int> find_production_number(char prod_symbol, string prod, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals){
    int prod_num=0;
    if(prod.size()==1){
        prod = "#";
    }else{
        prod.erase(prod.end()-1);
    }
    pair<int, int>  symbol_prod_num;
//    int symbol_pro
    for(int i=0;i<all_non_terminals.size();i++){
        for(int j=0;j<augmented_grammar_prod[all_non_terminals[i]].prod.size();j++){
            if(augmented_grammar_prod[all_non_terminals[i]].prod[j]==prod && all_non_terminals[i]==prod_symbol){
                 symbol_prod_num.first = i;
                 symbol_prod_num.second = prod_num;
                 return symbol_prod_num;
//                return prod_num;
            }
            prod_num++;
        }

    }
    return symbol_prod_num;
}
vector<pair<int, string>> find_complete_production(map<char,production> item_grammar, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals){
    vector<pair<int, string>> complete_prod;
    for(auto itr=item_grammar.begin();itr!=item_grammar.end();itr++){
        for(int i =0;i<item_grammar[itr->first].prod.size();i++){

            int size_of_prod = item_grammar[itr->first].prod[i].size()-1;
//            cout<<item_grammar[itr->first].prod[i]<<" ";
            if(item_grammar[itr->first].prod[i][size_of_prod]=='.'){
//                cout<<"nad";
                pair<int,int> symbol_prod_num = find_production_number(itr->first, item_grammar[itr->first].prod[i], augmented_grammar_prod, all_non_terminals);
                int prod_num = symbol_prod_num.second;
                int symbol_num = symbol_prod_num.first;
                complete_prod.push_back(pair<int, string>(symbol_num,"R"+to_string(prod_num)));
            }
        }
    }
    return complete_prod;
}

void store_in_table(string goto_this_item, int index, char this_column, map<int,map<char,vector<string>>> &slr_table){
    if(if_item_already_exist_in_table(index,slr_table)){
        if(if_symbol_already_exist_in_table(this_column,index,slr_table)){
            slr_table[index][this_column].push_back(goto_this_item);
        }else{
            map<char, vector<string>> cell;
            vector<string> cell_value;
            cell_value.push_back(goto_this_item);
            slr_table[index].insert(pair<char, vector<string>>(this_column,cell_value));

        }
    }else{
        map<char, vector<string>> cell;
        vector<string> cell_value;
        cell_value.push_back(goto_this_item);
        cell.insert(pair<char, vector<string>>(this_column,cell_value));
        slr_table.insert(pair<int,map<char,vector<string>>>(index,cell));
    }
}
