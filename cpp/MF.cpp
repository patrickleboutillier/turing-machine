#include "MF.h"


MC MF(MC A, MCfM f){
    return new MFM(A, f) ;
}


MC MF(MC A, char a, MCfMs f){
    return new MFMs(A, a, f) ;
}


/*
MC MF(MC, char, char, MCfMss){
    return nullptr ;
}


MC MF(MC, char, char, char, MCfMsss){
    return nullptr ;
}


MC MF(MC, char, char, char, char, MCfMssss){
    return nullptr ;
}


MC MF(MC, char, char, char, char, char, MCfMsssss){
    return nullptr ;
}
*/


MC MF(MC A, MC B, char a, MCfMMs f){
    return new MFMMs(A, B, a, f) ;
}


MC MF(MC A, MC B, char a, char b, MCfMMss f){
    return new MFMMss(A, B, a, b, f) ;
}


//MC MF(MC, MC, MC, char, char, MCfMMMss){
//    return nullptr ;
//}