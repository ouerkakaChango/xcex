#ifndef _ANY_ASSIST_H_
#define _ANY_ASSIST_H_
#include <string>
#include <iostream>
using std::cout;
using std::string;
string makestring(string i)
{return i;}
string makestring(char c){
string t(1,c);return t;}
string makestring(char* p){
string k=p;return k;}
string makestring(const char* p){
string k=p;return k;}
template <class T>
string makestring(const T& t){
string p="\nERROR:cannot out!";
return p;
}

int turndouble(int i){return i;}
float turndouble(float i){return i;}
double turndouble(double i){return i;}
long turndouble(long i){return i;}
template <class T>
double turndouble(const T& t){return (double)1.0;}
template <class T>
class must_can_add{
static inline void MustCanAdd(T* t)
{*t=*t+*t;}
public:
~must_can_add()
{void(*p)(T*)=MustCanAdd;}
};
template <class T>
class must_can_minus{
static inline void MustCanMinus(T* t)
{*t=*t-*t;}
public:
~must_can_minus()
{void(*p)(T*)=MustCanMinus;}
};
template <class T>
class must_can_multiply{
static inline void MustCanMultiply(T* t)
{(*t)=(*t)*(*t);}
public:
~must_can_multiply()
{void(*p)(T)=MustCanMultiply;}
};

template <class T>
class must_can_divide{
static inline void MustCanDivide(T* t)
{*t=*t / *t;}
public:
~must_can_divide()
{void(*p)(T*)=MustCanDivide;}
};

template <class T>
class must_can_mod{
static inline void MustCanMod(T* t)
{*t=*t % *t;}
public:
~must_can_mod()
{void(*p)(T*)=MustCanMod;}
};
#endif
