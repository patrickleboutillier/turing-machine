#ifndef MCONFIG_H
#define MCONFIG_H

#include "TAPE.h"
#include "PRINT.h"


// Symbol specifiers
#define     _BLANK     '*'
#define     _NONE      ' '
#define     _ANY       '?'
#define     _SYM(s)    s             // Usage restricted to printable ASCII chars (i.e. >= 32)
#define     _NOT(s)    (-s)


#define _RULE(ss, s, ops, fmc)   if (MCONFIG::matches(ss, s)){ TAPE::get_tape()->apply_ops(ops) ; return (*fmc)() ; }
#define BLANK(s, ops, fmc)       _RULE(_BLANK, s, ops, fmc)
#define NONE(s, ops, fmc)        _RULE(_NONE, s, ops, fmc)
#define ANY(s, ops, fmc)         _RULE(_ANY, s, ops, fmc)
#define SYM(s, a, ops, fmc)      _RULE(_SYM(a), s, ops, fmc)
#define NOT(s, a, ops, fmc)      _RULE(_NOT(a), s, ops, fmc)
#define DONE(s)                   { PRINT::print(s) ; PRINT::print("\n") ; }


class MCONFIG ;
typedef MCONFIG* MC ;


typedef MC(*MCf)(char) ;


class MCONFIG {
  protected:
    MCf f ;
  public:
    MCONFIG(MCf f) ;
    virtual MC clone() ;
    virtual ~MCONFIG() ;
    static bool matches(char ss, char s) ;
    virtual MC operator()(char s) ;
    virtual MC operator()() ;
    static MC move(MC mc, char s) ;
} ;


extern long NB_MCONFIG ;
extern long MAX_MCONFIG ;
extern long SIZE_MCONFIG ;
extern long MAX_SIZE_MCONFIG ;


#endif
