#include "MCONFIG.h"
#include "MFUNCTIONS.h"


// page 115
MF<MC(MC, MC, char)> f("f", [](MC C, MC B, char a, char s){
  SYM(s, 'e', "<", f1(C, B, a)) ;
  NOT(s, 'e', "<", f(C, B, a)) ;
  NONE(s,     "<", f(C, B, a)) ;
}) ;
MF<MC(MC, MC, char)> f1("f1", [](MC C, MC B, char a, char s){
  SYM(s, a,   "",   C) ;
  NOT(s, a,   ">",  f1(C, B, a)) ;
  NONE(s,     ">",  f2(C, B, a)) ;
}) ;
MF<MC(MC, MC, char)> f2("f2", [](MC C, MC B, char a, char s){
  SYM(s, a,   "",   C) ;
  NOT(s, a,   ">",  f1(C, B, a)) ;
  NONE(s,     ">",  B) ;
}) ;


// page 118
MF<MC(MC, MC, char)> e_3("e_3", [](MC C, MC B, char a, char s){ 
  BLANK(s, "",  f(e1(C, B, a), B, a)) ;
}) ;
MF<MC(MC, MC, char)> e1("e1", [](MC C, MC B, char a, char s){ 
  BLANK(s, " ", C) ;
}) ;  
MF<MC(MC, char)> e_2("e_2", [](MC B, char a, char s){ 
  BLANK(s, "",  e_3(e_2(B, a), B, a)) ;
}) ;  


// page 120
MF<MC(MC, char)> pe("pe", [](MC C, char b, char s){ 
  BLANK(s, "", f(pe1(C, b), C, 'e')) ;
}) ;  
MF<MC(MC, char)> pe1("pe1", [](MC C, char b, char s){ 
  ANY(s,  ">>", pe1(C, b)) ;
  const char op[] = {b, '\0'} ;
  NONE(s, op,   C) ;
}) ;  


// page 121
MF<MC(MC)> l("l", [](MC C, char s){ 
  BLANK(s, "<", C) ;
}) ;  
MF<MC(MC)> r("r", [](MC C, char s){ 
  BLANK(s, ">", C) ;
}) ;

MF<MC(MC, MC, char)> fl("fl", [](MC C, MC B, char a, char s){
  BLANK(s, "", f(l(C), B, a)) ;
}) ;
MF<MC(MC, MC, char)> fr("fr", [](MC C, MC B, char a, char s){
  BLANK(s, "", f(r(C), B, a)) ;
}) ;

MF<MC(MC, MC, char)> c("c", [](MC C, MC B, char a, char s){
  BLANK(s, "", fl(c1(C), B, a)) ;
}) ;
MF<MC(MC)> c1("c1", [](MC C, char s){ 
  return pe(C, s) ;
}) ;


// page 122
MF<MC(MC, MC, char)> ce_3("ce_3", [](MC C, MC B, char a, char s){
  BLANK(s, "", c(e_3(C, B, a), B, a)) ;
}) ;  
MF<MC(MC, char)> ce_2("ce_2", [](MC B, char a, char s){
  BLANK(s, "", ce_3(ce_2(B, a), B, a)) ;
}) ;  

MF<MC(MC, MC, char, char)> re_4("re_4", [](MC C, MC B, char a, char b, char s){
  BLANK(s, "", f(re1(C, B, a, b), B, a)) ;
}) ;  
MF<MC(MC, MC, char, char)> re1("re1", [](MC C, MC B, char a, char b, char s){  
  const char ops[] = {' ', b, '\0'} ;
  BLANK(s, ops, C) ;
}) ;  

MF<MC(MC, char, char)> re_3("re_3", [](MC B, char a, char b, char s){
  BLANK(s, "", re_4(re_3(B, a, b), B, a, b)) ;
}) ; 


// page 123
MF<MC(MC, MC, char)> cr_3("cr_3", [](MC C, MC B, char a, char s){
  BLANK(s, "", c(re_4(C, B, a, a), B, a)) ;
}) ;  
MF<MC(MC, char)> cr_2("cr_2", [](MC B, char a, char s){
  BLANK(s, "", cr_3(cr_2(B, a), re_3(B, a, a), a)) ;
}) ; 


MF<MC(MC, MC, MC, char, char)> cp("cp", [](MC C, MC U, MC E, char a, char b, char s){
  BLANK(s, "", fl(cp1(C, U, b), f(U, E, b), a)) ;
}) ; 
MF<MC(MC, MC, char)> cp1("cp1", [](MC C, MC U, char b, char s){
  return fl(cp2(C, U, s), U, b) ;
}) ;
MF<MC(MC, MC, char)> cp2("cp2", [](MC C, MC U, char y, char s){
  SYM(s, y, "", C) ;
  NOT(s, y, "", U) ; // NONE line required here?
}) ; 


//MF cpe(MF C, MF U, MF E, const char *a, const char *b){ return [C, U, E, a, b]() {
MF<MC(MC, MC, MC, char, char)> cpe_5("cpe_5", [](MC C, MC U, MC E, char a, char b, char s){
  BLANK(s, "", cp(e_3(e_3(C, C, b), C, a), U, E, a, b)) ;
}) ; 
MF<MC(MC, MC, char, char)> cpe_4("cpe_4", [](MC U, MC E, char a, char b, char s){
  BLANK(s, "", cpe_5(cpe_4(U, E, a, b), U, E, a, b)) ;
}) ;


// page 124, g instead of q
MF<MC(MC)> g("g", [](MC C, char s){ 
  ANY(s,  ">", g(C)) ;
  NONE(s, ">", g1(C)) ;
}) ;
MF<MC(MC)> g1("g1", [](MC C, char s){ 
  ANY(s,  ">", g(C)) ;
  NONE(s, "",  C) ;
}) ;


MF<MC(MC, char)> g_2("g_2", [](MC C, char a, char s){ 
  BLANK(s, "", g(g1_2(C, a))) ;
}) ; 
MF<MC(MC, char)> g1_2("g1_2", [](MC C, char a, char s){ 
  SYM(s, a, "", C) ;
  NOT(s, a, "<", g1_2(C, a)) ;
  NONE(s,   "<", g1_2(C, a)) ;
}) ; 

MF<MC(MC, char, char)> pe2("pe2", [](MC C, char a, char b, char s){
  BLANK(s, "", pe(pe(C, b), a)) ; 
}) ; 


// page 125
MF<MC(MC, char, char)> ce2("ce2", [](MC B, char a, char b, char s){
  BLANK(s, "", ce_2(ce_2(B, b), a)) ;
}) ;
MF<MC(MC, char, char, char)> ce3("ce3", [](MC B, char a, char b, char y, char s){
  BLANK(s, "", ce_2(ce2(B, b, y), a)) ;
}) ;
MF<MC(MC, char, char, char, char)> ce4("ce4", [](MC B, char a, char b, char y, char o, char s){
  BLANK(s, "", ce_2(ce3(B, b, y, o), a)) ;
}) ;
MF<MC(MC, char, char, char, char, char)> ce5("ce5", [](MC B, char a, char b, char y, char o, char e, char s){
  BLANK(s, "", ce_2(ce4(B, b, y, o, e), a)) ;
}) ;

MF<MC(MC)> e_1("e_1", [](MC C, char s){ 
  SYM(s, 'e', ">", e1_1(C)) ;
  NOT(s, 'e', "<", e_1(C)) ;
  NONE(s,     "<", e_1(C)) ;
}) ;    
MF<MC(MC)> e1_1("e1_1", [](MC C, char s){ 
  ANY(s,  "> >", e1_1(C)) ; 
  NONE(s, "",    C) ;
}) ;    

