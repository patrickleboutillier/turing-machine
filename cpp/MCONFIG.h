#ifndef MCONFIG_H
#define MCONFIG_H

#include "Lambda.h"
#include "TAPE.h"
#include <string.h>


// Symbol specifiers
#define     _BLANK     '*'
#define     _NONE      ' '
#define     _ANY       '?'
#define     _SYM(s)    s             // Usage restricted to printable ASCII chars (i.e. >= 32)
#define     _NOT(s)    (-s)


#define _RULE(ss, s, ops, fmc)   if (MCONFIG::matches(ss, s)){ TAPE::get_tape()->apply_ops(ops) ; return fmc ; }
#define BLANK(s, ops, fmc)       _RULE(_BLANK, s, ops, fmc)
#define NONE(s, ops, fmc)        _RULE(_NONE, s, ops, fmc)
#define ANY(s, ops, fmc)         _RULE(_ANY, s, ops, fmc)
#define SYM(s, a, ops, fmc)      _RULE(_SYM(a), s, ops, fmc)
#define NOT(s, a, ops, fmc)      _RULE(_NOT(a), s, ops, fmc)


class MCONFIG {
  private:
    Lambda<MCONFIG(char s)> _f ;
  public:
    MCONFIG(Lambda<MCONFIG(char s)>) ;
    static bool matches(char ss, char s) ;
    MCONFIG operator()(char s) ;
} ;


typedef MCONFIG MC ;


#endif
