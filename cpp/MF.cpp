#include "MF.h"


MC MF(MC A, MCfM f){
    return new MFM(A, f) ;
}


MC MF(MC A, char a, MCfMs f){
    return new MFMs(A, a, f) ;
}


MC MF(MC A, char a, char b, MCfMss f){
   return new MFMss(A, a, b, f) ;
}


MC MF(MC A, char a, char b, char c, MCfMsss f){
    return new MFMsss(A, a, b, c, f) ;
}


MC MF(MC A, char a, char b, char c, char d, MCfMssss f){
    return new MFMssss(A, a, b, c, d, f) ;
}


MC MF(MC A, char a, char b, char c, char d, char e, MCfMsssss f){
    return new MFMsssss(A, a, b, c, d, e, f) ;
}


MC MF(MC A, MC B, char a, MCfMMs f){
    return new MFMMs(A, B, a, f) ;
}


MC MF(MC A, MC B, char a, char b, MCfMMss f){
    return new MFMMss(A, B, a, b, f) ;
}


MC MF(MC A, MC B, MC C, char a, char b, MCfMMMss f){
    return new MFMMMss(A, B, C, a, b, f) ;
}