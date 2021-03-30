#ifndef MCONFIG_H
#define MCONFIG_H


#include "Lambda.h"
#include "TAPE.h"
#include <string.h>

extern int NB_MC ;
extern int MAX_MC ;
extern int SIZE_MC ;
extern int MAX_SIZE_MC ;
extern int NB_MF ;

// Symbol specifiers
#define     _BLANK     '*'
#define     _NONE      ' '
#define     _ANY       '?'
#define     _SYM(s)    s             // Usage restricted to printable ASCII chars (i.e. >= 32)
#define     _NOT(s)    (-s)


#define _RULE(ss, s, ops, fmc)   if (MCONFIG::matches(ss, s)){ MCONFIG::get_tape()->apply_ops(ops) ; return fmc ; }
#define BLANK(s, ops, fmc)       _RULE(_BLANK, s, ops, fmc)
#define NONE(s, ops, fmc)        _RULE(_NONE, s, ops, fmc)
#define ANY(s, ops, fmc)         _RULE(_ANY, s, ops, fmc)
#define SYM(s, a, ops, fmc)      _RULE(_SYM(a), s, ops, fmc)
#define NOT(s, a, ops, fmc)      _RULE(_NOT(a), s, ops, fmc)


class MCONFIG {
  private:
    char _name[5] ;
    Lambda<MCONFIG(char s)> _f ;
    static TAPE *_tape ;
    void set_name(const char *name) ;
  public:
    MCONFIG() ;
    MCONFIG(const MCONFIG &mc) ;
    MCONFIG(const char *name, Lambda<MCONFIG(char s)>) ;
    ~MCONFIG(){ NB_MC-- ;  SIZE_MC -= sizeof(*this) ; } ;
    const char *get_name() ;
    static bool matches(char ss, char s) ;
    MCONFIG operator()(char s) ;
    static TAPE *get_tape() ;
    static void set_tape(TAPE *) ;
} ;


typedef MCONFIG MC ;


template<typename T> class MF {} ;
template<typename Out, typename... In> class MF<Out(In...)> {
  private:
    char _name[9] ;
    Out (*_f)(In..., char s) ;
  public:
    MF(const char *name, MCONFIG (*f)(In..., char s)){ strncpy(_name, name, 3) ; _name[3] = '\0' ; _f = f ; NB_MF++ ; } ;
    const char *get_name(){ return _name ; } 
    Out operator()(In... args){ 
      return MC(get_name(), [args..., this](char s){
        return _f(args..., s) ;
      }) ;
    }
} ;





#endif
