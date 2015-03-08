#ifndef MFILE_H
#define MFILE_H
#include <iostream>
#include <fstream>
using std::ifstream;
void getdic(ifstream& fin,char* re){
char* dic=re;
fin.get(*dic);
dic++;
while(1){
if(fin.eof()){break;}
fin.get(*dic);dic++;
       }
dic=dic-1;
*dic='\0';
fin.close();
}
#endif