#include "MCONFIG.h"
#include <string.h>

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

int NB_MF = 0 ;
int NB_MC = 0 ;
int MAX_MC = 0 ;
int SIZE_MC = 0 ;
int MAX_SIZE_MC = 0 ;

TAPE *MCONFIG::_tape = NULL ; 


MCONFIG::MCONFIG(){
  NB_MC++ ;
  MAX_MC = MAX(MAX_MC, NB_MC) ;
  SIZE_MC += sizeof(*this) ;
  MAX_SIZE_MC = MAX(MAX_SIZE_MC, SIZE_MC) ;
}


MCONFIG::MCONFIG(const MCONFIG &mc) : MCONFIG(){
  //set_name(mc._name) ;
  _f = mc._f ;
}


MCONFIG::MCONFIG(const char *name, Lambda<MCONFIG(char s)> f) : MCONFIG(){
  //set_name(name) ;
  _f = f ;
}


void MCONFIG::set_tape(TAPE *tape){
    _tape = tape ; 
}


TAPE *MCONFIG::get_tape(){
    return _tape ; 
}


void MCONFIG::set_name(const char *name){
  //strncpy(_name, name, 4) ;
  //_name[4] = '\0' ;
}


const char *unknown = "?" ;
const char *MCONFIG::get_name(){
    return unknown;
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