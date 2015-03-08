#ifndef _ANY_H_
#define _ANY_H_
#include <iostream>
#include <string>
#include "stdlib.h"
#include "stdio.h"
#include <typeinfo>
#include "any_assist.h"
using std::cout;
using std::string;
using std::ostream;

class any_error{
string merrorinfo;
public:
any_error(string s="\nERROR:about any!"):merrorinfo(makestring(s)){cout<<s;}
string errorinfo(){return merrorinfo;}
};
class any;
template <class T>
T any_cast(any apro);

class any{
bool ig;
void* p;
bool mig(){int k=1;
#ifndef ANY_SAFEMODE
k=0;
#endif
return k;
}
bool isnum;
template <class T>
bool misnum(T& pro){
return 
 (typeid(T)==typeid(1)||
  typeid(T)==typeid(float)||
  typeid(T)==typeid(double)||
  typeid(T)==typeid(long)
  );  
}
bool ismchar;
template <class T>
bool mismchar(T& pro){
return 
   (typeid(T)==typeid(char)||
    typeid(T)==typeid(char*)||
    typeid(T)==typeid(const char*)||
    typeid(T)==typeid(string)
    );
}
public:
bool getisnum(){return isnum;}
bool getismchar(){return ismchar;}
void* getp(){return p;}

void safemode(){ig=1;}
void normalmode(){ig=0;}
const any& operator=(const any& an){
p=an.p;isnum=an.isnum;ismchar=an.ismchar;ig=an.ig;}
template <class T>
const any& operator=(const T& pro);
const any& operator=(const char* s){
p=new (string)(makestring(s));isnum=0;ismchar=1;ig=0;}

any():isnum(0),ismchar(0),ig(mig()){}
any(const char* s):ismchar(1),isnum(0),ig(mig())
{p=new (string)(makestring(s));}
template <class T>
any(const T& pro);

template <class T>
T operator+(const T& pro);
any& operator+(any& an);
string operator+(char s);
string operator+(char* s);
string operator+(const char* s);
string operator+(string s);
double operator+(double num);
double operator+(int num);
double operator+(float num);
double operator+(long num);
template <class T>
T operator-(const T& pro);
double operator-(double num);
double operator-(int num);
double operator-(float num);
double operator-(long num);
template <class T>
T operator*(const T& pro);
double operator*(double num);
double operator*(int num);
double operator*(float num);
double operator*(long num);
template <class T>
T operator/(const T& pro);
double operator/(double num);
double operator/(int num);
double operator/(float num);
double operator/(long num);
int operator%(int num); 
template <class T>
bool operator!=(const T& pro){
if(ismchar&&mismchar(pro))
{static string hh=makestring(pro);
return hh==any_cast<string>(*this);}
else {return !(any_cast<T>(*this)==pro);}
}
template <class T>
bool operator==(const T& pro){
return !((*this)!=pro);
}
char operator[](int i)
{
if(ismchar)
{return any_cast<string>(*this) [i];}
else if(isnum){
static char str[20];
sprintf(str,"%.8lf",any_cast<double>(*this));
if(i>19||i<0){any_error err("ERROR:operator[] for any_num out of range");
if(ig){throw(err);}
 return str[0];
           }
else {return str[i];}
             }
else{any_error err("\nERROR:Can't use operator[] in this any object");
if(!ig){throw(err);}
return ' ';
    }
}

template <class T>
any& selfadd(T t=static_cast<T>(0))
{T tt=any_cast<T>(*this);
tt++;*this=tt;
return (*this);
}
template <class T>
T cast(T t=static_cast<T>(0)) 
{return any_cast<T>(*this);
}

const any& operator++(int i=0){
if(isnum){selfadd<double>();}
else {any err("ERROR:Can't use operator++(int)!");
if(!ig){throw(err);}
     }
}
friend ostream& operator<<(ostream& out,any& pro);
};

template <class T>
any::any(const T& pro){
ismchar=0;isnum=0;ig=mig();
p=new (T)(pro);
  if(misnum(pro))
  {isnum=1;p=new (double)(turndouble(pro));}
  else if(mismchar(pro))
  {ismchar=1;p=new (string)(makestring(pro));}
}

template <class T>
const any& any::operator=(const T& pro){
p=new (T)(pro);
isnum=0;ismchar=0;ig=mig();
  if(misnum(pro))
  {isnum=1;p=new (double)(turndouble(pro));}
  else if(mismchar(pro))
  {ismchar=1;p=new (string)(makestring(pro));}
}

template <class T>
T any::operator+(const T& pro){
if((misnum(pro)&&isnum)||(mismchar(pro)&&ismchar)){
must_can_add<T> ggg;
return any_cast<T>(*this)+pro;
}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return pro;
}
}
template <class T>
T any::operator-(const T& pro){
if(isnum&&misnum(pro)){
must_can_minus<T> ggg;
return any_cast<T>(*this)-pro;
}
else{any_error err("ERROR:Can't minus!");
if(!ig){throw(err);}
return pro;
    }
}
template <class T>
T any::operator*(const T& pro){
if(isnum&&misnum(pro)){
must_can_multiply<T> ggg;
return any_cast<T>(*this)*pro;
}
else{any_error err("ERROR:Can't multiply!");
if(!ig){throw(err);}
return pro;
    }
}
template <class T>
T any::operator/(const T& pro){
if(isnum&&misnum(pro)){
must_can_divide<T> ggg;
return any_cast<T>(*this)/pro;
}
else{any_error err("ERROR:Can't divide!");
if(!ig){throw(err);}
return pro;
    }
}

any& any::operator+(any& an)
{
static any tem;
if(an.isnum&&isnum)
  {tem=any_cast<double>(*this)+any_cast<double>(an);
  return tem;}
else if(an.ismchar&&ismchar)
  {tem=any_cast<string>(*this)+any_cast<string>(an);
  return tem;}
else {any_error err("\nERROR:Can't add!");
if(!ig&&!an.ig){throw(err);}
 return tem;
     }
}
//###203
string any::operator+(const char* s){
if(ismchar)
{return any_cast<string>(*this)+makestring(s);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return "\nERROR:Can't add!";
}
}
string any::operator+(char s){
if(ismchar)
{return any_cast<string>(*this)+makestring(s);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return "\nERROR:Can't add!";
}
}
string any::operator+(char* s){
if(ismchar)
{return any_cast<string>(*this)+makestring(s);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return "\nERROR:Can't add!";
}
}
string any::operator+(string s){
if(ismchar)
{return any_cast<string>(*this)+makestring(s);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return "\nERROR:Can't add!";
}
}
double any::operator+(double num){
if(isnum){
return any_cast<double>(*this)+turndouble(num);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return 0.0;
    }
}

double any::operator+(int num){
if(isnum)
{return any_cast<double>(*this)+turndouble(num);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return 0.0;
    }
}
double any::operator+(float  num){
if(isnum)
{return any_cast<double>(*this)+turndouble(num);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return 0.0;
     }
}
double any::operator+(long num){
if(isnum)
{return any_cast<double>(*this)+turndouble(num);}
else {any_error err("ERROR:Can't add!");
if(!ig){throw(err);}
return 0.0;
   }
}
double any::operator-(double num){
if(isnum)
{return any_cast<double>(*this)-turndouble(num);}
else {any_error err("ERROR:Can't minus!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator-(int num){
if(isnum)
{return any_cast<double>(*this)-turndouble(num);}
else {any_error err("ERROR:Can't minus!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator-(float  num){
if(isnum)
{return any_cast<double>(*this)-turndouble(num);}
else {any_error err("ERROR:Can't minus!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator-(long num){
if(isnum)
{return any_cast<double>(*this)-turndouble(num);}
else {any_error err("ERROR:Can't minus!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator*(double num){
if(isnum)
{return any_cast<double>(*this)*turndouble(num);}
else {any_error err("ERROR:Can't multiply");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator*(int num){
if(isnum)
{return any_cast<double>(*this)*turndouble(num);}
else {any_error err("ERROR:Can't multiply!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator*(float  num){
if(isnum)
{return any_cast<double>(*this)*turndouble(num);}
else {any_error err("ERROR:Can't multiply!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator*(long num){
if(isnum)
{return any_cast<double>(*this)*turndouble(num);}
else {any_error err("ERROR:Can't multiply!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator/(double num){
if(isnum)
{return any_cast<double>(*this)/turndouble(num);}
else {any_error err("ERROR:Can't divide!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator/(int num){
if(isnum)
{return any_cast<double>(*this)/turndouble(num);}
else {any_error err("ERROR:Can't divide!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator/(float  num){
if(isnum)
{return any_cast<double>(*this)/turndouble(num);}
else {any_error err("ERROR:Can't divide!");
if(!ig){throw(err);}
return 0.0;}
}
double any::operator/(long num){
if(isnum)
{return any_cast<double>(*this)/turndouble(num);}
else {any_error err("ERROR:Can't divide!");
if(!ig){throw(err);}
return 0.0;}
}
int any::operator%(int num){
if(isnum){
return static_cast<int>(any_cast<double>(*this))%num;}
else{any_error err("ERROR:Can't mod!");
if(!ig){throw(err);}
return num;}
}
ostream& operator<<(ostream& out,any& pro){
if(pro.getisnum()){out<<any_cast<double>(pro);}
else if(pro.getismchar()){out<<any_cast<string>(pro);}
else{any_error err("\nERROR:Cannot out!");
if(!pro.ig) {throw(err);}
   }
return out;
}

template <class T>
T any_cast(any apro){
return *((T*)apro.getp());
}
#endif
