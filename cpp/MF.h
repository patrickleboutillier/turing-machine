#ifndef MF_H
#define MF_H


#include "MCONFIG.h"


// Types for the different functions
typedef MC(*MCfM)(MC, char) ;
extern MC MF(MC, MCfM) ;

typedef MC(*MCfMs)(MC, char, char) ;
extern MC MF(MC, char, MCfMs) ;

typedef MC(*MCfMss)(MC, char, char, char) ;
extern MC MF(MC, char, char, MCfMss) ;

typedef MC(*MCfMsss)(MC, char, char, char, char) ;
extern MC MF(MC, char, char, char, MCfMsss) ;

typedef MC(*MCfMssss)(MC, char, char, char, char, char) ;
extern MC MF(MC, char, char, char, char, MCfMssss) ;

typedef MC(*MCfMsssss)(MC, char, char, char, char, char, char) ;
extern MC MF(MC, char, char, char, char, char, MCfMsssss) ;

typedef MC(*MCfMMs)(MC, MC, char, char) ;
extern MC MF(MC, MC, char, MCfMMs) ;

typedef MC(*MCfMMss)(MC, MC, char, char, char) ;
extern MC MF(MC, MC, char, char, MCfMMss) ;

typedef MC(*MCfMMMss)(MC, MC, MC, char, char, char) ;
extern MC MF(MC, MC, MC, char, char, MCfMMMss) ;



class MFM : public MCONFIG {
  protected:
    MC A ;
  public:
    MFM(MC A, MCfM f) : MCONFIG((MCf)f) { this->A = A->clone() ; } ;
    virtual MC clone(){ return new MFM(A, (MCfM)f) ; }
    virtual ~MFM() { delete A ; } ;
    virtual MC operator()(char s) { return ((MCfM)f)(A, s) ; } ;
    virtual MC operator()(){ return this ; } ;
} ;


class MFMs : public MFM {
  protected:
    char a ;
  public:
    MFMs(MC A, char a, MCfMs f) : MFM(A, (MCfM)f) { this->a = a ;} ;
    virtual MC clone(){ return new MFMs(A, a, (MCfMs)f) ; }
    virtual MC operator()(char s) { return ((MCfMs)f)(A, a, s) ; } ;
} ;


class MFMMs : public MFM {
  protected:
    MC B ;
    char a ;
  public:
    MFMMs(MC A, MC B, char a, MCfMMs f) : MFM(A, (MCfM)f) { this->B = B->clone() ; this->a = a ; } ;
    virtual MC clone(){ return new MFMMs(A, B, a, (MCfMMs)f) ; }
    virtual ~MFMMs() { delete B ; } ;
    virtual MC operator()(char s) { return ((MCfMMs)f)(A, B, a, s) ; } ;
} ;


class MFMMss : public MFMMs {
  protected:
    char b ;
  public:
    MFMMss(MC A, MC B, char a, char b, MCfMMss f) : MFMMs(A, B, a, (MCfMMs)f) { this->b = b ; } ;
    virtual MC clone(){ return new MFMMss(A, B, a, b, (MCfMMss)f) ; }
    virtual MC operator()(char s) { return ((MCfMMss)f)(A, B, a, b, s) ; } ;
} ;


#endif