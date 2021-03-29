#include "MCONFIG.h"
#include "MFUNCTIONS.h"


// page 115
MF<MC*(MC*, MC*, char)> f("f", [](MC *C, MC *B, char a, char s){
  SYM(s, 'e', "<", f1(C, B, a, s)) ;
  NOT(s, 'e', "<", f(C, B, a, s)) ;
  NONE(s,     "<", f(C, B, a, s)) ;
}) ;
MF<MC*(MC*, MC*, char)> f1("f1", [](MC *C, MC *B, char a, char s){
  SYM(s, a,   "",   C) ;
  NOT(s, a,   ">",  f1(C, B, a, s)) ;
  NONE(s,     ">",  f2(C, B, a, s)) ;
}) ;
MF<MC*(MC*, MC*, char)> f2("f2", [](MC *C, MC *B, char a, char s){
  SYM(s, a,   "",   C) ;
  NOT(s, a,   ">",  f1(C, B, a, s)) ;
  NONE(s,     ">",  B) ;
}) ;


// page 118
MF<MC*(MC*, MC*, char)> e_3("e_3", [](MC *C, MC *B, char a, char s){ 
  BLANK(s, "",  f(e1(C, B, a, s), B, a, s)) ;
}) ;
MF<MC*(MC*, MC*, char)> e1("e", [](MC *C, MC *B, char a, char s){ 
  BLANK(s, " ", C) ;
}) ;  
MF<MC*(MC*, char)> e_2("e_2", [](MC *B, char a, char s){ 
  BLANK(s, "",  e_3(e_2(B, a, s), B, a, s)) ;
}) ;  


// page 120
MF<MC*(MC*, char)> pe("pe", [](MC *C, char b, char s){ 
  BLANK(s, "", f(pe1(C, b, s), C, 'e', s)) ;
}) ;  
MF<MC*(MC*, char)> pe1("pe1", [](MC *C, char b, char s){ 
  ANY(s,  ">>", pe1(C, b, s)) ;
  const char op[] = {b, '\0'} ;
  NONE(s, op,   C) ;
}) ;  


// page 121
MF<MC*(MC*)> l("l", [](MC *C, char s){ 
  BLANK(s, "<", C) ;
}) ;  
MF<MC*(MC*)> r("r", [](MC *C, char s){ 
  BLANK(s, ">", C) ;
}) ;

MF<MC*(MC*, MC*, char)> fl("fl", [](MC *C, MC *B, char a, char s){
  BLANK(s, "", f(l(C, s), B, a, s)) ;
}) ;
MF<MC*(MC*, MC*, char)> fr("fr", [](MC *C, MC *B, char a, char s){
  BLANK(s, "", f(r(C, s), B, a, s)) ;
}) ;


MF<MC*(MC*, MC*, char)> c("c", [](MC *C, MC *B, char a, char s){
  BLANK(s, "", fl(c1(C, s), B, a, s)) ;
}) ;
MF<MC*(MC*)> c1("c1", [](MC *C, char s){ 
  return pe(C, s, s) ;
}) ;


// page 122
MF<MC*(MC*, MC*, char)> ce_3("ce", [](MC *C, MC *B, char a, char s){
  BLANK(s, "", c(e_3(C, B, a, s), B, a, s)) ;
}) ;  
MF<MC*(MC*, char)> ce_2("ce", [](MC *B, char a, char s){
  BLANK(s, "", ce_3(ce_2(B, a, s), B, a, s)) ;
}) ;  

MF<MC*(MC*, MC*, char, char)> re_4("re_4", [](MC *C, MC *B, char a, char b, char s){
  BLANK(s, "", f(re1(C, B, a, b, s), B, a, s)) ;
}) ;  
MF<MC*(MC*, MC*, char, char)> re1("re1", [](MC *C, MC *B, char a, char b, char s){  
  const char ops[] = {' ', b, '\0'} ;
  BLANK(s, ops, C) ;
}) ;  

MF<MC*(MC*, char, char)> re_3("re_3", [](MC *B, char a, char b, char s){
  BLANK(s, "", re_4(re_3(B, a, b, s), B, a, b, s)) ;
}) ; 


/*
extern MF cr(MF C, MF B, const char *a), cr(MF B, const char *a), cp(MF C, MF U, MF E, const char *a, const char *b), 
  cp1(MF C, MF U, const char *b), cp2(MF C, MF U, const char *b), 
  cpe(MF C, MF U, MF E, const char *a, const char *b), cpe(MF U, MF E, const char *a, const char *b) ;

// page 123
MF cr(MF C, MF B, const char *a){ return [C, B, a]() {
  BLANK, "", c(re(C, B, a, a), B, a)) ;
} ; } ;  
MF cr(MF B, const char *a){ return [B, a]() {
  BLANK, "", cr(cr(B, a), re(B, a, a), a)) ;
} ; } ; 

MF cp(MF C, MF U, MF E, const char *a, const char *b){ return [C, U, E, a, b]() {
  BLANK, "", fl(cp1(C, U, b), f(U, E, b), a)) ;
} ; } ; 
MF cp1(MF C, MF U, const char *b){ return [C, U, b]() {
  const char *dom = MC.get_domain() ;
  for (int i = 0 ; dom[i] != '\0' ; i++){
    dom[i], "", fl(cp2(C, U, &dom[i]), U, b)) ;
  }
} ; } ;
MF cp2(MF C, MF U, const char *y){ return [C, U, y]() {
  SYM(*y), "", C) ;
  NOT(*y), "", U) ; //-- None line required here?
} ; } ; 

MF cpe(MF C, MF U, MF E, const char *a, const char *b){ return [C, U, E, a, b]() {
  BLANK, "", cp(e(e(C, C, b), C, a), U, E, a, b)) ;
} ; } ; 
MF cpe(MF U, MF E, const char *a, const char *b){ return [U, E, a, b]() {
  BLANK, "", cpe(cpe(U, E, a, b), U, E, a, b)) ;
} ; } ;


extern MF g(MF C), g1(MF C), g(MF C, const char *a), g1(MF C, const char *a), pe2(MF C, MF B, const char *a) ;

// page 124, g instead of q
MF g(MF C){ return [C]() {
  ANY,  ">", g(C)) ;
  NONE, ">", g1(C)) ;
} ; } ;
MF g1(MF C){ return [C]() {  
  ANY,  ">", g(C)) ;
  NONE, "",  C) ;
} ; } ; 

MF g(MF C, const char *a){ return [C, a]() {  
  BLANK, "", g(g1(C, a))) ;
} ; } ; 
MF g1(MF C, const char *a){ return [C, a]() {  
  SYM(*a), "", C) ;
  NOT(*a), "<", g1(C, a)) ;
  NONE,   "<", g1(C, a)) ;
} ; } ; 

MF pe2(MF C, const char *a, const char *b){ return [C, a, b]() {
  BLANK, "", pe(pe(C, b), a)) ; 
} ; } ;


extern MF ce(MF B, const char *a, const char *b), ce(MF B, const char *a, const char *b, const char *y), ce(MF B, const char *a, const char *b, const char *y, const char *o),
  ce(MF B, const char *a, const char *b, const char *y, const char *o, const char *e), e(MF C), e1(MF C) ;

// page 125
MF ce(MF B, const char *a, const char *b){ return [B, a, b]() {
  BLANK, "", ce(ce(B, b), a)) ;
} ; } ;
MF ce(MF B, const char *a, const char *b, const char *y){ return [B, a, b, y]() {
  BLANK, "", ce(ce(B, b, y), a)) ;
} ; } ;
MF ce(MF B, const char *a, const char *b, const char *y, const char *o){ return [B, a, b, y, o]() {
  BLANK, "", ce(ce(B, b, y, o), a)) ;
} ; } ;
 MF ce(MF B, const char *a, const char *b, const char *y, const char *o, const char *e){ return [B, a, b, y, o, e]() {
  BLANK, "", ce(ce(B, b, y, o, e), a)) ;
} ; } ;

MF e(MF C){ return [C]() { 
    SYM('e'), ">", e1(C)) ;
    NOT('e'), "<", e(C)) ;
    NONE,     "<", e(C)) ;
} ; } ;    
MF e1(MF C){ return [C]() { 
    ANY,  "> >", e1(C)) ; 
    NONE, "",    e(C)) ;
} ; } ;    


*/