#ifndef _XCEX_ASSIST_H_
#define _XCEX_ASSIST_H_
#include <string>
#include <iostream>
#include <sstream>
#include "mregex.h"
using std::string;
using std::istringstream;
using std::stringstream;
using std::cout;
string mmakestring(char c){
string t(1,c);return t;}
template <class T>
T strtonum(const string& str){
istringstream iss(str);
T num;
iss>>num;
return num;}
bool xaisnum(string str)
{stringstream sin(str);
 double d;
 char c;
if(!(sin>>d))
return 0;
if(sin>>c)
return 0;
return 1;
}
bool xaischar(char c){
int a=(int)c;
return (a>=65&&a<=90)||
       (a>=97&&a<=127);
}
bool xaislistindex(string a)
{
string::iterator it=a.begin();
regex reg("[a-zA-Z]\w*(\\[[a-zA-Z0-9]*\\]){1,}");
if(regex_match((char*)a.c_str(),&reg)&&(*it)!='['&&(*it)!='\"')
{return true;}
else{return false;}
/*string::iterator it=a.begin();
for(;(*it)!='[';it++){
if(xaischar(*it)){}
else {return false;}
}it++;
string num;
for(;(*it)!=']';it++)
{num+=mmakestring(*it);}
return ((*it)==']')&&(it==a.end()-1);
*/}
bool xaislore(string a){
string::iterator it=a.begin();
while(*it!='<'){
if((*it)=='<'){break;}
else if(!xaischar(*it)){return false;}
it++;
}
it++;if(*it!='='){return false;}
it++;string num="";
for(;it!=a.end();it++)
{num+=mmakestring(*it);}
return xaisnum(num);
}
#endif
