#include "MCONFIG.h"
#include <string.h>


TAPE *MCONFIG::_tape = NULL ; 


MCONFIG::MCONFIG(const char *name, MCONFIG*(*f)(char s)){
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


MCONFIG *MCONFIG::operator()(char s){     
    return ((MCONFIG*(*)(char s))_f)(s) ;
}