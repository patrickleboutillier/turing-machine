#include "TAPE.h"
#include <stdio.h>

#include "MCONFIG.h"


TAPE::TAPE(){
  for (int i = 0 ; i < (TAPE_LEN-1) ; i++){
    _squares[i] = ' ' ;
  }
  _squares[TAPE_LEN-1] = '\0' ;
  _pos = 1 ;
}


TAPE::TAPE(const char *tape){
  for (int i = 0 ; i < (TAPE_LEN-1) ; i++){
    _squares[i] = ' ' ;
  }
  _squares[TAPE_LEN-1] = '\0' ;
  _pos = 1 ;
  for (int i = 0 ; tape[i] != '\0' ; i++){
    _squares[_pos+i] = tape[i] ;
  }  
}


bool TAPE::apply_ops(const char *ops){
  for (int i = 0 ; ops[i] != '\0' ; i++){
    switch (ops[i]){
      case '>': _pos++ ; break ;
      case '<': _pos-- ; break ;
      default: _squares[_pos] = ops[i] ;
    }
  }
  return true ;
}


char TAPE::scan(){
  return _squares[_pos] ;
}


void TAPE::print(MCONFIG *mc){
  char x = _squares[_pos] ;
  _squares[_pos] = '\0' ;
  printf("[%s%c/%s%s]\n", _squares, x, mc->get_name(), _squares + _pos + 1) ;
  _squares[_pos] = x ;
}
