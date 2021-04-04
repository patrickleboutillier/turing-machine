#ifndef FUNCLIB_H
#define FUNCLIB_H

#include "MF.h"


MC f(MC C, MC B, char a), f1(MC C, MC B, char a), f2(MC C, MC B, char a), e(MC C, MC B, char a), e1(MC C, MC B, char a), e(MC B, char a) ;
MC pe(MC C, char b), pe1(MC C, char b), l(MC C), r(MC C), fl(MC C, MC B, char a), fr(MC C, MC B, char a), c(MC C, MC B, char a), c1(MC C) ; 
MC ce(MC C, MC B, char a), ce(MC B, char a), re(MC C, MC B, char a, char b), re1(MC C, char b), re(MC B, char a, char b) ;
MC cr(MC C, MC B, char a), cr(MC B, char a), cp(MC C, MC U, MC E, char a, char b), cp1(MC C, MC U, char b), cp2(MC C, MC U, char y) ;
MC cpe(MC C, MC U, MC E, char a, char b), cpe(MC U, MC E, char a, char b) ;
MC g(MC C), g1(MC C), g(MC C, char a), g1(MC C, char a), pe2(MC C, char a, char b) ; 
MC ce2(MC B, char a, char b), ce3(MC B, char a, char b, char y), ce4(MC B, char a, char b, char y, char o), ce5(MC B, char a, char b, char y, char o, char e) ;
MC e(MC C), e1(MC C) ;


#endif
