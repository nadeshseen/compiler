#include "../../header/ll1parser.h"

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
void find_first2(char index, map<char,production> &list_prod){

      if(!(list_prod[index].first.empty())){
        for(int j=0;j<list_prod[index].first.size();j++){
          push_char(list_prod[index].first,list_prod[index].first[j]);
        }
        return;
      }else{
        for(int j=0 ; j<list_prod[index].prod.size() ; j++){
          int k=0;
          int epsilon_flag=0;
          do{
            epsilon_flag=0;
            if(!is_non_terminal(list_prod[index].prod[j][k]))
              push_char(list_prod[index].first,list_prod[index].prod[j][k]);
            else
            {
//              int new_index = find_production(list_prod[index].prod[j][k],list_prod);

                    find_first(list_prod[index].prod[j][k], list_prod);
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
