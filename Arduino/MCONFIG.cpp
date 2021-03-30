#include "MCONFIG.h"
#include <string.h>

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

int NB_MF = 0 ;
int NB_MC = 0 ;
int MAX_MC = 0 ;

TAPE *MCONFIG::_tape = NULL ; 


MCONFIG::MCONFIG(){
  NB_MC++ ;
  MAX_MC = MAX(MAX_MC, NB_MC) ;
}


MCONFIG::MCONFIG(const MCONFIG &mc) : MCONFIG(){
  strncpy(_name, mc._name, 3) ;
  _name[3] = '\0' ;
  _f = mc._f ;
}


MCONFIG::MCONFIG(const char *name, Lambda<MCONFIG(char s)> f) : MCONFIG(){
  strncpy(_name, name, 3) ;
  _name[3] = '\0' ;
  _f = f ;
}


void MCONFIG::set_tape(TAPE *tape){
    _tape = tape ; 
}


TAPE *MCONFIG::get_tape(){
    return _tape ; 
}


const char *MCONFIG::get_name(){
    return _name ;
}


bool MCONFIG::matches(char ss, char s){
  if (ss == _BLANK){
    return true ;
  }
  else if (ss == _NONE){
    return (s == ' ') ;
  }
  else if (ss == _ANY){
    return (s != ' ') ; 
  }
  else if (ss < 0){
    return ((s != ' ')&&(s != -ss)) ;
  }
  else {
    return (ss == s) ; 
  }
}


MCONFIG MCONFIG::operator()(char s){     
    return _f(s) ;
}