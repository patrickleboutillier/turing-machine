#include "MF.h"


#define NB_TEMP 3
MC TEMP[NB_TEMP] = {nullptr, nullptr, nullptr} ;
int TEMP_IDX = 0 ;


void free_cache(){
    for (int i = 0 ; i < NB_TEMP ; i++){
        if (TEMP[i] != nullptr){
            delete MCONFIG::uncount(TEMP[i]) ;
        }
    }
}


MC wrap(MC t){
    t = MCONFIG::count(t) ;
    if (TEMP[TEMP_IDX] != nullptr){
        delete MCONFIG::uncount(TEMP[TEMP_IDX]) ;
    }
    TEMP[TEMP_IDX] = t ;
    TEMP_IDX = (TEMP_IDX + 1) % NB_TEMP ;

    return t ;
}


MC MF(MC A, MCfM f){
    return wrap(new MFM(A, f)) ;
}


MC MF(MC A, char a, MCfMs f){
    return wrap(new MFMs(A, a, f)) ;
}


MC MF(MC A, char a, char b, MCfMss f){
   return wrap(new MFMss(A, a, b, f)) ;
}


MC MF(MC A, char a, char b, char c, MCfMsss f){
    return wrap(new MFMsss(A, a, b, c, f)) ;
}


MC MF(MC A, char a, char b, char c, char d, MCfMssss f){
    return wrap(new MFMssss(A, a, b, c, d, f)) ;
}


MC MF(MC A, char a, char b, char c, char d, char e, MCfMsssss f){
    return wrap(new MFMsssss(A, a, b, c, d, e, f)) ;
}


MC MF(MC A, MC B, char a, MCfMMs f){
    return wrap(new MFMMs(A, B, a, f)) ;
}


MC MF(MC A, MC B, char a, char b, MCfMMss f){
    return wrap(new MFMMss(A, B, a, b, f)) ;
}


MC MF(MC A, MC B, MC C, char a, char b, MCfMMMss f){
    return wrap(new MFMMMss(A, B, C, a, b, f)) ;
}