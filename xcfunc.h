#ifndef XCFUNC_H
#define XCFUNC_H
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <math.h>
#include "any.h"
#include "xcex_assist.h"
#include "mygetch.h"
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::list;
typedef pair<any,string> xcvar;
typedef list<xcvar> xclist;
extern int XC_CONSOLEMODE;
int XC_LISTNOW[10];
int XC_LISTNUM=-1;
extern void analyse(char*);
extern xcvar realrval(string);
bool isnotlist(){
for(int i=0;i<10;i++)
{if(XC_LISTNOW[i]==1){return false;}}
return true;}

bool allthetype(xclist tlist){
xclist::iterator it=tlist.begin();
string thetype=it->second;
for(;it!=tlist.end();it++)
{if(it->second!=thetype)
 {return false;}
}
return true;
}
xcvar xcnullfunc(xcvar a){
return xcvar(any(0),"xcnum");}

xcvar xcadd(xcvar a){
if(a.second=="xclist")
 {
xclist tlist=any_cast<xclist>(a.first);
 if(!allthetype(tlist))
   {
   cout<<">>error:elements' types are not the same.\n";
   return xcvar(any(0),"xcnum");
   }
 else 
   {
    xclist::iterator it=tlist.begin();
     if(it->second=="xcnum"||it->second=="xcstr")
       {
any re;
if(it->second=="xcnum")
{re=0;}
else {re="";}
for(;it!=tlist.end();it++)
{re=re+it->first;
}
it=tlist.begin();
return xcvar(re,it->second);
       }
       else 
        {
       cout<<">>error:add doesn't support such type.\n";
       return xcvar(any(0),"xcnum");
        }
   }
 }
else 
 {
cout<<">>error:bad type for add.\n";
return xcvar(any(0),"xcnum");
 }
}
//#########
xcvar xcmultiply(xcvar a){
if(a.second=="xclist")
 {
xclist tlist=any_cast<xclist>(a.first);
 if(!allthetype(tlist))
   {
   cout<<">>error:elements' types are not the same.\n";
   return xcvar(any(0),"xcnum");
   }
 else 
   {
    xclist::iterator it=tlist.begin();
     if(it->second=="xcnum")
       {
any re=it->first;it++;
for(;it!=tlist.end();it++)
{re=re*(any_cast<double>(it->first));
}
return xcvar(re,"xcnum");
       }
       else 
        {
       cout<<">>error:multiply doesn't support such type.\n";
       return xcvar(any(0),"xcnum");
        }
   }
 }
else 
 {
cout<<">>error:bad type for multiply.\n";
return xcvar(any(0),"xcnum");
 }
}
//#########
xcvar xcminus(xcvar a){
if(a.second=="xclist")
 {
xclist tlist=any_cast<xclist>(a.first);
 if(!allthetype(tlist))
   {
   cout<<">>error:elements' types are not the same.\n";
   return xcvar(any(0),"xcnum");
   }
 else 
   {
    xclist::iterator it=tlist.begin();
     if(it->second=="xcnum")
       {
any re=it->first;
it++;
for(;it!=tlist.end();it++)
{re=re-any_cast<double>(it->first);
}
return xcvar(re,"xcnum");
       }
       else 
        {
       cout<<">>error:minus doesn't support such type.\n";
       return xcvar(any(0),"xcnum");
        }
   }
 }
else 
 {
cout<<">>error:bad type for minus.\n";
return xcvar(any(0),"xcnum");
 }
}
//#########
xcvar xcdivide(xcvar a){
if(a.second=="xclist")
 {
xclist tlist=any_cast<xclist>(a.first);
 if(!allthetype(tlist))
   {
   cout<<">>error:elements' types are not the same.\n";
   return xcvar(any(0),"xcnum");
   }
 else 
   {
    xclist::iterator it=tlist.begin();
     if(it->second=="xcnum")
       {
any re=it->first;it++;
for(;it!=tlist.end();it++)
{re=re/any_cast<double>(it->first);
}
return xcvar(re,"xcnum");
       }
       else 
        {
       cout<<">>error:divide doesn't support such type.\n";
       return xcvar(any(0),"xcnum");
        }
   }
 }
else 
 {
cout<<">>error:bad type for divide.\n";
return xcvar(any(0),"xcnum");
 }
}
//@@@@@@@@@@@@
xcvar xcmod(xcvar a){
if(a.second=="xclist")
 {
xclist tlist=any_cast<xclist>(a.first);
 if(!allthetype(tlist))
   {
   cout<<">>error:elements' types are not the same.\n";
   return xcvar(any(0),"xcnum");
   }
 else 
   {
    xclist::iterator it=tlist.begin();
     if(it->second=="xcnum")
       {
any re=it->first;it++;
for(;it!=tlist.end();it++)
{re=re%(int)any_cast<double>(it->first);
}
return xcvar(re,"xcnum");
       }
       else 
        {
       cout<<">>error:mod doesn't support such type.\n";
       return xcvar(any(0),"xcnum");
        }
   }
 }
else 
 {
cout<<">>error:bad type for divide.\n";
return xcvar(any(0),"xcnum");
 }
}
//########
xcvar xcpow(xcvar a){
if(a.second!="xclist")
{cout<<">>error: bad type for pow.\n";
return xcvar(any(0),"xcnum");}
else{
 xclist tlist=any_cast<xclist>(a.first);
    if(tlist.size()!=2)
       {cout<<">>error: too many arguments for pow.\n";
         return xcvar(any(0),"xcnum");
        }
    else { 
       if(!allthetype(tlist))
      {cout<<">>error:not the same type.\n";
        return xcvar(any(0),"xcnum");
      }
    else {
       xclist::iterator it=tlist.begin();
           if(it->second!="xcnum")
            {cout<<">>error:pow doesn\'t support such type.\n";
              return xcvar(any(0),"xcnum");
             }
          else{ any re=it->first;
                it++;
     re=pow(any_cast<double>(re),any_cast<double>(it->first));
               return xcvar(re,"xcnum");
               }
            }
         }
}
}
//&&&&&&&&&&
xcvar xcprint(xcvar a){
if(a.second=="xcstr"||a.second=="xcnum")
{cout<<a.first;
if(XC_CONSOLEMODE&&isnotlist()){cout<<endl;}
}
else if(a.second=="xclist"){
cout<<"[";xclist tlist=any_cast<xclist>(a.first);
xclist::iterator it=tlist.begin();
xcvar tvar(any(0),"xcnum");
XC_LISTNUM++;
XC_LISTNOW[XC_LISTNUM]=1;
for(;it!=tlist.end();it++)
{if(it==tlist.begin()){}
 else{cout<<",";}
 tvar=xcprint(*it);}
cout<<"]";
XC_LISTNOW[XC_LISTNUM]=0;
XC_LISTNUM--;
if(XC_CONSOLEMODE&&isnotlist()){cout<<endl;}
}
else {cout<<">>error:bad type for print.\n";}
return xcvar(any(0),"xcnum");}
//$$$$$$$$$$
xcvar xc_builtinprint(xcvar a){
if(a.second=="xcstr"||a.second=="xcnum")
{cout<<a.first;}
else if(a.second=="xclist"){
xclist tlist=any_cast<xclist>(a.first);
xclist::iterator it=tlist.begin();
xcvar tvar(any(0),"xcnum");
for(;it!=tlist.end();it++)
{tvar=xc_builtinprint(*it);}
}
else {cout<<">>error:bad type for itemprint.\n";}
return xcvar(any(0),"xcnum");} 



xcvar xcitemprint(xcvar a){
if(a.second=="xcstr"||a.second=="xcnum")
{cout<<a.first;}
else if(a.second=="xclist"){
xclist tlist=any_cast<xclist>(a.first);
xclist::iterator it=tlist.begin();
xcvar tvar(any(0),"xcnum");
for(;it!=tlist.end();it++)
{tvar=xc_builtinprint(*it);}
if(XC_CONSOLEMODE){cout<<endl;}
}
else {cout<<">>error:bad type for itemprint.\n";}
return xcvar(any(0),"xcnum");} 

xcvar xcinput(xcvar a){
if(a.second!="xcnum"){
cout<<">>error:bad argument for input.\n";}
else {
char str[200];
cin.getline(str,199);
string tem(str);
return realrval(tem);
     }
}

xcvar xcexec(xcvar a){
if(a.second=="xcstr"){
analyse((char*)any_cast<string>(a.first).c_str());
}
else if(a.second=="xclist"){
xclist tlist=any_cast<xclist>(a.first);
if(!allthetype(tlist))
{cout<<">>error:list not the same type.\n";
return xcvar(any(0),"xcnum");
}
else {xclist::iterator it=tlist.begin();
   if((*it).second!="xcstr")
  {cout<<">>error:list's element type not str.\n";
   return xcvar(any(0),"xcnum");
   }
  else{
    for(;it!=tlist.end();it++)
   {xcexec(*it);}
      }
}
}
else{
cout<<">>error:bad type for exec.\n";
}
return xcvar(any(0),"xcnum");
}

xcvar xcassign(xcvar a){
if(a.second=="xcnum"
||a.second=="xcstr"
||a.second=="xclist"){
return a;
}
else {cout<<">>error:bad type for '='.\n";}
}

xcvar xcgetch(xcvar a){
if(a.second!="xcnum")
{cout<<">>error:bad type for getch.\n";
 return xcvar(any(0),"xcnum");}
else {int i=(int)any_cast<double>(a.first);
if(i==0){
char c=(char)mygetch();
return xcvar(any(c),"xcstr");}
else {int t=mygetch();
return xcvar(any(t),"xcnum");}
}
}

xcvar xcif(xcvar a){
if(a.second!="xclist"){
cout<<">>error:wrong type for if.\n";
}
else{xclist tlist=any_cast<xclist>(a.first);
xclist::iterator it=tlist.begin();
if((*it).second!="xcnum")
  {cout<<">>error:wrong type for the first element.\n";
  }
else{int i=(int)any_cast<double>((*it).first);
     if(i==0){}
    else{it++;
      for(;it!=tlist.end();it++) 
         {xcexec(*it);}
     }
    }
}
return xcvar(any(0),"xcnum");
}

xcvar xcfor(xcvar a){
if(a.second!="xclist")
{cout<<">>error:wrong type for 'for' function.\n";
}
else{xclist tlist=any_cast<xclist>(a.first);
  if(tlist.size()<4){cout<<">>error:too few arguments for 'for' function .\n";
                  }
  else{xclist::iterator it=tlist.begin();
       xcexec(*it);it++;
       xclist::iterator thebreaker=it;
   it++;xclist::iterator thecondition=it;
   it++;xclist::iterator thebegin=it;
       while(1){
     string condi=any_cast<string>((*thebreaker).first);
    xcvar xcondi=realrval(condi);
    int i=(int)any_cast<double>(xcondi.first);
   if(i==0){break;}
   for(it=thebegin;it!=tlist.end();it++)
       {xcexec(*it);}
    xcexec(*thecondition);
               }
     }
}
return xcvar(any(0),"xcnum");
}

xcvar xctypename(xcvar a){
return xcvar(any(a.second),"xcstr");
}

xcvar xccolor(xcvar a){
if(a.second!="xcstr")
{cout<<">>error:wrong type for 'color' .\n";
}
else{
int conum=0;
//"\033[0dm " doesn't make a difference
string co=any_cast<string>(a.first);
if(co=="red"){conum=41;}
else if(co=="green"){conum=42;}
else if(co=="brown"){conum=43;}
else if(co=="blue"){conum=44;}
else if(co=="purple"){conum=45;}
else if(co=="blue2"){conum=46;}
else if(co=="grey"){conum=47;}
else if(co=="origin"){conum=0;}
else{
cout<<">>error:such color isn't supported.\n";
   }
cout<<"\033["<<conum<<"m";
}
return xcvar(any(0),"xcnum");
}
#endif
