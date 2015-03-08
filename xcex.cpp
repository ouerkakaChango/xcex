#include "stdio.h"
#include "string.h"
#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <string>
#include "any.h"
#include "mregex.h"
#include "mfile.h"
#include "xcfunc.h"
#include "xcex_assist.h"
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::pair;
using std::list;
using std::string;
int XC_CONSOLEMODE;
typedef xcvar (*RFUNC)(xcvar);
list<pair<string,RFUNC> > funclist;
list<pair<string,xcvar> > varlist;
void minit();
void mconsole();
void analyse(char* text);

void minit(){
XC_CONSOLEMODE=0;
funclist.push_back(pair<string,RFUNC>("print",xcprint));
funclist.push_back(pair<string,RFUNC>("=",xcassign));
funclist.push_back(pair<string,RFUNC>("exec",xcexec));
funclist.push_back(pair<string,RFUNC>("input",xcinput));
funclist.push_back(pair<string,RFUNC>("+",xcadd));
funclist.push_back(pair<string,RFUNC>("-",xcminus));
funclist.push_back(pair<string,RFUNC>("*",xcmultiply));
funclist.push_back(pair<string,RFUNC>("/",xcdivide));
funclist.push_back(pair<string,RFUNC>("%",xcmod));
funclist.push_back(pair<string,RFUNC>("**",xcpow));
funclist.push_back(pair<string,RFUNC>("itemprint",xcitemprint));
funclist.push_back(pair<string,RFUNC>("getch",xcgetch));
funclist.push_back(pair<string,RFUNC>("if",xcif));
funclist.push_back(pair<string,RFUNC>("for",xcfor));
funclist.push_back(pair<string,RFUNC>("typename",xctypename));
funclist.push_back(pair<string,RFUNC>("color",xccolor));
varlist.push_back(pair<string,xcvar>("endl",xcvar(any("\n"),"xcstr")));
}
int main(int argc,char* argv[]){
minit();
if(argc==1){
XC_CONSOLEMODE=1;
mconsole();}
else if(argc>=3)
{cout<<">>error:too many command-line arguments\n";}
else{
char fname[50];
sprintf(fname,"%s",argv[1]);
regex reg(".*\.xc");
if(!regex_match(fname,&reg))
{cout<<">>error:not .xc file\n";}
else {
ifstream mfile(fname,ios::out);
if(!mfile){
cout<<">>error:fail to open\n";}
else {
char context[10000];
getdic(mfile,context);
analyse(context);
}
}}return 0;}
bool mcheck(char*);
void merror(int i,string name="");
void senanalyse(string,string,string);
void mconsole(){
char linetext[200];
while(1){
cout<<">>";
cin.getline(linetext,199);
if(strcmp(linetext,"quit")==0){break;}
else if(strcmp(linetext,"funclist")==0)
{
list<pair<string,RFUNC> >::iterator its;
for(its=funclist.begin();its!=funclist.end();its++)
{cout<<(*its).first<<endl;}
}
else {analyse(linetext);}
}
cout<<"\n>>Thanks for using.\n>>Author\'s email:2293933523@qq.com\n>>or xcznb@hotmail.com\n";
}

void analyse(char* text){
if(!mcheck(text)){merror(1);return;}
else {
char* ch=text;
string lvar="",funcname="",rvar="";
string mode;bool isstr=false;bool islist=false;
int listnum=0;
while(*ch!='\0'){
if((!isstr)&&(!islist)){
   if(*ch=='('){mode="lvar";}
 else if(*ch=='\n'){}
 else if(*ch==','&&mode=="lvar")
       {mode="funcname";}
 else if(*ch==','&&mode=="funcname")
       {mode="rvar";}
 else if(*ch==')')
       {mode="senend";}
 else  { if(*ch=='\"'&&*(ch-1)!='\\')
         {isstr=!isstr;}
         if(*ch=='['){islist=!islist;}
       if(mode=="lvar"){lvar+=mmakestring(*ch);}
         else if(mode=="funcname"){funcname+=mmakestring(*ch);}
         else if(mode=="rvar"){rvar+=mmakestring(*ch);}
       }
}
else if(isstr){
if(*ch=='\n'){}
else{rvar+=makestring(*ch);}
if((*ch=='\"'&&*(ch-1)!='\\')||*ch==']'){isstr=!isstr;}
}
else if(islist){
if(*ch=='\n'){}
else {rvar+=makestring(*ch);}
if(*ch=='['){listnum++;}
else if(*ch==']'&&listnum!=0){listnum--;}
else if(*ch==']'&&listnum==0){islist=!islist;}
}
if(mode=="senend")
              {
   senanalyse(lvar,funcname,rvar);
    lvar="";funcname="";rvar="";
     mode="";
               }
ch++;
     }
}
}
//@@@@@
bool mcheck(char* ch){
int i=0,j=0;bool isstr=false;
bool islist=false;
int listnum=0;
while(*ch!='\0'){
if((!isstr)&&(!islist)){
if(*ch=='\"'&&*(ch-1)!='\\')
{isstr=!isstr;}
if(*ch=='[')
{islist=!islist;}
if(*ch=='('){i++;}
if(*ch==','){j++;}
if(*ch==')'){i--;
  if(i==0&&j==2){j=0;}
  else {return 0;}
           }
       }
else if(isstr){if(*ch=='\"'&&*(ch-1)!='\\')
       {isstr=!isstr;}
     }
else if(islist){
if(*ch=='['){listnum++;}
else if(*ch==']'&&listnum!=0){listnum--;}
else if(*ch==']'&&listnum==0){islist=!islist;}
             }
ch++;
}
if(j==0&&i==0){return 1;}
else {return 0;}
}
void merror(int i,string name){
switch(i){
case 1:
cout<<">>parase error:something about punctuation.\n";
break;
case 2:
cout<<">>var error:No var called \'"<<name<<"\' .\n";
default:break;
}
}
RFUNC realfunc(string funcname){
list<pair<string,RFUNC> >::iterator it=funclist.begin(); 
for(;it!=funclist.end();it++)
{if(it->first==funcname){return it->second;} }
cout<<">>error:not found function named \'"<<funcname<<"\'\n";
return xcnullfunc;
}
//@@@@@@@@@@@
xcvar realrval(string rval)
{
if(rval==""){
return xcvar(any(0),"xcnum");}

else if(xaislistindex(rval))
{string::iterator it=rval.begin();
string listname="";
list<string> num;string tnum="";
for(;*(it)!='[';it++){
listname+=mmakestring(*it);
}it+=1;
for(;it!=rval.end();it++){
if((*it)!=']'&&(*it)!='[') 
{tnum+=mmakestring(*it);}
else if((*it)=='['){}
else {num.push_back(tnum);
       tnum="";
     }
}
xcvar mlist=realrval(listname);
if(mlist.second!="xclist")
  {cout<<">>error:No list named \'"<<listname<<"\' .\n";
   return xcvar(any(0),"xcnum");
  }
else
  { xclist tlist=any_cast<xclist>(mlist.first);
  list<string>::iterator numit=num.begin();
 int myyy=0;
 for(;numit!=num.end();numit++)
 {myyy++;
    xcvar t=realrval(*numit);
   int tnum=(int)any_cast<double>(t.first);
      if(tnum>=tlist.size())
      {cout<<">>error:index out of range\n";
       return xcvar(any(0),"xcnum");
       }
    else {
     xclist::iterator kit=tlist.begin();
      for(int i=0;i<tnum;i++)
       {kit++;}
    //list<string>::iterator tem=numit++;
    if(myyy==num.size())
    {return (*kit);}
   else {
if((*kit).second=="xclist")
{
tlist=any_cast<xclist>((*kit).first);
}
else 
{cout<<">>error:too many index number.\n";
return xcvar(any(0),"xcnum");
}
        }
         }
   }//for for
  }
}
else if(xaislore(rval))
{string::iterator it=rval.begin();
string var="",num="";
for(;(*it)!='<';it++)
{var+=mmakestring(*it);}
it++;it++;
for(;it!=rval.end();it++)
{num+=mmakestring(*it);}
xcvar tnum=realrval(var);
if(tnum.second!="xcnum")
{cout<<">>error:wrong type for <= .\n";
 return xcvar(any(0),"xcnum");
}
else {
double a=any_cast<double>(tnum.first);
double b=strtonum<double>(num);
int i=(a<=b);
return xcvar(any(i),"xcnum");
     }
}
else if(*(rval.begin())=='[' && *(rval.end()-1)==']')
{string::iterator it=rval.begin()+1;
 xclist tlist;
 string element="";
 bool isstr=false,islist=false;
 for(;it!=rval.end()-1;it++){
  if((*it)=='['&&!xaischar(*(it-1))&&!isstr){
 islist=true;element+="[";}
  else if(*it==']'&&!isstr)
 {islist=false;element+=']';}
  else if(!islist&&*it=='\"'&&*(it-1)!='\\')
     {isstr=!isstr;
      element+="\"";}
  else if(!islist&&(*it)==','&&!isstr){tlist.push_back(realrval(element));
              element="";}
  else {element+=mmakestring(*it);}
                     }
tlist.push_back(realrval(element));
return xcvar(any(tlist),"xclist");
}
else if(*(rval.begin())=='\"' && *(rval.end()-1)=='\"')
{rval.erase(rval.begin());
 rval.erase(rval.end()-1);
 string::iterator it=rval.begin(),it2;
 for(;it!=rval.end();){
   if((*it)=='\\')
     {it2=it;it++;
        switch(*it){
  case 'n':*it2='\n';break;
  case '\"':*it2='\"';break;
  default :break;
                  }
      it=rval.erase(it);
     }
   else {it++;}
                     }
 return xcvar(any(rval),"xcstr");
}
else if(xaisnum(rval))
{ any b=strtonum<double>(rval);
 return xcvar(b,"xcnum");
}
else {list<pair<string,xcvar> >::iterator it;
for(it=varlist.begin();it!=varlist.end();it++)
{if(it->first==rval){return it->second;}}
merror(2,rval);
return xcvar(any(0),"xcnum");
}
}
//@@@@@@@@@@
void reallvar(string lvar,xcvar result){
if(lvar=="0"||lvar==""){}
else {
list<pair<string,xcvar> >::iterator it;
for(it=varlist.begin();it!=varlist.end();it++)
{  if(lvar==it->first)
   {it->second=result;return;}
}
varlist.push_back(pair<string,xcvar>(lvar,result));
}
}
void senanalyse(string lvar,string funcname,string rval){
reallvar(lvar,(*(realfunc(funcname)))(realrval(rval)) );
}