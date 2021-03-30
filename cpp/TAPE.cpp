#include "TAPE.h"
#include <stdio.h>

#include "MCONFIG.h"


TAPE::TAPE(){
  for (int i = 0 ; i < (TAPE_LEN-1) ; i++){
    _squares[i] = ' ' ;
  }
  _squares[TAPE_LEN-1] = '\0' ;
  _pos = 1 ;
  _max_pos = 1 ;
}


TAPE::TAPE(const char *tape){
  for (int i = 0 ; i < (TAPE_LEN-1) ; i++){
    _squares[i] = ' ' ;
  }
  _squares[TAPE_LEN-1] = '\0' ;
  _pos = 1 ;
  _max_pos = 1 ;
  for (int i = 0 ; tape[i] != '\0' ; i++){
    _squares[_pos+i] = tape[i] ;
  }  
}


bool TAPE::apply_ops(const char *ops){
  for (int i = 0 ; ops[i] != '\0' ; i++){
    switch (ops[i]){
      case '>': 
        _pos++ ; 
        if (_pos > _max_pos){
          _max_pos = _pos ;
        }
        break ;
      case '<': _pos-- ; break ;
      default: _squares[_pos] = ops[i] ;
    }
  }
  return true ;
}


char TAPE::scan(){
  return _squares[_pos] ;
}


void TAPE::print(MCONFIG mc){
  char x = _squares[_pos] ;
  _squares[_pos] = '\0' ;
  printf("[%s%c/%s", _squares, x, mc.get_name()) ;
  _squares[_pos] = x ;

  if (_max_pos > _pos){
    char m = _squares[_max_pos] ;
    _squares[_max_pos] = '\0' ;
    printf("%s", _squares + _pos + 1) ;
    _squares[_max_pos] = m ;
  }

  printf("]\n") ;
}
