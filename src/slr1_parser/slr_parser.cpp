#include"header/slr1_parser.h"





void reduce_moves(map<int,map<char,vector<string>>> &slr_table, vector<map<char,production>> items, map<char,production> augmented_grammar_prod, vector<char> all_non_terminals){
    vector<pair<int, string>> reduce_list;
    for(int i=0;i<items.size();i++){
        reduce_list = find_complete_production(items[i], augmented_grammar_prod,all_non_terminals);


        for(int j=0;j<reduce_list.size();j++){
            int symbol_num = reduce_list[j].first;
//            cout<<reduce_list[j].second<<", "<<all_non_terminals[symbol_num]<<" ";
//            cout<<
            for(int k=0;k<augmented_grammar_prod[all_non_terminals[symbol_num]].follow.size();k++){
                char symbol_follow = augmented_grammar_prod[all_non_terminals[symbol_num]].follow[k];
//                cout<<i<<" "<<symbol_follow<<endl;
                slr_table[i][symbol_follow].push_back(reduce_list[j].second);
            }

        }
//        cout<<endl;
    }

}
void find_closure(char closure_symbol, map<char,production> grammar_prod, map<char, production> &item_grammar){
//    map<char, production> item_grammar;
    vector<char> closed_symbols;
//    cout<<closure_symbol<<" ";
    if(grammar_prod[closure_symbol].is_closed != 2){

        production some_symbol;
        some_symbol.name = closure_symbol;
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
//                    cout<<grammar_prod[closure_symbol].prod[i][0]<<endl;
                    closed_symbols.push_back(grammar_prod[closure_symbol].prod[i][0]);
                    grammar_prod[grammar_prod[closure_symbol].prod[i][0]].is_closed=1;
                }
            }
            some_symbol.prod.push_back(item_prod);
        }
        grammar_prod[closure_symbol].is_closed=2;
//        item_grammar[closure_symbol].prod.push_back()
//        item_grammar.insert(pair<char,production>(closure_symbol,some_symbol));
        if(if_symbol_already_present(closure_symbol,item_grammar)){
            for(int i=0;i<some_symbol.prod.size();i++){
                item_grammar[closure_symbol].prod.push_back(some_symbol.prod[i]);
            }

        }else{
            item_grammar.insert(pair<char,production>(closure_symbol,some_symbol));
        }
    }
//    cout<<closed_symbols.size()<<endl;
    for(int i=0;i<closed_symbols.size();i++){
        find_closure(closed_symbols[i],grammar_prod,item_grammar);
    }
}

map<char, production> generate_item0(map<char,production> grammar_prod, vector<char> all_non_terminals){
    map<char, production> item_grammar;

    string item_prod;
    item_prod+=".";
    item_prod+=grammar_prod[all_non_terminals[0]].prod[0];
    production item_0_prod;
    item_0_prod.name = all_non_terminals[0];
    item_0_prod.prod.push_back(item_prod);
    item_0_prod.start_symbol=2;
    item_grammar.insert(pair<char, production >(all_non_terminals[0],item_0_prod));
    find_closure(all_non_terminals[1],grammar_prod, item_grammar);



    return item_grammar;
}





void goto_function(map<char, production> item_grammar, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals, int index, map<int,map<char,vector<string>>> &slr_table){
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
//                                cout<<"Nadesh";
//                                cout<<endl<<all_non_terminals[i]<<"->"<<item_grammar[all_non_terminals[i]].prod[j]<<" ";
                                string item_prod = item_grammar[all_non_terminals[i]].prod[j];
                                char temp = item_prod[k-1];
                                item_prod[k-1] = item_prod[k];
                                item_prod[k]=temp;
                                goto_symbol.name=all_non_terminals[i];
                                goto_symbol.prod.push_back(item_prod);
                                if(k!=item_prod.size()-1){
                                    if(is_non_terminal(item_prod[k+1])){

                                        find_closure(item_prod[k+1],augmented_grammar_prod, other_item_grammar);
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
                        other_item_grammar[goto_symbol.name].prod.push_back(goto_symbol.prod[i]);
                    }

                }else{
                    other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                }
            }
        }


    if(flag==1){
        int same_flag = is_same_grammar(other_item_grammar,items);
        if(same_flag==-1){
            items.push_back(other_item_grammar);
            string goto_this_item;
            goto_this_item+=to_string(items.size()-1);
            store_in_table(goto_this_item,index,all_non_terminals[l],slr_table);
        }else{
            //                cout<<all_non_terminals[l]<<" "<<same_flag<<", ";
            string goto_this_item;
            goto_this_item+=to_string(same_flag);
            store_in_table(goto_this_item,index,all_non_terminals[l],slr_table);
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
                            //                        cout<<"Nadesh";
                            if(k!=0){
                                //                            cout<<"Nadesh";
                                if(item_grammar[all_non_terminals[i]].prod[j][k-1]=='.'){
                                    //                                cout<<"Nadesh";
                                    string item_prod = item_grammar[all_non_terminals[i]].prod[j];
                                    char temp = item_prod[k-1];
                                    item_prod[k-1] = item_prod[k];
                                    item_prod[k]=temp;
                                    goto_symbol.name=all_non_terminals[i];
                                    goto_symbol.prod.push_back(item_prod);
                                    if(k!=item_prod.size()-1){
                                        if(is_non_terminal(item_prod[k+1])){
                                            find_closure(item_prod[k+1],augmented_grammar_prod, other_item_grammar);
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
                            other_item_grammar[goto_symbol.name].prod.push_back(goto_symbol.prod[i]);
                        }

                    }else{
                        other_item_grammar.insert(pair<char,production>(goto_symbol.name,goto_symbol));
                    }
                }
            }

            if(flag==1){
                int same_flag = is_same_grammar(other_item_grammar,items);
                if(same_flag==-1){
                    items.push_back(other_item_grammar);
                    string goto_this_item;
                    goto_this_item+="S"+to_string(items.size()-1);
                    store_in_table(goto_this_item,index,all_terminals[l],slr_table);
                }else{
                    string goto_this_item = "S";
                    goto_this_item +=to_string(same_flag);
                    store_in_table(goto_this_item,index,all_terminals[l],slr_table);
                }
            }


    }

}





void generate_lr0_items(map<int,map<char,vector<string>>> &slr_table, map<char,production> augmented_grammar_prod, vector<map<char,production>> &items, vector<char> all_non_terminals, vector<char> all_terminals){
//    all_non_terminals[0];
    map<char, production> item_grammar;

    item_grammar = generate_item0(augmented_grammar_prod, all_non_terminals);
    items.push_back(item_grammar);

    for(int i=0;i<items.size();i++){

        goto_function(items[i],augmented_grammar_prod,items,all_non_terminals,all_terminals,i,slr_table);

    }

    reduce_moves(slr_table, items, augmented_grammar_prod, all_non_terminals);


}



void initializing_slr(){
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
    map<int,map<char,vector<string>>> slr_table;
    generate_lr0_items(slr_table, augmented_grammar_prod, items, all_non_terminals, all_terminals);

    cout<<endl<<endl<<"LR(0) ITEMS : "<<endl<<endl;
    for(int i=0;i<items.size();i++){
        cout<<"Item "<<i<<" "<<endl;
        for(int j=0;j<all_non_terminals.size();j++){
            if(items[i][all_non_terminals[j]].prod.size()>0){
                cout<<all_non_terminals[j]<<" -> ";
                for(int k=0;k<items[i][all_non_terminals[j]].prod.size();k++){
                    if(k!=items[i][all_non_terminals[j]].prod.size()-1)
                        cout<<items[i][all_non_terminals[j]].prod[k]<<" |";
                    else
                        cout<<items[i][all_non_terminals[j]].prod[k];
                }
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

    draw_table(slr_table,items,all_symbols);
    if(duplicate_entries(slr_table)){
        cout<<endl<<"Grammar cannot be parsed by SLR(1) table"<<endl;
        return;
    }
    string parsing_string;
    cout<<endl<<"String to parse : ";
    cin>>parsing_string;
    if(parse_slr_string(parsing_string,augmented_grammar_prod,slr_table,all_non_terminals)){
        cout<<endl<<"String is Parsed"<<endl;
    }else{
        cout<<endl<<"String cannot be parsed"<<endl;
    }
    cout<<endl<<endl;
}



