#ifndef MCONFIG_H
#define MCONFIG_H


#include "TAPE.h"


// Symbol specifiers
#define     _BLANK     '*'
#define     _NONE      ' '
#define     _ANY       '?'
#define     _SYM(s)    s             // Usage restricted to printable ASCII chars (i.e. >= 32)
#define     _NOT(s)    (-s)


#define _RULE(ss, s, ops, fMCONFIG)   if (MCONFIG::matches(ss, s)){ MCONFIG::get_tape()->apply_ops(ops) ; return fMCONFIG ; }
#define BLANK(s, ops, fMCONFIG)       _RULE(_BLANK, s, ops, fMCONFIG)
#define NONE(s, ops, fMCONFIG)        _RULE(_NONE, s, ops, fMCONFIG)
#define ANY(s, ops, fMCONFIG)         _RULE(_ANY, s, ops, fMCONFIG)
#define SYM(s, a, ops, fMCONFIG)      _RULE(_SYM(a), s, ops, fMCONFIG)
#define NOT(s, a, ops, fMCONFIG)      _RULE(_NOT(a), s, ops, fMCONFIG)


class MCONFIG {
  private:
    char _name[4] ;
    MCONFIG *(*_f)(char s) ;
    static TAPE *_tape ;
  public:
    MCONFIG(const char *name, MCONFIG *(*f)(char s)) ;
    const char *get_name() ;
    static bool matches(char ss, char s) ;
    MCONFIG *operator()(char s) ;
    static TAPE *get_tape() ;
    static void set_tape(TAPE *) ;
} ;


typedef MCONFIG MC ;


template<typename T> class MF {} ;
template<typename Out, typename... In> class MF<Out(In...)> {
  private:
    Out (*_f)(In..., char s) ;
  public:
    MF(const char *name, MCONFIG *(*f)(In..., char s)){ _f = f  ; } ;
    Out operator()(In... args, char s){ return _f(args..., s) ; }
} ;


#endif
