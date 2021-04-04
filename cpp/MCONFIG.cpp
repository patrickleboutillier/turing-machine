#include "MCONFIG.h"
#include <string.h>


#define MAX(a,b) ((a) > (b) ? a : b)


long NB_MCONFIG = 0 ;
long MAX_MCONFIG = 0 ;
long SIZE_MCONFIG = 0 ;
long MAX_SIZE_MCONFIG = 0 ;


MCONFIG::MCONFIG(MCf f){
  this->f = (MCf)f ;
  NB_MCONFIG++ ;
  MAX_MCONFIG = MAX(MAX_MCONFIG, NB_MCONFIG) ;
} ;


MC MCONFIG::clone(){
  return new MCONFIG((MCf)f) ;
}


MCONFIG::~MCONFIG(){
  NB_MCONFIG-- ;
} ;


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


MC MCONFIG::operator()(char s){  
  MCf f = (MCf)this->f ;
  return f(s) ;
}


MC MCONFIG::operator()(){
  return clone() ;  
}


MC MCONFIG::move(MC mc, char s){
  MC o = mc ;
  MC n = (*o)(s) ;
  delete o ;
  return n ;
}
