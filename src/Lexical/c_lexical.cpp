#include "../../header/lexical_header.h"
#include<fstream>
int lexical(){

  ifstream in("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Lexical/program.c");
  string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
//  string contents = "a+(b*c)";
  for(int i=0;i<contents.size();i++){
    cout<<contents[i];
  }
  // cout<<contents;
  vector<string> token_list;
  token_list = get_tokens(contents);
  // system("color A1");
  cout<<endl<<"Following are the tokens generated seperated by spaces : "<<endl;
  string store_in_file;
  for(int i=0;i<token_list.size();i++){
    // store_in_file+=token_list[i]+" ";
    cout<<token_list[i]<<" ";
  }

  // system("color A2");
  cout<<endl<<endl;
  // cout;
  cout<<setw(51)<<setfill('-')<<""<<""<<endl;
  for(int i=0;i<token_list.size();i++){
    cout<<setfill(' ');
    if(is_keyword(token_list[i])){

      store_in_file+=token_list[i]+" : Keyword ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Keyword"<<"|"<<endl;
    }

    else if(is_separator(token_list[i])){
      store_in_file+=token_list[i]+" : Separator ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Separator"<<"|"<<endl;
    }
    else if(is_operator(token_list[i])){
      store_in_file+=token_list[i]+" : Operator ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Operator"<<"|"<<endl;
    }
    else if(is_integer_constant(token_list[i])){
      store_in_file+=token_list[i]+" : Integer ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Integer constant"<<"|"<<endl;
    }else if(is_real_constant(token_list[i])){
      store_in_file+=token_list[i]+" : Real ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Real Number constant"<<"|"<<endl;
    }else if(is_string_constant(token_list[i])){
      store_in_file+=token_list[i]+" : String ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| String constant"<<"|"<<endl;
    }else if(is_char_constant(token_list[i])){
      store_in_file+=token_list[i]+" : Character ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Character constant"<<"|"<<endl;
    }else if(is_identifier(token_list[i])){
      store_in_file+="i : Identifier ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Identifier"<<"|"<<endl;
    }else{
      store_in_file+=token_list[i]+" : Invalid ;\n";
      cout<<left<<setw(5)<<"|"<<left<<setw(20)<<token_list[i]<<left<<setw(25)<<"| Invalid Token"<<"|"<<endl;
    }
    cout<<setw(51)<<setfill('-')<<""<<""<<endl;
  }
  ofstream token_file("/run/media/nadesh/Nadesh/techtoys/qt_c_compiler/c_compiler/src/Lexical/token_list.txt");
  token_file<<store_in_file;
  token_file.close();
  cout<<setfill(' ');
  cout<<endl;

  // cout<<is_identifier("_12asdf");
  return 0;
}


vector<string> get_tokens(string s){
  vector<string> token_list;
  string token;

  for(int i=0;i<s.size();i++){
    string s_i(1,s[i]);
    if(s_i=="\""){
      token = token+s_i;
      i++;
      s_i = s[i];
      // cout<<"nad"<<endl;
      while(s_i!="\""&&s_i!="\n"){
        token = token+s_i;
        i++;
        s_i = s[i];
      }
      if(s_i!="\n")
      token = token+s_i;
      // i++;
      // s_i = s[i];
      token_list.push_back(token);
      token="";
      continue;
    }
    if(is_arth_operator(s_i)||is_assign_operator(s_i,1)||is_separator(s_i)||is_comparison(s_i,1)||is_logical(s_i,1)||is_bitwise(s_i)||is_pointer_check(s_i)){
      if(s_i=="."){
        // string first_char(1,token[0]);
        if(is_digit(token[0])){
          token = token+s_i;
          continue;
        }
      }
      if(token.size()!=0)
        token_list.push_back(token);
      token = "";

      if(i!=s.size()-2){
        string size3_op=s_i;
        string second_op(1,s[i+1]);
        string third_op(1,s[i+2]);
        size3_op = size3_op + second_op +third_op;

        if(is_assign_operator(size3_op,3)){
          token_list.push_back(size3_op);

          i++;
          i++;
          continue;

        }
      }
      if(i!=s.size()-1){

        string size2_op=s_i;
        string extra_op(1,s[i+1]);
        size2_op +=extra_op;

        if(is_inc_dec_op(size2_op)||is_logical(size2_op,2)||is_assign_operator(size2_op,2)||is_comparison(size2_op,2)){
          token_list.push_back(size2_op);
          i++;
          continue;
        }

      }

      token_list.push_back(s_i);

    }
    else if(s_i==" "){
      if(token.size()!=0)
        token_list.push_back(token);
      token = "";
    }
    else{
      if(s[i+1]=='\0'){
        if(token.size()!=0){
          token_list.push_back(token);
        }
        token = "";
      }
    }

    if(s_i!=" "&&s_i!="\n"&&!(is_arth_operator(s_i)||is_assign_operator(s_i,1)||is_separator(s_i)||is_comparison(s_i,1)\
    ||is_logical(s_i,1)||is_bitwise(s_i)||is_pointer_check(s_i)))
      token = token + s_i;



  }
  return token_list;
}


bool is_digit(char check){
  vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
  for(int i=0;i<digits.size();i++){
    if(check == digits[i]){
      return true;
    }
  }
  return false;
}


bool is_hexa(char check){
  vector<char> hexa_char={'a','b','c','d','e','f','A','B','C','D','E','F'};
  for(int i=0;i<hexa_char.size();i++){
    if(check == hexa_char[i]){
      return true;
    }
  }
  return false;
}

bool is_octal(char check){
  vector<char> digits = {'0','1','2','3','4','5','6','7'};
  for(int i=0;i<digits.size();i++){
    if(check == digits[i]){
      return true;
    }
  }
  return false;
  return false;
}

bool is_operator(string char_check){
  if(char_check.size()==1){
    if(is_arth_operator(char_check)||is_assign_operator(char_check,1)||is_separator(char_check)||is_comparison(char_check,1)||\
    is_logical(char_check,1)||is_bitwise(char_check)||is_pointer_check(char_check))
      return true;
  }else if (char_check.size()==2){
    if(is_inc_dec_op(char_check)||is_logical(char_check,2)||is_assign_operator(char_check,2)||is_comparison(char_check,2)){
      return true;
    }
  }else if (char_check.size()==3){
    if(is_assign_operator(char_check,3)){
      return true;
    }

  }
  return false;
}

bool check_in(vector<string> arr,string check){
  for(int i = 0;i<arr.size();i++){
    if(arr[i]==check){
      return true;
    }
  }
  return false;
}
bool is_arth_operator(string char_check){
  vector<string> op_arr = {"+","-","/","*","%"};
  return check_in(op_arr,char_check);
}
bool is_assign_operator(string char_check, int size){
  vector<string> assign_arr;
  if(size==1)
    assign_arr = {"="};
  else if(size==2)
    assign_arr = {"+=","-=","/=","*=","%=","&=","|=","^="};
  else
    assign_arr = {">>=","<<="};

  return check_in(assign_arr,char_check);
}
bool is_inc_dec_op(string char_check){
  vector<string> op_arr = {"++","--"};

  return check_in(op_arr,char_check);
}
bool is_comparison(string str_check,int size){
  vector<string> comp_arr;
  if(size==1)
    comp_arr = {">","<"};
  else
    comp_arr = {"==",">=","<=","!="};
  return check_in(comp_arr,str_check);
}

bool is_logical(string str_check,int size){
  vector<string> log_arr;
  if(size==1)
    log_arr = {"!"};
  else
  log_arr = {"&&","||"};

  return check_in(log_arr,str_check);
}

bool is_bitwise(string str_check){
  vector<string> log_arr = {"&","|","^","~"};
  return check_in(log_arr,str_check);
}

bool is_pointer_check(string str_check){
  vector<string> log_arr = {"*"};
  return check_in(log_arr,str_check);
}

bool is_keyword(string str_check){
  vector<string> keyword_arr = {"auto","double","int","struct","break","else","long","switch","case","enum","register","typedef",\
  "char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile"\
  "do","if","static","while"};
  return  check_in(keyword_arr,str_check);
}

bool is_separator(string char_check){
  vector<string> sep_arr = {"[" , "]" , "{" , "}" , "(" , ")" , " , " , "." , ";" , ":"};
  return check_in(sep_arr,char_check);
}

//constants
bool is_constant(string str_check){
  if(is_integer_constant(str_check)||is_string_constant(str_check)||is_char_constant(str_check)||is_real_constant(str_check)){
    return true;
  }
  return false;
}
bool is_integer_constant(string str_check){
  int current_state = 0;
  int size = str_check.size();
  int i=0;

  while(size>=0){
    // cout<<current_state<<" "<<str_check[i]<<endl;
    switch (current_state) {
      case 0:
        if(str_check[i]=='0'){
          current_state=1;
        }else if(is_digit(str_check[i])){
          current_state=5;
        }else{
          return false;
        }
        break;
      case 1:
        if(size==0){
          return true;
        }else if(is_octal(str_check[i])){
          current_state=4;
        }else if(str_check[i]=='x'||str_check[i]=='X'){
          current_state=2;
        }else{
          return false;
        }
        break;
      case 2:
        if(str_check[i]=='u'||str_check[i]=='U'){
          current_state=5;
        }
        else if(str_check[i]=='L'||str_check[i]=='l'){
        	current_state=6;
        }
        else if(size==0){
          return true;
        }else if(is_digit(str_check[i])||is_hexa(str_check[i])){
          current_state=2;
        }else{
          return false;
        }
        break;
      case 3:
        if(size==0){
          return true;
        }
        if(str_check[i]=='u'||str_check[i]=='U'	){
          current_state=5;
        }else if(str_check[i]=='L'||str_check[i]=='l'){
        	current_state=6;
        }
        else if(is_octal(str_check[i])){
          current_state=3;
        }else{
          return false;
        }
        break;
      case 4:
        if(size==0){
          return true;
        }else if(is_digit(str_check[i])){
          current_state=4;
        }else if(str_check[i]=='u'||str_check[i]=='U'){
          current_state=5;
        }else if(str_check[i]=='L'||str_check[i]=='l'){
        	current_state=6;
        }else{
          return false;
        }
        break;
      case 5:
        if(size==0){
          return true;
        }else if(str_check[i]=='L'||str_check[i]=='l'){
        	current_state=6;
        }else{
          return false;
        }
        break;
      case 6:
        if(size==0){
          return true;
        }else if(str_check[i]=='L'||str_check[i]=='l'){
        	current_state=7;
        }else{
          return false;
        }
        break;
      case 7:
        if(size==0){
          return true;
        }else{
          return false;
        }
        break;
    }
    size--;
    i++;
  }
  return false;
}
bool is_real_constant(string str_check){
  int current_state = 0;
  int size = str_check.size();
  int i=0;

  while(size>=0){
    switch (current_state) {
      case 0:
          if(is_digit(str_check[i])&&str_check[i]!=0){
            current_state=0;
          }else if(str_check[i]=='.'){
            current_state=1;
          }else if(str_check[i]=='f'||str_check[i]=='F'||str_check[i]=='l'||str_check[i]=='L'){
          	current_state=3;
          }else if(str_check[i]=='e'||str_check[i]=='E'){
          	current_state=2;
          }else{
            return false;
          }
        break;
      case 1:
        if(is_digit(str_check[i])){
        	current_state=1;
        }else if(size==0){
          return true;
        }else if(str_check[i]=='f'||str_check[i]=='F'||str_check[i]=='l'||str_check[i]=='L'){
          	current_state=3;

        }else{
          return false;
        }
        break;
       case 2:
        if(is_digit(str_check[i])||str_check[i]=='+'||str_check[i]=='-'){
        	current_state=1;
        }else{
            return false;
        }
       case 3:
       if(size==0)
       		return true;
       else
       		return false;
        break;


    }
    i++;
    size--;
  }
  return false;
}
bool is_string_constant(string str_check){
  int current_state = 0;
  int size = str_check.size();
  int i=0;

  while(size>=0){
    switch (current_state) {
      case 0:
        if(str_check[i]=='"'){
          current_state=1;
        }else{
          return false;
        }
        break;
      case 1:
        if(str_check[i]=='"'){
          current_state=2;
        }else{
          current_state=1;
        }
        break;
      case 2:
        if(size==0){
          return true;
        }else{
          return false;
        }
        break;
    }
    i++;
    size--;
  }
  return false;
}
bool is_char_constant(string str_check){
  int current_state = 0;
  int size = str_check.size();
  int i=0;

  while(size>=0){
    switch (current_state) {
      case 0:
        if(str_check[i]=='\''){
          current_state=1;
        }else{
          return false;
        }
        break;
      case 1:
      	if((str_check[i]>='a'&&str_check[i]<='z')||(str_check[i]>='A'&&str_check[i]<='Z'))
        	current_state=3;
        else if(str_check[i]=='\\')
        	current_state=2;
        else
        	false;
        break;
      case 2:
        if(str_check[i]=='\\'||(str_check[i]>='a'&&str_check[i]<='z')||(str_check[i]>='A'&&str_check[i]<='Z')){
          current_state=3;
        }else{
          return false;
        }
        break;
  	  case 3:
        if(str_check[i]=='\''){
          current_state=4;
        }else{
          return false;
        }
        break;
      case 4:
        if(size==0){
          return true;
        }else{
        	return false;
        }
    }
    i++;
    size--;
  }
  return false;
}

bool is_identifier(string str_check){
  int current_state = 0;
  int size = str_check.size();
  int i=0;
  while(size>=0){
    switch (current_state) {
      case 0:
        if(size==0){
          return true;
        }else if((str_check[i]>='a'&&str_check[i]<='z')||(str_check[i]>='A'&&str_check[i]<='Z')||str_check[i]=='_'){
          current_state=1;
        }else{
          return false;
        }
        break;
      case 1:
        if(size==0){
          return true;
        }else if((str_check[i]>='a'&&str_check[i]<='z')||(str_check[i]>='A'&&str_check[i]<='Z')||(str_check[i]>='0'&&str_check[i]<='9')||str_check[i]=='_'){
          current_state=1;
        }else{
          return false;
        }
        break;
    }
    i++;
    size--;

  }
  return false;
}
