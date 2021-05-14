#include "../../header/ll1parser.h"

void find_first(char index, map<char,production> &list_prod){

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
