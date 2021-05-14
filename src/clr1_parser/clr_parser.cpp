#include "header/clr1_parser.h"

void insert_charvector_in_vector(vector<char> provider, vector<char> &storing_list){
    for(int i=0;i<provider.size();i++){
        push_char(storing_list, provider[i]);
    }
}

vector<char> find_lookahead(string lookahead_string, char lookahead_of_this_symbol, map<char, production> grammar_prod, map<char, production> item_grammar){
    vector<char> new_lookaheads;

    for(int i=0;i<item_grammar[lookahead_of_this_symbol].k_lookahead.size();i++){
        string char_to_string(1, item_grammar[lookahead_of_this_symbol].k_lookahead[i]);
        string new_look = lookahead_string;
        new_look+=char_to_string;
        vector<char> first_list;
        find_first_of_string(new_look, first_list, 0, grammar_prod);
        for(int j=0;j<first_list.size();j++){
            if(first_list[j]!='#'){
                push_char(new_lookaheads, first_list[j]);
            }
        }
    }

    return new_lookaheads;
}
int is_same_clr_grammar(map<char,production> grammar_prod, vector<map<char,production>> items){
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
                    if(items[i][itr->first].k_lookahead.size() == grammar_prod[itr->first].k_lookahead.size()){
                       sort(items[i][itr->first].k_lookahead.begin(), items[i][itr->first].k_lookahead.end());
                       sort(grammar_prod[itr->first].k_lookahead.begin(), grammar_prod[itr->first].k_lookahead.end());
                       if(items[i][itr->first].k_lookahead != grammar_prod[itr->first].k_lookahead){
                           is_same_flag=0;
                           break;
                       }
                    }else{
                        is_same_flag=0;
                        break;
                    }
                }else {
                    is_same_flag=0;
                    break;
                }

            }
            if(is_same_flag){
                return i;
            }
    }
    return -1;

}


bool is_char_string_already_present(string some, vector<string> list){
    for(int i=0;i<list.size();i++){
        if(some==list[i]){
            return true;
        }
    }
    return false;
}


void find_closure_clr(char closure_symbol, map<char,production> grammar_prod, map<char, production> &item_grammar, char lookahead_of_this_symbol, string lookahead_string){
    vector<pair<char, string>> closed_symbols;
    vector<char> new_lookaheads;

    new_lookaheads = find_lookahead(lookahead_string,lookahead_of_this_symbol,grammar_prod, item_grammar);

    if(grammar_prod[closure_symbol].is_closed != 2){

        production some_symbol;
        some_symbol.name = closure_symbol;
        insert_charvector_in_vector(new_lookaheads, some_symbol.k_lookahead);
        for(int i=0;i<grammar_prod[closure_symbol].prod.size();i++){
            string item_prod;
            if(grammar_prod[closure_symbol].prod[i]!="#"){
                item_prod+=".";
                item_prod+=grammar_prod[closure_symbol].prod[i];


            }else{
                item_prod=".";
            }
            if(is_non_terminal(grammar_prod[closure_symbol].prod[i][0])){

                if(grammar_prod[grammar_prod[closure_symbol].prod[i][0]].is_closed ==0){
                    string new_lookahead_string = grammar_prod[closure_symbol].prod[i];
                    new_lookahead_string.erase(0,1);
                    closed_symbols.push_back(make_pair(grammar_prod[closure_symbol].prod[i][0], new_lookahead_string));
                    grammar_prod[grammar_prod[closure_symbol].prod[i][0]].is_closed=1;
                }
                if(grammar_prod[closure_symbol].prod[i][0]==closure_symbol){
                    string new_lookahead_string = grammar_prod[closure_symbol].prod[i];
                    new_lookahead_string.erase(0,1);
                    vector<char> new_lookaheads = find_lookahead(new_lookahead_string,lookahead_of_this_symbol,grammar_prod, item_grammar);
                    insert_charvector_in_vector(new_lookaheads, some_symbol.k_lookahead);
                }

            }
            some_symbol.prod.push_back(item_prod);
        }
        grammar_prod[closure_symbol].is_closed=2;

        if(if_symbol_already_present(closure_symbol,item_grammar)){
            for(int i=0;i<some_symbol.prod.size();i++){
                push_production(item_grammar[closure_symbol].prod, some_symbol.prod[i]);
            }

        }else{
            item_grammar.insert(pair<char,production>(closure_symbol,some_symbol));
        }
    }
    for(int i=0;i<closed_symbols.size();i++){
        find_closure_clr(closed_symbols[i].first,grammar_prod,item_grammar, closure_symbol, closed_symbols[i].second);
    }
}

map<char, production> generate_clr_item0(map<char,production> grammar_prod, vector<char> all_non_terminals){
    map<char, production> item_grammar;

    string item_prod;
    item_prod+=".";
    item_prod+=grammar_prod[all_non_terminals[0]].prod[0];
    string lookahead_string=grammar_prod[all_non_terminals[0]].prod[0];
    lookahead_string.erase(0,1);
    production item_0_prod;
    item_0_prod.name = all_non_terminals[0];
    item_0_prod.prod.push_back(item_prod);
    item_0_prod.start_symbol=2;
    item_0_prod.k_lookahead.push_back('$');
    item_grammar.insert(pair<char, production >(all_non_terminals[0],item_0_prod));
//    find_lookahead(all_non_terminals[0],);
    vector<char> recent_lookaheads;
    recent_lookaheads.push_back('$');
    char lookahead_of_this_symbol = all_non_terminals[0];
    find_closure_clr(all_non_terminals[1],grammar_prod, item_grammar, lookahead_of_this_symbol, lookahead_string);



    return item_grammar;
}

void goto_function_clr(map<char, production> item_grammar, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals, int index, map<int,map<char,vector<string>>> &clr_table){
//    cout<<endl<<"Non Terminals"<<endl;
    for(int l=0;l<all_non_terminals.size();l++){
//        cout<<all_non_terminals[l]<<" ";

        map<char, production> other_item_grammar;
        int flag=0;
        for(int i=0;i<all_non_terminals.size();i++){
            production goto_symbol;
            for(int j=0;j<item_grammar[all_non_terminals[i]].prod.size();j++){

                for(int k=0;k<item_grammar[all_non_terminals[i]].prod[j].size();k++){
//                cout<<"Nadesh";
                    if(all_non_terminals[l]==item_grammar[all_non_terminals[i]].prod[j][k]){
//                        cout<<"Nadesh";
                        if(k!=0){
//                            cout<<"Nadesh";
                            if(item_grammar[all_non_terminals[i]].prod[j][k-1]=='.'){

                                insert_charvector_in_vector(items[index][all_non_terminals[i]].k_lookahead,goto_symbol.k_lookahead);
//                                cout<<"Nadesh";
//                                cout<<endl<<all_non_terminals[i]<<"->"<<item_grammar[all_non_terminals[i]].prod[j]<<" ";
                                string item_prod = item_grammar[all_non_terminals[i]].prod[j];

                                char temp = item_prod[k-1];
                                item_prod[k-1] = item_prod[k];
                                item_prod[k]=temp;
                                goto_symbol.name=all_non_terminals[i];
                                goto_symbol.prod.push_back(item_prod);
                                other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                                if(k!=item_prod.size()-1){
                                    if(is_non_terminal(item_prod[k+1])){
                                        string lookahead_string;
                                        lookahead_string = item_prod;

                                        if(lookahead_string.size()!=0){
                                            while(lookahead_string[0]!='.'){
                                                lookahead_string.erase(0,1);
                                            }

                                            lookahead_string.erase(0,1);
                                            if(lookahead_string.size()!=0){
                                                lookahead_string.erase(0,1);
                                            }
                                        }


                                        find_closure_clr(item_prod[k+1], augmented_grammar_prod, other_item_grammar, all_non_terminals[i], lookahead_string);
                                    }
                                }

                                break;
                            }
                        }
                    }
                }
            }

            if(goto_symbol.prod.size()!=0){

                flag=1;
    //            other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                if(if_symbol_already_present(goto_symbol.name,other_item_grammar)){
                    for(int i=0;i<goto_symbol.prod.size();i++){
                        push_production(other_item_grammar[goto_symbol.name].prod, goto_symbol.prod[i]);
                    }

                }else{
                    other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                }
            }
        }


    if(flag==1){
        int same_flag = is_same_clr_grammar(other_item_grammar,items);
        if(same_flag==-1){
            items.push_back(other_item_grammar);
            string goto_this_item;
            goto_this_item+=to_string(items.size()-1);
            store_in_table(goto_this_item,index,all_non_terminals[l],clr_table);
        }else{
            //                cout<<all_non_terminals[l]<<" "<<same_flag<<", ";
            string goto_this_item;
            goto_this_item+=to_string(same_flag);
            store_in_table(goto_this_item,index,all_non_terminals[l],clr_table);
        }
    }
    }
    for(int l=0;l<all_terminals.size();l++){

//            cout<<all_terminals[l]<<"Terminals"<<endl;
            map<char, production> other_item_grammar;
            int flag=0;
            for(int i=0;i<all_non_terminals.size();i++){
                production goto_symbol;
                for(int j=0;j<item_grammar[all_non_terminals[i]].prod.size();j++){
                    for(int k=0;k<item_grammar[all_non_terminals[i]].prod[j].size();k++){
                        //                cout<<"Nadesh";
                        if(all_terminals[l]==item_grammar[all_non_terminals[i]].prod[j][k]){
//                                                    cout<<"Nadesh";
                            if(k!=0){
//                                                            cout<<"Nadesh";
                                if(item_grammar[all_non_terminals[i]].prod[j][k-1]=='.'){
                                    insert_charvector_in_vector(items[index][all_non_terminals[i]].k_lookahead,goto_symbol.k_lookahead);
//                                                                    cout<<"Nadesh";
                                    string item_prod = item_grammar[all_non_terminals[i]].prod[j];

                                    char temp = item_prod[k-1];
                                    item_prod[k-1] = item_prod[k];
                                    item_prod[k]=temp;
                                    goto_symbol.name=all_non_terminals[i];
                                    goto_symbol.prod.push_back(item_prod);
                                    other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                                    if(k!=item_prod.size()-1){
                                        if(is_non_terminal(item_prod[k+1])){
                                            string lookahead_string;
                                            lookahead_string = item_prod;
                                            if(lookahead_string.size()!=0){
                                                while(lookahead_string[0]!='.'){
                                                    lookahead_string.erase(0,1);
                                                }

                                                lookahead_string.erase(0,1);
                                                if(lookahead_string.size()!=0){
                                                    lookahead_string.erase(0,1);
                                                }
                                            }
                                            find_closure_clr(item_prod[k+1], augmented_grammar_prod, other_item_grammar, all_non_terminals[i], lookahead_string);
                                        }
                                    }

                                    break;
                                }
                            }
                        }
                    }


                }

                if(goto_symbol.prod.size()!=0){
                    flag=1;
                    if(if_symbol_already_present(goto_symbol.name,other_item_grammar)){
                        for(int i=0;i<goto_symbol.prod.size();i++){
                            push_production(other_item_grammar[goto_symbol.name].prod, goto_symbol.prod[i]);

                        }

                    }else{
                        other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                    }
                }
            }

            if(flag==1){
                int same_flag = is_same_clr_grammar(other_item_grammar,items);
                if(same_flag==-1){
                    items.push_back(other_item_grammar);
                    string goto_this_item;
                    goto_this_item+="S"+to_string(items.size()-1);
                    store_in_table(goto_this_item,index,all_terminals[l],clr_table);
                }else{
                    string goto_this_item = "S";
                    goto_this_item +=to_string(same_flag);
                    store_in_table(goto_this_item,index,all_terminals[l],clr_table);
                }
            }


    }
//    cout<<endl<<endl;

}
void reduce_moves_clr(map<int,map<char,vector<string>>> &clr_table, vector<map<char,production>> items, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals){
    vector<pair<int, string>> reduce_list;
    for(int i=0;i<items.size();i++){
//        cout<<i<<endl;
        reduce_list = find_complete_production(items[i], augmented_grammar_prod,all_non_terminals);
        for(int j=0;j<reduce_list.size();j++){
            int symbol_num = reduce_list[j].first;
            for(int k=0;k<items[i][all_non_terminals[symbol_num]].k_lookahead.size();k++){
                char symbol_follow = items[i][all_non_terminals[symbol_num]].k_lookahead[k];

                clr_table[i][symbol_follow].push_back(reduce_list[j].second);
            }

        }
    }

}

void generate_lr1_items_clr(map<int,map<char,vector<string>>> &clr_table, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals){
    map<char, production> item_grammar;
    item_grammar = generate_clr_item0(augmented_grammar_prod, all_non_terminals);
    items.push_back(item_grammar);

    for(int i=0;i<items.size();i++){
        goto_function_clr(items[i], augmented_grammar_prod, items, all_non_terminals, all_terminals, i, clr_table);
    }
    reduce_moves_clr(clr_table, items, augmented_grammar_prod, all_non_terminals);
}

void merge_items(vector<map<char,production>> &items){
    vector<pair<int, int>> index_list;
    for(int i=0;i<items.size();i++){
        int index = is_same_grammar(items[i],items);

        if(index!=-1 && index!=i){
            index_list.push_back(make_pair(i,index));
        }
    }
    for(int i=0;i<index_list.size();i++){
        for(auto itr = items[index_list[i].first].begin();itr!=items[index_list[i].first].end();itr++){
            insert_charvector_in_vector(items[index_list[i].second][itr->first].k_lookahead, items[index_list[i].first][itr->first].k_lookahead);
        }

        items.erase(items.begin()+index_list[i].second);
    }
}

void generate_lr1_items_lalr(map<int,map<char,vector<string>>> &clr_table, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals){
    map<char, production> item_grammar;
    item_grammar = generate_clr_item0(augmented_grammar_prod, all_non_terminals);
    items.push_back(item_grammar);

    for(int i=0;i<items.size();i++){
        goto_function_clr(items[i], augmented_grammar_prod, items, all_non_terminals, all_terminals, i, clr_table);
    }
    merge_items(items);
    reduce_moves_clr(clr_table, items, augmented_grammar_prod, all_non_terminals);
}




void initialize_clr(){
    map<char,production> grammar_prod;
    vector<char> all_non_terminals;

    string contents = import_grammar(grammar_prod,all_non_terminals);

    generate_grammar_general(contents,grammar_prod,all_non_terminals);
    vector<char> all_terminals;
    find_all_terminals(grammar_prod,all_terminals, all_non_terminals);

    map<char,production> augmented_grammar_prod=grammar_prod;
    create_augmented_grammar(augmented_grammar_prod,all_non_terminals);

    for(int i=0;i<all_non_terminals.size();i++){
        find_first(all_non_terminals[i], augmented_grammar_prod);
    }
    augmented_grammar_prod[all_non_terminals[0]].follow.push_back('$');
    for(int i=0;i<all_non_terminals.size();i++){
        find_follow(all_non_terminals[i], augmented_grammar_prod,augmented_grammar_prod[all_non_terminals[i]].follow,all_non_terminals);

    }
//  string
//    string any = augmented_grammar_prod[all_non_terminals[2]].prod[0];
//    vector<char> first_list;
//    find_first_of_string(any, first_list,0, augmented_grammar_prod);
//    cout<<endl<<any<<endl;

//    for(int i=0;i<first_list.size();i++){
//        cout<<first_list[i]<<" ";
//    }
//    cout<<endl<<endl;
    cout<<endl<<"Augmented Grammar"<<endl;
    cout<<endl;
    cout<<setw(20)<<left<<" "<<setw(20)<<"First"<<setw(20)<<"Follow"<<endl<<endl;

    for(int i=0;i<all_non_terminals.size();i++){
      string output="";
      // cout<<grammar_prod[i].name;
      string change(1,augmented_grammar_prod[all_non_terminals[i]].name);
      output += change+" -> ";
      // cout<<output;
      for(int j=0;j<augmented_grammar_prod[all_non_terminals[i]].prod.size();j++){
        if(j!=augmented_grammar_prod[all_non_terminals[i]].prod.size()-1)
          output += augmented_grammar_prod[all_non_terminals[i]].prod[j] + "|";
        else
          output += augmented_grammar_prod[all_non_terminals[i]].prod[j];
      }
      cout<<left<<setw(20)<<output;
      output="";
      output+="{";
      for(int j=0;j<augmented_grammar_prod[all_non_terminals[i]].first.size();j++){
        string first_str(1, augmented_grammar_prod[all_non_terminals[i]].first[j]);
        if(j!=augmented_grammar_prod[all_non_terminals[i]].first.size()-1)
          output+= first_str+",";
        else
          output+= first_str;
      }
      output+="}";

      cout<<left<<setw(20)<<output;
    // cout<<endl;}
      output="";
      output+="{";
      for(int j=0;j<augmented_grammar_prod[all_non_terminals[i]].follow.size();j++){
        // cout<<"asdf";

        string follow_str(1, augmented_grammar_prod[all_non_terminals[i]].follow[j]);
        // cout<<follow_str;
        if(j!=augmented_grammar_prod[all_non_terminals[i]].follow.size()-1)
          output+= follow_str+",";
        else
          output+= follow_str;
      }
      output+="}";
      cout<<output;
      cout<<endl;
    }
    cout<<endl<<endl;

    vector<map<char,production>> items;
    map<int,map<char,vector<string>>> clr_table;
    cout<<endl<<"Do you want CLR Parser or LALR Parser ?(Type CLR/LALR)"<<endl;
    string type_of_parser;
    cin>>type_of_parser;
    if(type_of_parser=="LALR"){
        generate_lr1_items_lalr(clr_table, augmented_grammar_prod, items, all_non_terminals, all_terminals);
    }else{
        generate_lr1_items_clr(clr_table, augmented_grammar_prod, items, all_non_terminals, all_terminals);
    }


    cout<<endl<<endl<<"LR(1) ITEMS : "<<endl<<endl;
    for(int i=0;i<items.size();i++){
        cout<<"Item "<<i<<" "<<endl;
        for(int j=0;j<all_non_terminals.size();j++){
            if(items[i][all_non_terminals[j]].prod.size()>0){
                cout<<all_non_terminals[j]<<" -> ";
                string output="";
                for(int k=0;k<items[i][all_non_terminals[j]].prod.size();k++){
                    if(k!=items[i][all_non_terminals[j]].prod.size()-1)
                        output+=items[i][all_non_terminals[j]].prod[k]+" |";
                    else
                        output+=items[i][all_non_terminals[j]].prod[k];
                }
                cout<<setw(20)<<left<<output;
                output="{ ";
//                cout<<items[i][all_non_terminals[j]].k_lookahead.size();
                for(int k=0;k<items[i][all_non_terminals[j]].k_lookahead.size();k++){
                    string look;
                    look = items[i][all_non_terminals[j]].k_lookahead[k];
                    if(k!=items[i][all_non_terminals[j]].k_lookahead.size()-1)
                        output+=look+",";
                    else{
                        output+=look+" }";
                    }
                }
                cout<<output;
                cout<<endl;
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    vector<char> all_symbols;
    all_symbols = all_terminals;
    all_symbols.push_back('$');
    all_symbols.insert(all_symbols.end(), all_non_terminals.begin()+1,all_non_terminals.end());

    draw_table(clr_table,items,all_symbols);
    if(duplicate_entries(clr_table)){
        cout<<endl<<"Grammar cannot be parsed by SLR(1) table"<<endl;
        return;
    }
    string parsing_string;
    cout<<endl<<"String to parse : ";
    cin>>parsing_string;
    if(parse_clr_string(parsing_string,augmented_grammar_prod,clr_table,all_non_terminals)){
        cout<<endl<<"String is Parsed"<<endl;
    }else{
        cout<<endl<<"String cannot be parsed"<<endl;
    }
    cout<<endl<<endl;

}
