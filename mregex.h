#ifndef __MREGEX_H__
#define __MREGEX_H__
#include "stdio.h"
#include "regex.h"
#include <iostream>
using namespace std;
class regex{
public:
regex_t reg;
regmatch_t pm[10];
char errbuf[100];
regex(char* pattern){
if(regcomp(&reg,pattern,REG_EXTENDED)<0)
    {
     regerror(10,&reg,errbuf,100);
     cout<<errbuf;
    }
                    }
regex(){}
void setpattern(char* pa){
     regfree(&reg);
     regcomp(&reg,pa,REG_EXTENDED);
                    }
};

bool regex_match(char* bematch,regex* preg)
{int i;
i=regexec(&(preg->reg),bematch,10,preg->pm,0);
if(i==REG_NOMATCH){return false;}
else {return true;}
}
int regex_count(char* be,regex* preg)
{int re=0;int i,cuthere;char* bematch=be;
while(1){
i=regexec(&(preg->reg),bematch,10,preg->pm,0);
if(i==REG_NOMATCH){break;}
else {
cuthere=preg->pm[0].rm_eo;
bematch+=cuthere;
re++;}
}   return re;
}
#endif