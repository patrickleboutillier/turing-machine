#include "MCONFIG.h"
#include <string.h>

#define MAX(a,b) ((a) > (b) ? a : b)

int NB_LAMBDA = 0 ;
int MAX_LAMBDA = 0 ;
int SIZE_LAMBDA = 0 ;
int MAX_SIZE_LAMBDA = 0 ;



MCONFIG::MCONFIG(Lambda<MCONFIG(char s)> f) {
  _f = f ;
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