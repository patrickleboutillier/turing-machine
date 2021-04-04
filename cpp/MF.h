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
    int size(){ return sizeof(*this) + A->size() ; } ;
    virtual MC clone(){ return count(new MFM(A, (MCfM)f)) ; }
    virtual ~MFM() { delete uncount(A) ; } ;
    virtual MC operator()(char s) { return ((MCfM)f)(A, s) ; } ;
} ;


class MFMs : public MFM {
  protected:
    char a ;
  public:
    MFMs(MC A, char a, MCfMs f) : MFM(A, (MCfM)f) { this->a = a ; } ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMs(A, a, (MCfMs)f)) ; }
    virtual MC operator()(char s) { return ((MCfMs)f)(A, a, s) ; } ;
} ;


class MFMss : public MFMs {
  protected:
    char b ;
  public:
    MFMss(MC A, char a, char b, MCfMss f) : MFMs(A, a, (MCfMs)f) { this->b = b ; } ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMss(A, a, b, (MCfMss)f)) ; }
    virtual MC operator()(char s) { return ((MCfMss)f)(A, a, b, s) ; } ;
} ;


class MFMsss : public MFMss {
  protected:
    char c ;
  public:
    MFMsss(MC A, char a, char b, char c, MCfMsss f) : MFMss(A, a, b, (MCfMss)f) { this->c = c ;} ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMsss(A, a, b, c, (MCfMsss)f)) ; }
    virtual MC operator()(char s) { return ((MCfMsss)f)(A, a, b, c, s) ; } ;
} ;


class MFMssss : public MFMsss {
  protected:
    char d ;
  public:
    MFMssss(MC A, char a, char b, char c, char d, MCfMssss f) : MFMsss(A, a, b, c, (MCfMsss)f) { this->d = d ;} ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMssss(A, a, b, c, d, (MCfMssss)f)) ; }
    virtual MC operator()(char s) { return ((MCfMssss)f)(A, a, b, c, d, s) ; } ;
} ;


class MFMsssss : public MFMssss {
  protected:
    char e ;
  public:
    MFMsssss(MC A, char a, char b, char c, char d, char e, MCfMsssss f) : MFMssss(A, a, b, c, d, (MCfMssss)f) { this->e = e ;} ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMsssss(A, a, b, c, d, e, (MCfMsssss)f)) ; }
    virtual MC operator()(char s) { return ((MCfMsssss)f)(A, a, b, c, d, e, s) ; } ;
} ;


class MFMMs : public MFM {
  protected:
    MC B ;
    char a ;
  public:
    MFMMs(MC A, MC B, char a, MCfMMs f) : MFM(A, (MCfM)f) { this->B = B->clone() ; this->a = a ; } ;
    int size(){ return sizeof(*this) + sizeof(*B) ; } ;
    virtual MC clone(){ return count(new MFMMs(A, B, a, (MCfMMs)f)) ; }
    virtual ~MFMMs() { delete uncount(B) ; } ;
    virtual MC operator()(char s) { return ((MCfMMs)f)(A, B, a, s) ; } ;
} ;


class MFMMss : public MFMMs {
  protected:
    char b ;
  public:
    MFMMss(MC A, MC B, char a, char b, MCfMMss f) : MFMMs(A, B, a, (MCfMMs)f) { this->b = b ; } ;
    int size(){ return sizeof(*this) ; } ;
    virtual MC clone(){ return count(new MFMMss(A, B, a, b, (MCfMMss)f)) ; }
    virtual MC operator()(char s) { return ((MCfMMss)f)(A, B, a, b, s) ; } ;
} ;


class MFMMMss : public MFM {
  protected:
    MC B ;
    MC C ;
    char a ;
    char b ;
  public:
    MFMMMss(MC A, MC B, MC C, char a, char b, MCfMMMss f) : MFM(A, (MCfM)f) { this->B = B->clone() ; this->C = C->clone() ; this->a = a ; this->b = b ; } ;
    int size(){ return sizeof(*this) + sizeof(*B) + sizeof(*C) ; } ;
    virtual MC clone(){ return count(new MFMMMss(A, B, C, a, b, (MCfMMMss)f)) ; }
    virtual ~MFMMMss() { delete uncount(B) ; delete uncount(C) ; } ;
    virtual MC operator()(char s) { return ((MCfMMMss)f)(A, B, C, a, b, s) ; } ;
} ;


extern void free_cache() ;


#endif